
// SmartView.h
//

#pragma once

#include "pch.h"
#include "Resource.h"

/////////////////////////////////////////////////////////////////////////////
// CSmartView

/// <summary> Шаблонен клас за View. </summary>
template<class DOCUMENT_CLASS, typename RECORD_TYPE>
class CSmartView : public CListView
{
	// Macros
	// ----------------


	// Constants
	// ----------------
	

	// Constructor / Destructor
	// ----------------
	
public:

	/// <summary> Контруктор. </summary>
	CSmartView()
	{
	}
	
	/// <summary> Деструктор. </summary>
	virtual ~CSmartView()
	{
	}
	
	// Overrides
	// ----------------
	
public:

	/// <summary> Добавяне на заглавни редове във View-то. </summary>
	virtual BOOL SetColumnsHeader() = 0;

	/// <summary> Визуализиране на данни по колоните във View-то. </summary>
	/// <param name="lRecordIndex"> Номерът на елемента. </param>	
	/// <param name="recRecord"> Запис за визуализиране. </param>	
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	virtual BOOL SetItem(const long lRecordIndex, const RECORD_TYPE& recRecord) = 0;

	/// <summary> Вземане на идентификатора на записа. </summary>
	/// <param name="recRecord"> Записa. </param>	
	/// <returns> Идентификаторът на записа. </returns>
	virtual const long GetRecordID(const RECORD_TYPE& recRecord) const = 0;

	/// <summary> Отваря диалога. </summary>
	/// <param name="recRecord"> Записa. </param>	
	/// <param name="RecordsAction"> Действие със записa. </param>	
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	virtual BOOL OpenDialog(RECORD_TYPE& recRecord, const RecordsActions RecordsAction) = 0;

	/// <summary> Първоначална инициализация на View-то. </summary>
	virtual void OnInitialUpdate() override
	{
		__super::OnInitialUpdate();

		if (!SetColumnsStyle())
		{
			MessageBox(gl_strErrorLoadingData, gl_strError, MB_ICONERROR);
			return;
		}

		if (!SetColumnsHeader())
		{
			MessageBox(gl_strErrorLoadingData, gl_strError, MB_ICONERROR);
			return;
		}

		if (!LoadRecords())
		{
			MessageBox(gl_strErrorLoadingData, gl_strError, MB_ICONERROR);
			return;
		}
	}

	/// <summary> Oпресняване на данните при промяна в документа. </summary>
	/// <param name="pSender"> Указател към view-то, от което е направена промяната. </param>
	/// <param name="lHint"> Член променлива, съдържаща информация за вида на промяната (редактиране, добавяне, изтриване). </param>	
	/// <param name="pHint"> Указател към променения запис. </param>
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) override
	{
		if (lHint == RecordsActionInsert)
		{
			RECORD_TYPE* pRecord = (RECORD_TYPE*)pHint;
			if (pRecord == NULL)
			{
				MessageBox(gl_strErrorLoadingData, gl_strError, MB_ICONERROR);
				return;
			}

			// Добавяне на ред
			long lRecordIndex = GetListCtrl().GetItemCount();

			if (GetListCtrl().InsertItem(lRecordIndex, 0) != INT_ERROR)
				SetItem(lRecordIndex, *pRecord);
		}
		else if (lHint == RecordsActionUpdate)
		{
			RECORD_TYPE* pRecord = (RECORD_TYPE*)pHint;
			if (pRecord == NULL)
			{
				MessageBox(gl_strErrorLoadingData, gl_strError, MB_ICONERROR);
				return;
			}

			// Редактиране на ред
			for (long i = 0; i < GetListCtrl().GetItemCount(); i++)
			{
				if (GetListCtrl().GetItemData(i) != GetRecordID(*pRecord))
					continue;

				SetItem(i, *pRecord);
				break;
			} // for
		}
		else if (lHint == RecordsActionDelete)
		{
			long* pID = (long*)pHint;
			if (pID == NULL)
			{
				MessageBox(gl_strErrorLoadingData, gl_strError, MB_ICONERROR);
				return;
			}

			// Изтриване на ред
			for (long i = 0; i < GetListCtrl().GetItemCount(); i++)
			{
				if (GetListCtrl().GetItemData(i) != *pID)
					continue;

				if (GetListCtrl().DeleteItem(i) == 0)
					break;
			}
		} // if
	}
	
	// Methods
	// ----------------
	
public:
	
	/// <summary> Достъпване на документа. </summary>
	/// <returns> Указател към документа. </returns>
	DOCUMENT_CLASS* GetDocument() const
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(DOCUMENT_CLASS)));
		return (DOCUMENT_CLASS*)m_pDocument;
	}
	
	/// <summary> Зареждане на записи. </summary>
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	virtual BOOL LoadRecords()
	{
		const CSmartPtrArray<RECORD_TYPE>& oRecordsArray = ((DOCUMENT_CLASS*)GetDocument())->GetDataArray();

		long lRecordIndex = 0;
		for (INT_PTR i = 0; i < oRecordsArray.GetCount(); i++, lRecordIndex++)
		{
			// Извличане на елемент от масива
			RECORD_TYPE* pRecord = oRecordsArray.GetAt(i);
			if (pRecord == NULL)
				return FALSE;

			// Добавяне на нов ред
			if (GetListCtrl().InsertItem(lRecordIndex, NONE) == INT_ERROR)
				return FALSE;

			// Визуализиране на данни
			if (!SetItem(lRecordIndex, *pRecord))
				return FALSE;
		}

		return TRUE;
	}

	/// <summary> Намиране на данните за маркирания елемент. </summary>
	/// <param name="recRecord"> Запис. </param>	
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	virtual BOOL GetSelectedItem(RECORD_TYPE& recRecord)
	{
		// Извличане на позицията на избрания запис
		POSITION oPosition = GetListCtrl().GetFirstSelectedItemPosition();
		if (oPosition == NULL)
		{
			MessageBox(gl_strErrorNoSelectedData, gl_strWarning, MB_ICONWARNING);
			return FALSE;
		}

		// Извличане на избрания елемент
		const CSmartPtrArray<RECORD_TYPE>& oRecordsArray = ((DOCUMENT_CLASS*)GetDocument())->GetDataArray();
		long lItemIndex = GetListCtrl().GetNextSelectedItem(oPosition);

		BOOL bIsRecordFound = FALSE;

		for (INT_PTR i = 0; i < oRecordsArray.GetCount(); i++)
		{
			RECORD_TYPE* pRecord = oRecordsArray.GetAt(i);
			if (pRecord == NULL)
			{
				MessageBox(gl_strErrorRecordNotFound, gl_strError, MB_ICONERROR);
				return FALSE;
			}

			if (GetRecordID(*pRecord) == GetListCtrl().GetItemData(lItemIndex))
			{
				recRecord = *pRecord;
				bIsRecordFound = TRUE;
				break;
			}
		}

		if (!bIsRecordFound)
		{
			MessageBox(gl_strErrorRecordNotFound, gl_strError, MB_ICONERROR);
			return FALSE;
		}

		return TRUE;
	}

protected:

	/// <summary> Задаване на стил на колконите </summary>
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	virtual BOOL SetColumnsStyle()
	{
		if (GetListCtrl().ModifyStyle(0, LVS_REPORT | LVS_SINGLESEL) == 0)
			return FALSE;

		GetListCtrl().SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_TWOCLICKACTIVATE);

		return TRUE;
	}

	// Message Handlers
	// ----------------

protected:

	/// <summary> При натискане на десен бутон. </summary>
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point)
	{
		ClientToScreen(&point);
		OnContextMenu(this, point);
	}

	/// <summary> При отваряне на контекстното меню. </summary>
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point)
	{
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_LIST_VIEW_CONTEXT_MENU, point.x, point.y, this, TRUE);
	}

	/// <summary> При натискане на елемент от списъка. </summary>
	afx_msg void ItemActivate(NMHDR* pNMHDR, LRESULT* pResult)
	{
		// Извличане на избрания елемент
		RECORD_TYPE recRecord;
		if (!GetSelectedItem(recRecord))
			return;

		// Отваряне на диалога
		OpenDialog(recRecord, RecordsActionView);
	}

	/// <summary> При натискане на преглед от контекстното меню. </summary>
	afx_msg void OnCommandView()
	{
		// Извличане на избрания елемент
		RECORD_TYPE recRecord;
		if (!GetSelectedItem(recRecord))
			return;

		// Отваряне на диалога
		OpenDialog(recRecord, RecordsActionView);
	}

	/// <summary> При натискане на преглед от контекстното меню. </summary>
	afx_msg void OnUpdateCommandUIView(CCmdUI* pCmdUI)
	{
		if (GetListCtrl().GetFirstSelectedItemPosition() == NULL)
			pCmdUI->Enable(false);
		else
			pCmdUI->Enable(true);
	}

	/// <summary> При натискане на добавяне от контекстното меню. </summary>
	afx_msg void OnCommandInsert()
	{
		RECORD_TYPE recRecord;

		// Отваряне на диалога
		if (!OpenDialog(recRecord, RecordsActionInsert))
			return;

		// Редактиране на записа
		if (!((DOCUMENT_CLASS*)GetDocument())->InsertRecord(recRecord))
			MessageBox(gl_strErrorDataInsertFailed, gl_strError, MB_ICONERROR);
	}

	/// <summary> При натискане на добавяне от контекстното меню. </summary>
	afx_msg void OnUpdateCommandUIInsert(CCmdUI* pCmdUI)
	{
		if (theApp.GetCurrentUser().GetAccessLevel() != EmployeeAccessLevelAdmin)
			pCmdUI->Enable(false);
		else
			pCmdUI->Enable(true);
	}

	/// <summary> При натискане на редактиране от контекстното меню. </summary>
	afx_msg void OnCommandUpdate()
	{
		// Извличане на избрания елемент
		RECORD_TYPE recRecord;
		if (!GetSelectedItem(recRecord))
			return;

		// Отваряне на диалога
		if (!OpenDialog(recRecord, RecordsActionUpdate))
			return;

		// Редактиране на записа
		if (!((DOCUMENT_CLASS*)GetDocument())->UpdateRecord(GetRecordID(recRecord), recRecord))
			MessageBox(gl_strErrorDataUpdateFailed, gl_strError, MB_ICONERROR);
	}

	/// <summary> При натискане на редактиране от контекстното меню. </summary>
	afx_msg void OnUpdateCommandUIUpdate(CCmdUI* pCmdUI)
	{
		if (GetListCtrl().GetFirstSelectedItemPosition() == NULL
			|| theApp.GetCurrentUser().GetAccessLevel() != EmployeeAccessLevelAdmin)
			pCmdUI->Enable(false);
		else
			pCmdUI->Enable(true);
	}

	/// <summary> При натискане на изтриване от контекстното меню. </summary>
	afx_msg void OnCommandDelete()
	{
		// Извличане на избрания елемент
		RECORD_TYPE recRecord;
		if (!GetSelectedItem(recRecord))
			return;

		// Изтриване на записа
		if (!((DOCUMENT_CLASS*)GetDocument())->DeleteRecord(GetRecordID(recRecord)))
			MessageBox(gl_strErrorDataDeleteFailed, gl_strError, MB_ICONERROR);
	}

	/// <summary> При натискане на изтриване от контекстното меню. </summary>
	afx_msg void OnUpdateCommandUIDelete(CCmdUI* pCmdUI)
	{
		if (GetListCtrl().GetFirstSelectedItemPosition() == NULL
			|| theApp.GetCurrentUser().GetAccessLevel() != EmployeeAccessLevelAdmin)
			pCmdUI->Enable(false);
		else
			pCmdUI->Enable(true);
	}

	/// <summary> При натискане на търсене от контекстното меню. </summary>
	afx_msg void OnCommandSearch()
	{
		
	}

	/// <summary> При натискане на опресняване от контекстното меню. </summary>
	afx_msg void OnCommandRefresh()
	{
		// Изтриване на текущите визуализирани данни
		GetListCtrl().DeleteAllItems();
		ASSERT(GetListCtrl().GetItemCount() == 0);

		// Опреснявана на документа
		if (!((DOCUMENT_CLASS*)GetDocument())->RefreshData())
		{
			MessageBox(gl_strErrorLoadingData, gl_strError, MB_ICONERROR);
			return;
		}

		// Зареждане на данните от опреснения документ
		if (!LoadRecords())
			MessageBox(gl_strErrorLoadingData, gl_strError, MB_ICONERROR);
	}

};
