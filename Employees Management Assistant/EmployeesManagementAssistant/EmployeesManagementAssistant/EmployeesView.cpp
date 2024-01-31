
// EmployeesView.cpp
//

#include "pch.h"
#include "EmployeesManagementAssistant.h"
#include "EmployeesView.h"
#include "EmployeesDialog.h"
#include "LoginDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CEmployeesView

#define COLUMN_WIDTH_FIRST_NAME		350
#define COLUMN_WIDTH_MIDDLE_NAME	350
#define COLUMN_WIDTH_LAST_NAME		350
#define COLUMN_WIDTH_IDENTIFIER		100

IMPLEMENT_DYNCREATE(CEmployeesView, CListView)

BEGIN_MESSAGE_MAP(CEmployeesView, CListView)
	ON_WM_RBUTTONUP()
	ON_WM_CONTEXTMENU()

	ON_NOTIFY_REFLECT(LVN_ITEMACTIVATE, &ItemActivate)

	ON_COMMAND(ID_CONTEXT_MENU_VIEW, &OnCommandView)
	ON_UPDATE_COMMAND_UI(ID_CONTEXT_MENU_VIEW, OnUpdateCommandUIView)
	ON_COMMAND(ID_CONTEXT_MENU_INSERT, &OnCommandInsert)
	ON_UPDATE_COMMAND_UI(ID_CONTEXT_MENU_INSERT, OnUpdateCommandUIInsert)
	ON_COMMAND(ID_CONTEXT_MENU_UPDATE, &OnCommandUpdate)
	ON_UPDATE_COMMAND_UI(ID_CONTEXT_MENU_UPDATE, OnUpdateCommandUIUpdate)
	ON_COMMAND(ID_CONTEXT_MENU_DELETE, &CEmployeesView::OnCommandDelete)
	ON_UPDATE_COMMAND_UI(ID_CONTEXT_MENU_DELETE, OnUpdateCommandUIDelete)
	ON_COMMAND(ID_CONTEXT_MENU_SEARCH, &OnCommandSearch)
	ON_COMMAND(ID_CONTEXT_MENU_REFRESH, &OnCommandRefresh)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------

CEmployeesView::CEmployeesView()
{
}

CEmployeesView::~CEmployeesView()
{
}

// Overrides
// ----------------

BOOL CEmployeesView::SetColumnsHeader()
{
	GetDocument()->SetTitle(_T("Служители"));
	SetIcon(NULL, FALSE);

	if (GetListCtrl().InsertColumn(ColumnIndexFirstName			, _T("Име")			, LVCFMT_LEFT, COLUMN_WIDTH_FIRST_NAME		, INT_ERROR) == INT_ERROR
		|| GetListCtrl().InsertColumn(ColumnIndexMiddleName		, _T("Презиме")		, LVCFMT_LEFT, COLUMN_WIDTH_MIDDLE_NAME		, INT_ERROR) == INT_ERROR
		|| GetListCtrl().InsertColumn(ColumnIndexLastName		, _T("Фамилия")		, LVCFMT_LEFT, COLUMN_WIDTH_LAST_NAME		, INT_ERROR) == INT_ERROR
		|| GetListCtrl().InsertColumn(ColumnIndexIdentifier		, _T("ЕГН")			, LVCFMT_LEFT, COLUMN_WIDTH_IDENTIFIER		, INT_ERROR) == INT_ERROR)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEmployeesView::SetItem(const long lItemIndex, const EMPLOYEES& recEmployees)
{
	// Задаване на стойност на колоните
	if (GetListCtrl().SetItemText(lItemIndex, ColumnIndexFirstName, recEmployees.szFirstName) == 0
		|| GetListCtrl().SetItemText(lItemIndex, ColumnIndexMiddleName, recEmployees.szMiddleName) == 0
		|| GetListCtrl().SetItemText(lItemIndex, ColumnIndexLastName, recEmployees.szLastName) == 0
		|| GetListCtrl().SetItemText(lItemIndex, ColumnIndexIdentifier, recEmployees.szIdentifier) == 0)
	{
		MessageBox(gl_strErrorLoadingData, gl_strError, MB_ICONERROR);
		return FALSE;
	}

	// Запазване на ID-то на елемента в масива
	if (GetListCtrl().SetItemData(lItemIndex, recEmployees.lID) == 0)
	{
		MessageBox(gl_strErrorLoadingData, gl_strError, MB_ICONERROR);
		return FALSE;
	}

	return TRUE;
}

const long CEmployeesView::GetRecordID(const EMPLOYEES& recEmployee) const
{
	return recEmployee.lID;
}

BOOL CEmployeesView::OpenDialog(EMPLOYEES& recEmployee, const RecordsActions RecordsAction)
{
	CEmployeesDialog oEmployeesDialog(recEmployee, RecordsAction);
	if (oEmployeesDialog.DoModal() != IDOK)
		return FALSE;

	return TRUE;
}

// Methods
// ----------------

// Message Handlers
// ----------------

/// <summary> При натискане на изтриване от контекстното меню. </summary>
void CEmployeesView::OnCommandDelete()
{
	// Извличане на избрания елемент
	EMPLOYEES recEmployee;
	if (!GetSelectedItem(recEmployee))
		return;

	// Изтриване на записа
	if (!((CEmployeesDocument*)GetDocument())->DeleteRecord(GetRecordID(recEmployee), recEmployee))
		MessageBox(gl_strErrorDataDeleteFailed, gl_strError, MB_ICONERROR);
}
