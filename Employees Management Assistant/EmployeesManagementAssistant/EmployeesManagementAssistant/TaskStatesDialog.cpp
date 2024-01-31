
// TasksStatesDialog.cpp
//

#include "pch.h"
#include "EmployeesManagementAssistant.h"
#include "TaskStatesDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CTaskStatesDialog

IMPLEMENT_DYNAMIC(CTaskStatesDialog, CDialog)

// Constructor / Destructor
// ----------------

CTaskStatesDialog::CTaskStatesDialog(TASK_STATES& recTaskState, const RecordsActions& eRecordAction)
	: CSmartDialog(IDD, recTaskState, eRecordAction)
{
}

CTaskStatesDialog::~CTaskStatesDialog()
{
}

// Overrides
// ----------------

void CTaskStatesDialog::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDB_TASK_STATES_NAME, m_edbName);
	DDX_Control(pDX, IDC_CHB_TASK_STATES_IS_FOR_ARCHIVE, m_chbIsForArchive);
	DDX_Control(pDX, IDOK, m_btnOK);
}

void CTaskStatesDialog::SetTextsLimit()
{
	m_edbName.LimitText(CHAR_SIZE_64);
}

void CTaskStatesDialog::DisableAndHideControls()
{
	m_edbName.SetReadOnly(true);
	m_chbIsForArchive.EnableWindow(FALSE);
	m_btnOK.ShowWindow(SW_HIDE);
}

BOOL CTaskStatesDialog::SetDataToControls()
{
	m_edbName.SetWindowTextW(m_recRecord.szName);
	m_chbIsForArchive.SetCheck(m_recRecord.sIsForAchive == TRUE ? BST_CHECKED : BST_UNCHECKED);

	return TRUE;
}

void CTaskStatesDialog::GetDataFormControls()
{
	CString strTextHelper;

	// Име
	m_edbName.GetWindowTextW(strTextHelper);
	wcscpy_s(m_recRecord.szName, strTextHelper);

	m_recRecord.sIsForAchive = m_chbIsForArchive.GetCheck() == BST_CHECKED ? TRUE : FALSE;
}

BOOL CTaskStatesDialog::Validate()
{
	if (!ValidateMandatoryField(m_recRecord.szName, _T("заглавие")))
		return FALSE;

	return TRUE;
}

// Methods
// ----------------
