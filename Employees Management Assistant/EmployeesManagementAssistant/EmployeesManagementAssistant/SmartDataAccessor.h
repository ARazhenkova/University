
// SmartDataAccessor.h
//

#pragma once

#include "SmartTable.h"

/////////////////////////////////////////////////////////////////////////////
// CSmartDataAccessor

/// <summary> Шаблон за работа с данни. </summary>
template<class TABLE_CLASS, typename RECORD_TYPE>
class CSmartDataAccessor
{
	// Macros
	// ----------------


	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------

public:

	/// <summary> Контруктор. </summary>
	CSmartDataAccessor()
	{
	}

	/// <summary> Деструктор. </summary>
	virtual ~CSmartDataAccessor()
	{
	}

	// Overrides
	// ----------------


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
		return TABLE_CLASS().ReadRecords(oRecordsArray, strRecordsForRead, eLockHint, strConditions);
	}

	/// <summary> Добавяне на запис. </summary>
	/// <param name="recRecord"> Данни. </param>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	virtual BOOL InsertRecord(RECORD_TYPE& recRecord)
	{
		return TABLE_CLASS().InsertRecord(recRecord);
	}

	/// <summary> Актуализация на запис. </summary>
	/// <param name="recRecord"> Данни. </param>
	/// <param name="eLockHint"> Вид заключване. </param>
	/// <param name="strConditions"> Условие на селекта. </param>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	virtual BOOL UpdateRecord(RECORD_TYPE& recRecord
		, const LockHints& eLockHint = LockHintUpdateLock
		, const CString& strConditions = _T(""))
	{
		return TABLE_CLASS().UpdateRecord(recRecord, eLockHint, strConditions);
	}

	/// <summary> Изтриване на запис. </summary>
	/// <param name="strConditions"> Условие на селекта. </param>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	virtual BOOL DeleteRecord(const CString& strConditions = _T(""))
	{
		return TABLE_CLASS().DeleteRecord(strConditions);
	}

	/// <summary> Изчитане на всички записи. </summary>
	/// <param name="oRecordsArray"> Данни. </param>
	/// <param name="eLockHint"> Вид заключване. </param>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	virtual BOOL ReadAllRecords(CSmartPtrArray<RECORD_TYPE>& oRecordsArray
		, const LockHints& eLockHint = LockHintNoLock
		, const CString& strConditions = _T(""))
	{
		return TABLE_CLASS().ReadRecords(oRecordsArray, _T("*"), eLockHint, strConditions);
	}

	/// <summary> Изчитане на запис. </summary>
	/// <param name="recRecord"> Запис. </param>
	/// <param name="bHasRecord"> Дали съществува запис. </param>
	/// <param name="eLockHint"> Вид заключване. </param>
	/// <param name="strConditions"> Условие на селекта. </param>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	virtual BOOL ReadRecord(RECORD_TYPE& recRecord
		, BOOL& bHasRecord
		, const LockHints& eLockHint = LockHintNoLock
		, const CString& strConditions = _T(""))
	{
		CSmartPtrArray<RECORD_TYPE> oRecordsArray;
		bHasRecord = FALSE;

		if (!TABLE_CLASS().ReadRecords(oRecordsArray
			, _T("TOP(1) *"), eLockHint, strConditions))
			return FALSE;

		if (oRecordsArray.GetCount() != 0)
		{
			RECORD_TYPE* pRecord = oRecordsArray.GetAt(0);
			if (pRecord == NULL)
				return FALSE;

			recRecord = *pRecord;
			bHasRecord = TRUE;
		}
	
		return TRUE;
	}

	/// <summary> Актуализация на запис по ID. </summary>
	/// <param name="lID"> Идентификационен номер на записа.</param>
	/// <param name="recRecord"> Данни. </param>
	/// <param name="eLockHint"> Вид заключване. </param>
	/// <param name="strConditions"> Условие на селекта. </param>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	virtual BOOL UpdateRecordByID(const long lID
		, RECORD_TYPE& recRecord
		, const LockHints& eLockHint = LockHintUpdateLock
		, const CString& strConditions = _T(""))
	{
		CString strCustomConditions;
		strCustomConditions.Format(_T("WHERE ID = %ld"), lID);

		if (!strConditions.IsEmpty())
			strCustomConditions.Format(_T("WHERE %s AND %s"), strCustomConditions, strConditions);

		return TABLE_CLASS().UpdateRecord(recRecord, eLockHint, strCustomConditions);
	}

	/// <summary> Изтриване на запис по ID </summary>
	/// <param name="lID"> Идентификационен номер на записа. </param>
	/// <param name="strConditions"> Условие на селекта. </param>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	virtual BOOL DeleteRecordByID(const long lID, const CString& strConditions = _T(""))
	{
		CString strCustomConditions;
		strCustomConditions.Format(_T("WHERE ID = %ld"), lID);

		if (!strConditions.IsEmpty())
			strCustomConditions.Format(_T("WHERE %s AND %s"), strCustomConditions, strConditions);

		return TABLE_CLASS().DeleteRecord(strCustomConditions);
	}

private:

	/// <summary> Възникнали грешки по време на изпълнение. </summary>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	BOOL WriteErrorLog()
	{
		//GetErrorLog();

		return TRUE;
	}

	// Members
	// ----------------

};
