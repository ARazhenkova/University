
// TaskStatesView.cpp
//

#include "pch.h"
#include "EmployeesManagementAssistant.h"
#include "TaskStatesView.h"
#include "TaskStatesDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CTaskStatesView

#define COLUMN_WIDTH_NAME 550

IMPLEMENT_DYNCREATE(CTaskStatesView, CListView)

BEGIN_MESSAGE_MAP(CTaskStatesView, CListView)
	ON_WM_RBUTTONUP()
	ON_WM_CONTEXTMENU()

	ON_NOTIFY_REFLECT(LVN_ITEMACTIVATE, &ItemActivate)

	ON_COMMAND(ID_CONTEXT_MENU_VIEW, &OnCommandView)
	ON_UPDATE_COMMAND_UI(ID_CONTEXT_MENU_VIEW, OnUpdateCommandUIView)
	ON_COMMAND(ID_CONTEXT_MENU_INSERT, &OnCommandInsert)
	ON_UPDATE_COMMAND_UI(ID_CONTEXT_MENU_INSERT, OnUpdateCommandUIInsert)
	ON_COMMAND(ID_CONTEXT_MENU_UPDATE, &OnCommandUpdate)
	ON_UPDATE_COMMAND_UI(ID_CONTEXT_MENU_UPDATE, OnUpdateCommandUIUpdate)
	ON_COMMAND(ID_CONTEXT_MENU_DELETE, &OnCommandDelete)
	ON_UPDATE_COMMAND_UI(ID_CONTEXT_MENU_DELETE, OnUpdateCommandUIDelete)
	ON_COMMAND(ID_CONTEXT_MENU_SEARCH, &OnCommandSearch)
	ON_COMMAND(ID_CONTEXT_MENU_REFRESH, &OnCommandRefresh)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------

CTaskStatesView::CTaskStatesView()
{
}

CTaskStatesView::~CTaskStatesView()
{
}

// Overrides
// ----------------

BOOL CTaskStatesView::SetColumnsHeader()
{
	GetDocument()->SetTitle(_T("Състояние на задача"));

	if (GetListCtrl().InsertColumn(ColumnIndexName, _T("Име"), LVCFMT_LEFT, COLUMN_WIDTH_NAME, INT_ERROR) == INT_ERROR)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTaskStatesView::SetItem(const long lItemIndex, const TASK_STATES& recTaskState)
{
	// Задаване на стойност на колоните
	if (GetListCtrl().SetItemText(lItemIndex, ColumnIndexName, recTaskState.szName) == 0)
	{
		MessageBox(gl_strErrorLoadingData, gl_strError, MB_ICONERROR);
		return FALSE;
	}

	// Запазване на ID-то на елемента в масива
	if (GetListCtrl().SetItemData(lItemIndex, recTaskState.lID) == 0)
	{
		MessageBox(gl_strErrorLoadingData, gl_strError, MB_ICONERROR);
		return FALSE;
	}

	return TRUE;
}

const long CTaskStatesView::GetRecordID(const TASK_STATES& recTaskState) const
{
	return recTaskState.lID;
}

BOOL CTaskStatesView::OpenDialog(TASK_STATES& recTaskState, const RecordsActions RecordsAction)
{
	CTaskStatesDialog oTaskStatesDialog(recTaskState, RecordsAction);
	if (oTaskStatesDialog.DoModal() != IDOK)
		return FALSE;

	return TRUE;
}

// Methods
// ----------------
