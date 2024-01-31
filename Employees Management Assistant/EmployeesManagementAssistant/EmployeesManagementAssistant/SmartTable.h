
// SmartTable.h
//

#pragma once

#include "pch.h"
#include "DatabaseAccessor.h"

/////////////////////////////////////////////////////////////////////////////
// CSmartTable

#define ID_ACCESSOR 0
#define DATA_ACCESSOR 1

/// <summary> Шаблон за работа с таблици. </summary>
template<class ACCESSOR_CLASS, typename RECORD_TYPE>
class CSmartTable : protected CCommand<CAccessor<ACCESSOR_CLASS>>
{
	// Macros
	// ----------------


	// Constants
	// ----------------

	
	// Constructor / Destructor
	// ----------------
	
public:

	/// <summary> Контруктор. </summary>
	CSmartTable()
		: m_IsInitSuccessful(FALSE)
	{
		m_strErrorLog = _T("");

		// Отваряне на връзка към базата данни
		m_pDatabaseConnection = CDatabaseAccessor::GetInstance();
		if (m_pDatabaseConnection->GetConnectionStatus() == DBConnectionStatusDisconnected)
		{
			m_strErrorLog += gl_strFailedToOpenDatabaseConnection;
			return;
		}

		// Създаване на сесия
		HRESULT hResult = m_oSession.Open(m_pDatabaseConnection->GetDataSource());
		if (FAILED(hResult))
		{
			m_strErrorLog += gl_strFaildToCreateSession;
			return;
		}

		m_IsInitSuccessful = TRUE;
	}

	/// <summary> Деструктор. </summary>
	virtual ~CSmartTable()
	{
		m_oSession.Close();
	}

	// Overrides
	// ----------------
	
protected:

	/// <summary> Вземане на името на таблицата. </summary>
	/// <returns> Името на таблицата. </returns>
	virtual const CString GetTableName() const = 0;

	/// <summary> Вземене на аксесора. </summary>
	/// <returns> Данните. </returns>
	virtual RECORD_TYPE& GetAccessor() = 0;

	/// <summary> Вземане на името на брояча на промени. </summary>
	/// <param name="recRecordType"> Записа, от който се взема брояча на промени. </param>	
	/// <returns> Броячът на промени. </returns>
	virtual const long GetUpdateCounter(const RECORD_TYPE& recRecordType) const = 0;

	/// <summary> Вземане на идентификатора на записа. </summary>
	/// <param name="recRecord"> Записa. </param>	
	/// <returns> Идентификаторът на записа. </returns>
	virtual const long GetRecordID(const RECORD_TYPE& recRecord) const = 0;

	/// <summary> Увеличаване на брояча на промени. </summary>
	virtual void IncrementUpdateCounter(RECORD_TYPE& recRecordType) = 0;

	// Methods
	// ----------------
	
public:

	/// <summary> Изчитане на записи. </summary>
	/// <param name="oRecordsArray"> Данни. </param>
	/// <param name="strRecordsForRead"> Брой записи за изчитане. </param>
	/// <param name="eLockHint"> Вид заключване. </param>
	/// <param name="strConditions"> Условие на селекта. </param>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	virtual BOOL ReadRecords(CSmartPtrArray<RECORD_TYPE>& oRecordsArray
		, const CString& strRecordsForRead = _T("*")
		, const LockHints& eLockHint = LockHintNoLock
		, const CString& strConditions = _T(""))
	{
		// Изпълняване на заявката
		if (!ExecuteQuery(_T("*"), eLockHint, strConditions, TRUE))
			return FALSE;

		// Изчитане на всички записи
		HRESULT hResult = S_OK;
		while (hResult == S_OK)
		{
			if (FAILED(hResult))
			{
				m_strErrorLog += gl_strFailedToReadRecord;
				Close();
				return FALSE;
			}

			RECORD_TYPE* pRecord = new RECORD_TYPE();
			*pRecord = GetAccessor();

			if (GetRecordID(*pRecord) != 0)
				oRecordsArray.Add(pRecord);

			hResult = MoveNext();
		}

		Close();

		return TRUE;
	}
	
	/// <summary> Добавяне на запис. </summary>
	/// <param name="oRecordsType"> Данни. </param>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	virtual BOOL InsertRecord(RECORD_TYPE& recRecordType)
	{
		// Изпълняване на заявката
		if (!ExecuteQuery(_T("TOP(0) *"), LockHintUpdateLock, _T(""), TRUE))
			return FALSE;

		// Добавяне на запис;
		GetAccessor() = recRecordType;

		HRESULT hResult = CRowset::Insert(DATA_ACCESSOR);
		if (FAILED(hResult))
		{
			m_strErrorLog += gl_strInsertRecordFailed;
			Close();
			return FALSE;
		}

		// Извличане на ID на новия запис
		hResult = MoveNext();
		if (FAILED(hResult))
		{
			m_strErrorLog += gl_strFailedToReadRecord;
			Close();
			return FALSE;
		}

		recRecordType = GetAccessor();
		Close();

		return TRUE;
	}

	/// <summary> Актуализация на запис. </summary>
	/// <param name="oRecordsType"> Данни. </param>
	/// <param name="eLockHint"> Вид заключване. </param>
	/// <param name="strConditions"> Условие на селекта. </param>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	virtual BOOL UpdateRecord(RECORD_TYPE& recRecordType
		, const LockHints& eLockHint = LockHintUpdateLock
		, const CString& strConditions = _T(""))
	{
		// Изпълняване на заявката
		if (!ExecuteQuery(_T("TOP(1) *"), eLockHint, strConditions))
			return FALSE;

		// Обработване на записа
		if (GetUpdateCounter(GetAccessor()) != GetUpdateCounter(recRecordType))
		{
			m_strErrorLog += gl_strUpdateCounterDiscrepancy;
			Close();
			return FALSE;
		}

		GetUpdateCounter(recRecordType);
		IncrementUpdateCounter(recRecordType);
		GetAccessor() = recRecordType;

		// Запазване на промените
		HRESULT hResult = SetData(DATA_ACCESSOR);
		if (FAILED(hResult))
		{
			m_strErrorLog += gl_strUpdatedRecordFailed;
			Close();
			return FALSE;
		}

		return TRUE;
	}

	/// <summary> Изтриване на запис по ID </summary>
	/// <param name="strConditions"> Условие на селекта. </param>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	virtual BOOL DeleteRecord(const CString& strConditions = _T(""))
	{
		// Изпълняване на заявката
		if (!ExecuteQuery(_T("TOP(1) *"), LockHintRowLock, strConditions))
			return FALSE;

		// Изтриване на запис;
		HRESULT hResult = Delete();
		if (FAILED(hResult))
		{
			m_strErrorLog += gl_strDeleteRecordFailed;
			Close();
			return FALSE;
		}

		Close();

		return TRUE;
	}
	
	/// <summary> Изпълняване на заявка. </summary>
	/// <param name="strRecordsForRead"> Брой записи за изчитане. </param>
	/// <param name="eLockHint"> Вид заключване. </param>
	/// <param name="strConditions"> Условие на селекта. </param>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	BOOL ExecuteQuery(const CString& strRecordsForRead
		, const LockHints& eLockHint
		, const CString& strConditions
		, BOOL CanReturnNoRecords = FALSE)
	{
		if (!m_IsInitSuccessful)
			return FALSE;

		// Вземане на заключването като текст
		const CString& strLockHint = GetLockHint(eLockHint);
		if (strLockHint.IsEmpty())
			return FALSE;

		// Подготвяне на заявката
		CString strQuery;
		strQuery.Format(_T("SELECT %s FROM [%s] WITH(%s) %s")
			, strRecordsForRead, GetTableName(), strLockHint, strConditions);

		// Настройки за работа със записи
		CDBPropSet oDBRowset = DBPROPSET_ROWSET;

		oDBRowset.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
		oDBRowset.AddProperty(DBPROP_IRowsetScroll, true);
		oDBRowset.AddProperty(DBPROP_IRowsetChange, true);
		oDBRowset.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);

		// Изпълняване на заявката
		HRESULT hResult = Open(m_oSession, strQuery, &oDBRowset);
		if (FAILED(hResult))
		{
			m_strErrorLog += gl_strFailedToExecuteQuery;
			Close();
			return FALSE;
		}

		// Проверка дали заявката е изпълнена успешно
		if (!IsRecordReadSuccessfuly(CanReturnNoRecords))
		{
			m_strErrorLog += gl_strFailedToExecuteQuery;
			Close();
			return FALSE;
		}

		return TRUE;
	}
	
	/// <summary> Проверка дали записът е изчетен успешно. </summary>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	BOOL IsRecordReadSuccessfuly(BOOL CanReturnNoRecords = FALSE)
	{
		HRESULT hResult = MoveFirst();
		
		// Проверка дали изчитането е било успешно
		if (FAILED(hResult))
		{
			m_strErrorLog += gl_strFailedToReadRecord;
			return FALSE;
		}

		// Проверка дали записът съществува
		if (!CanReturnNoRecords && hResult == DB_S_ENDOFROWSET)
		{
			m_strErrorLog += gl_strRecordNotFound;
			return FALSE;
		}

		return TRUE;
	}
	
	/// <summary> Вземане на заключването като текст. </summary>
	/// <returns> Заключването като текст. </returns>
	const CString GetLockHint(const LockHints eLockHint)
	{
		switch(eLockHint)
		{
			case LockHintNoLock:
				return _T("NOLOCK");
			case LockHintUpdateLock:
				return _T("UPDLOCK");
			case LockHintRowLock:
				return _T("ROWLOCK");
			default:
			{
				m_strErrorLog += gl_strLockHintNotFound;
				return _T("");
			}
		} // switch
	}

	/// <summary> Възникнали грешки. </summary>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	CString GetErrorLog()
	{
		return m_strErrorLog;
	}

	// Members
	// ----------------
	
private:

	/// <summary> Дали инициализацията на класа е минала успешно. </summary>
	BOOL m_IsInitSuccessful;

	/// <summary> Връзката с базата данни. </summary>
	CDatabaseAccessor* m_pDatabaseConnection;
	
	/// <summary> Сесията. </summary>
	CSession m_oSession;

	/// <summary> Лог за грешки, които да се изведат в клиенската част. </summary>
	CString m_strErrorLog;
};