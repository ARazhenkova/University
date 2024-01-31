
// TaskPrioritiesView.cpp
//

#include "pch.h"
#include "EmployeesManagementAssistant.h"
#include "TaskPrioritiesView.h"
#include "TaskPrioritiesDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CTaskPrioritiesView

#define COLUMN_WIDTH_NAME 550
#define COLUMN_WIDTH_LEVEL 100

IMPLEMENT_DYNCREATE(CTaskPrioritiesView, CListView)

BEGIN_MESSAGE_MAP(CTaskPrioritiesView, CListView)
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

CTaskPrioritiesView::CTaskPrioritiesView()
{
}

CTaskPrioritiesView::~CTaskPrioritiesView()
{
}

// Overrides
// ----------------

BOOL CTaskPrioritiesView::SetColumnsHeader()
{
	GetDocument()->SetTitle(_T("Приоритети на задача"));

	if (GetListCtrl().InsertColumn(ColumnIndexName		, _T("Име")			, LVCFMT_LEFT	, COLUMN_WIDTH_NAME	, INT_ERROR) == INT_ERROR
		|| GetListCtrl().InsertColumn(ColumnIndexLevel	, _T("Приоритет")	, LVCFMT_CENTER	, COLUMN_WIDTH_LEVEL	, INT_ERROR) == INT_ERROR)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTaskPrioritiesView::SetItem(const long lItemIndex, const TASK_PRIORITIES& recTaskPriority)
{
	// Задаване на стойност на колоните
	if (GetListCtrl().SetItemText(lItemIndex, ColumnIndexName, recTaskPriority.szName) == 0
		|| GetListCtrl().SetItemText(lItemIndex, ColumnIndexLevel, CConvertToString::Convert(recTaskPriority.sLevel)) == 0)
	{
		MessageBox(gl_strErrorLoadingData, gl_strError, MB_ICONERROR);
		return FALSE;
	}

	// Запазване на ID-то на елемента в масива
	if (GetListCtrl().SetItemData(lItemIndex, recTaskPriority.lID) == 0)
	{
		MessageBox(gl_strErrorLoadingData, gl_strError, MB_ICONERROR);
		return FALSE;
	}

	return TRUE;
}

const long CTaskPrioritiesView::GetRecordID(const TASK_PRIORITIES& recTaskPriority) const
{
	return recTaskPriority.lID;
}

BOOL CTaskPrioritiesView::OpenDialog(TASK_PRIORITIES& recTaskPriority, const RecordsActions RecordsAction)
{
	CTaskPrioritiesArray oTaskPrioritiesArray;
	if (!GetDocument()->GetAllPriorities(oTaskPrioritiesArray))
	{
		MessageBox(gl_strErrorFailedToLoadEmployees, gl_strError, MB_ICONERROR);
		return FALSE;
	}

	CTaskPrioritiesDialog oTaskPrioritiesDialog(recTaskPriority, oTaskPrioritiesArray, RecordsAction);
	if (oTaskPrioritiesDialog.DoModal() != IDOK)
		return FALSE;

	return TRUE;
}

// Methods
// ----------------
