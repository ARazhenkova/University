
// SmartDocument.h
//

#pragma once

#include "pch.h"
#include "SmartDataAccessor.h"
#include "EmployeesManagementAssistant.h"

/////////////////////////////////////////////////////////////////////////////
// CSmartDocument

/// <summary> Шаблонен клас за Document. </summary>
template<class DATA_CLASS, typename RECORD_TYPE>
class CSmartDocument : public CDocument
{
	// Macros
	// ----------------


	// Constructor / Destructor
	// ----------------

public:

	/// <summary> Контруктор. </summary>
	CSmartDocument()
	{
	}

	/// <summary> Деструктор. </summary>
	virtual ~CSmartDocument()
	{
	}

	// Overrides
	// ----------------

	/// <summary> Инициализация на документ. </summary>
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	virtual BOOL OnNewDocument() override
	{
		if (!__super::OnNewDocument())
			return FALSE;

		return RefreshData();
	}

	// Methods
	// ----------------

public:

	/// <summary> Достъпване на данните от масив. </summary>
	/// <returns> Масив от данни. </returns>
	const CSmartPtrArray<RECORD_TYPE>& GetDataArray() const
	{
		return m_RecordsArray;
	}

	/// <summary> Добавяне на запис. </summary>
	/// <param name="recRecord"> Структура, която ще се добавя в базата данни. </param>	
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	virtual BOOL CSmartDocument::InsertRecord(RECORD_TYPE& recRecord)
	{
		// Обновяване в базата данни
		DATA_CLASS oDataClass;
		if (!oDataClass.InsertRecord(recRecord))
			return FALSE;

		// Обновяване в масива от данни
		m_RecordsArray.Add(new RECORD_TYPE(recRecord));

		// Обновяване на заредените данни във View-тата
		__super::UpdateAllViews(NULL, RecordsActionInsert, (CObject*)&recRecord);

		return TRUE;
	}

	/// <summary> Актуализиране на запис. </summary>
	/// <param name="lID"> Идентификационният номер на записа. </param>
	/// <param name="recRecord"> Структура, от която ще се опресняват данните. </param>	
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	virtual BOOL CSmartDocument::UpdateRecord(const long lID, RECORD_TYPE& recRecord)
	{
		// Обновяване в базата данни
		if (!DATA_CLASS().UpdateRecordByID(lID, recRecord))
			return FALSE;

		// Обновяване в масива
		RECORD_TYPE recOldRecord;
		INT_PTR nIndex = m_RecordsArray.Search(lID);
		if (nIndex == INT_ERROR)
			return FALSE;

		RECORD_TYPE* pRecord = m_RecordsArray.GetAt(nIndex);
		if (pRecord == NULL)
			return FALSE;

		*pRecord = recRecord;

		// Обновяване на заредените данни във View-тата
		__super::UpdateAllViews(NULL, RecordsActionUpdate, (CObject*)&recRecord);

		return TRUE;
	}

	/// <summary> Изтриване на запис. </summary>
	/// <param name="lID"> Идентификационният номер на записа. </param>
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	BOOL CSmartDocument::DeleteRecord(const long& lID)
	{
		// Обновяване в базата данни
		DATA_CLASS oDataClass;
		if (!oDataClass.DeleteRecordByID(lID))
			return FALSE;

		// Обновяване в масива от данни
		INT_PTR nIndex = m_RecordsArray.Search(lID);
		if (nIndex == INT_ERROR)
			return FALSE;

		m_RecordsArray.DeleteAt(nIndex);

		// Обновяване на заредените данни във View-тата
		__super::UpdateAllViews(NULL, RecordsActionDelete, (CObject*)&lID);

		return TRUE;
	}

	/// <summary> Зареждане на данни повторно. </summary>
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	virtual BOOL RefreshData()
	{
		m_RecordsArray.DeleteAll();

		return DATA_CLASS().ReadAllRecords(m_RecordsArray);
	}

	// Members
	// ----------------

protected:

	/// <summary> Масив от записи. </summary>
	CSmartPtrArray<RECORD_TYPE> m_RecordsArray;
};
