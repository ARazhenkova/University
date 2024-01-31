
// EmployeesView.cpp
//

#include "pch.h"
#include "EmployeesManagementAssistant.h"
#include "TasksView.h"
#include "TaskPriorities.h"
#include "TaskStates.h"
#include "TasksDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CTasksView

#define COLUMN_WIDTH_NAME		550
#define COLUMN_WIDTH_PRIORITY	350
#define COLUMN_WIDTH_STATE		350

IMPLEMENT_DYNCREATE(CTasksView, CListView)

BEGIN_MESSAGE_MAP(CTasksView, CListView)
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

CTasksView::CTasksView()
{
}

CTasksView::~CTasksView()
{
}

// Overrides
// ----------------

BOOL CTasksView::SetColumnsHeader()
{
	GetDocument()->SetTitle(_T("Задачи"));

	if (GetListCtrl().InsertColumn(ColumnIndexName				, _T("Име")				, LVCFMT_LEFT, COLUMN_WIDTH_NAME			, INT_ERROR) == INT_ERROR
		|| GetListCtrl().InsertColumn(ColumnIndexPriority		, _T("Приоритет")		, LVCFMT_LEFT, COLUMN_WIDTH_PRIORITY		, INT_ERROR) == INT_ERROR
		|| GetListCtrl().InsertColumn(ColumnIndexState			, _T("Състояние")		, LVCFMT_LEFT, COLUMN_WIDTH_STATE			, INT_ERROR) == INT_ERROR)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTasksView::SetItem(const long lItemIndex, const TASKS& recTask)
{
	// Задаване на стойност на колоните
	CString strPriorityName;
	GetDocument()->LookForPriority(recTask.lPriorityID, strPriorityName);

	CString strStateName;
	GetDocument()->LookForState(recTask.lStateID, strStateName);

	if (GetListCtrl().SetItemText(lItemIndex		, ColumnIndexName			, recTask.szName) == 0
		|| GetListCtrl().SetItemText(lItemIndex		, ColumnIndexPriority		, strPriorityName) == 0
		|| GetListCtrl().SetItemText(lItemIndex		, ColumnIndexState			, strStateName) == 0)
	{
		MessageBox(gl_strErrorLoadingData, gl_strError, MB_ICONERROR);
		return FALSE;
	}

	// Запазване на ID-то на елемента в масива
	if (GetListCtrl().SetItemData(lItemIndex, recTask.lID) == 0)
	{
		MessageBox(gl_strErrorLoadingData, gl_strError, MB_ICONERROR);
		return FALSE;
	}

	return TRUE;
}

const long CTasksView::GetRecordID(const TASKS& recTask) const
{
	return recTask.lID;
}

BOOL CTasksView::OpenDialog(TASKS& recTask, const RecordsActions RecordsAction)
{
	CTaskPrioritiesArray oTaskPrioritiesArray;
	if (!PrepareTaskPriorities(oTaskPrioritiesArray))
		return FALSE;

	CTaskStatesArray oTaskStatesArray;
	if (!PrepareTaskStates(oTaskStatesArray))
		return FALSE;

	CEmployeesArray oEmployeesArray;
	if (!PrepareEmployees(oEmployeesArray))
		return FALSE;


	CTasksDialog oTasksDialog(recTask, oTaskPrioritiesArray, oTaskStatesArray, oEmployeesArray, RecordsAction);
	if (oTasksDialog.DoModal() != IDOK)
		return FALSE;

	return TRUE;
}

// Methods
// ----------------

BOOL CTasksView::PrepareTaskPriorities(CTaskPrioritiesArray& oTaskPrioritiesArray)
{
	if (!GetDocument()->GetTaskPriorities(oTaskPrioritiesArray))
	{
		MessageBox(gl_strErrorFailedToLoadTaskPriorities, gl_strError, MB_ICONERROR);
		return FALSE;
	}

	if (oTaskPrioritiesArray.GetCount() == 0)
	{
		MessageBox(gl_strErrorNoPriorities, gl_strMissingData, MB_ICONWARNING);
		return FALSE;
	}

	return TRUE;
}

BOOL CTasksView::PrepareTaskStates(CTaskStatesArray& oTaskStatesArray)
{
	if (!GetDocument()->GetTaskStates(oTaskStatesArray))
	{
		MessageBox(gl_strErrorFailedToLoadTaskStates, gl_strError, MB_ICONERROR);
		return FALSE;
	}

	if (oTaskStatesArray.GetCount() == 0)
	{
		MessageBox(gl_strErrorNoStates, gl_strMissingData, MB_ICONWARNING);
		return FALSE;
	}

	return TRUE;
}

BOOL CTasksView::PrepareEmployees(CEmployeesArray& oEmployeesArray)
{
	if (!GetDocument()->GetEmployees(oEmployeesArray))
	{
		MessageBox(gl_strErrorFailedToLoadEmployees, gl_strError, MB_ICONERROR);
		return FALSE;
	}

	if (oEmployeesArray.GetCount() < 2)
	{
		MessageBox(gl_strErrorNotEnoughEmployees, gl_strMissingData, MB_ICONWARNING);
		return FALSE;
	}

	return TRUE;
}

// Message Handlers
// ----------------

void CTasksView::OnUpdateCommandUIInsert(CCmdUI* pCmdUI)
{
	if (theApp.GetCurrentUser().GetAccessLevel() != EmployeeAccessLevelDirector
		&& theApp.GetCurrentUser().GetAccessLevel() != EmployeeAccessLevelAdmin)
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}

void CTasksView::OnUpdateCommandUIUpdate(CCmdUI* pCmdUI)
{
	if (GetListCtrl().GetFirstSelectedItemPosition() == NULL
		|| theApp.GetCurrentUser().GetAccessLevel() == EmployeeAccessLevelEmployee)
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}

void CTasksView::OnUpdateCommandUIDelete(CCmdUI* pCmdUI)
{
	if (GetListCtrl().GetFirstSelectedItemPosition() == NULL
		|| (theApp.GetCurrentUser().GetAccessLevel() != EmployeeAccessLevelDirector
		&& theApp.GetCurrentUser().GetAccessLevel() != EmployeeAccessLevelAdmin))
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}
