
// TasksDialog.cpp
//

#include "pch.h"
#include "EmployeesManagementAssistant.h"
#include "TasksDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CTasksDialog

IMPLEMENT_DYNAMIC(CTasksDialog, CDialog)

// Constructor / Destructor
// ----------------

CTasksDialog::CTasksDialog(TASKS& recTask
	, const CTaskPrioritiesArray& oTaskPrioritiesArray
	, const CTaskStatesArray& oTaskStatesArray
	, const CEmployeesArray& oEmployeesArray
	, const RecordsActions& eRecordAction)
	: CSmartDialog(IDD, recTask, eRecordAction)
	, m_oTaskPrioritiesArray(oTaskPrioritiesArray)
	, m_oTaskStatesArray(oTaskStatesArray)
	, m_oEmployeesArray(oEmployeesArray)
{
}

CTasksDialog::~CTasksDialog()
{
}

// Overrides
// ----------------

void CTasksDialog::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDB_TASKS_NAME				, m_edbName);
	DDX_Control(pDX, IDC_CMB_TASKS_PRIORITY			, m_cmbPriority);
	DDX_Control(pDX, IDC_CMB_TASKS_STATE			, m_cmbState);
	DDX_Control(pDX, IDC_CMB_TASKS_ASSIGN_FROM		, m_cmbAssignFrom);
	DDX_Control(pDX, IDC_CMB_TASKS_ASSIGN_TO		, m_cmbAssignTo);
	DDX_Control(pDX, IDC_EDB_TASKS_DESCRIPTION		, m_edbDescription);

	DDX_Control(pDX, IDOK, m_btnOK);
}

void CTasksDialog::SetTextsLimit()
{
	m_edbName.LimitText(CHAR_SIZE_64);
	m_edbDescription.LimitText(CHAR_SIZE_512);
}

void CTasksDialog::DisableAndHideControls()
{
	m_edbName.SetReadOnly(true);
	m_edbDescription.SetReadOnly(true);
	m_btnOK.ShowWindow(SW_HIDE);
}

BOOL CTasksDialog::SetDataToControls()
{
	LoadTaskPriorities();
	LoadTaskStates();
	LoadEmployees();

	m_edbName.SetWindowTextW(m_recRecord.szName);
	m_edbDescription.SetWindowTextW(m_recRecord.szDescription);

	return TRUE;
}

BOOL CTasksDialog::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;
	if (theApp.GetCurrentUser().GetAccessLevel() == EmployeeAccessLevelTeamLeader)
	{
		m_edbName.SetReadOnly(true);
		m_edbDescription.SetReadOnly(true);
	}

	return TRUE;
}

void CTasksDialog::GetDataFormControls()
{
	CString strTextHelper;
	long lIndexHelper = 0;

	// Име
	m_edbName.GetWindowTextW(strTextHelper);
	wcscpy_s(m_recRecord.szName, strTextHelper);

	// Приоритет
	lIndexHelper = m_cmbPriority.GetCurSel();
	m_recRecord.lPriorityID = m_cmbPriority.GetItemData(lIndexHelper);

	// Състояние
	lIndexHelper = m_cmbState.GetCurSel();
	m_recRecord.lStateID = m_cmbState.GetItemData(lIndexHelper);

	// Назначена от
	lIndexHelper = m_cmbAssignFrom.GetCurSel();
	m_recRecord.lAssignFromID = m_cmbAssignFrom.GetItemData(lIndexHelper);

	// Назначена на
	lIndexHelper = m_cmbAssignTo.GetCurSel();
	m_recRecord.lAssignToID = m_cmbAssignTo.GetItemData(lIndexHelper);

	// Описание
	m_edbDescription.GetWindowTextW(strTextHelper);
	wcscpy_s(m_recRecord.szDescription, strTextHelper);
}

BOOL CTasksDialog::Validate()
{
	if (!ValidateMandatoryField(m_recRecord.szName, _T("заглавие")))
		return FALSE;

	if (m_recRecord.lAssignFromID == m_recRecord.lAssignToID)
	{
		MessageBox(gl_strErrorIncorrectTaskAssigning, gl_strError, MB_ICONERROR);
		return FALSE;
	}


	return TRUE;
}

// Methods
// ----------------

void CTasksDialog::LoadTaskPriorities()
{
	long lIndexHelper = 0;

	if (m_eRecordAction == RecordsActionView || theApp.GetCurrentUser().GetAccessLevel() == EmployeeAccessLevelTeamLeader)
	{
		for (INT_PTR i = 0; i < m_oTaskPrioritiesArray.GetCount(); i++, lIndexHelper++)
		{
			TASK_PRIORITIES* pPriority = m_oTaskPrioritiesArray.GetAt(i);
			if (pPriority == NULL)
			{
				MessageBox(gl_strErrorFailedToLoadTaskPriorities, gl_strError, MB_ICONERROR);
				__super::OnCancel();
			}

			if (m_recRecord.lPriorityID != pPriority->lID)
				continue;

			lIndexHelper = m_cmbPriority.AddString(pPriority->szName);
			m_cmbPriority.SetItemData(lIndexHelper, pPriority->lID);
			break;
		}

		m_cmbPriority.SetCurSel(ZERO);
	}
	else
	{
		for (INT_PTR i = 0; i < m_oTaskPrioritiesArray.GetCount(); i++, lIndexHelper++)
		{
			TASK_PRIORITIES* pPriority = m_oTaskPrioritiesArray.GetAt(i);
			if (pPriority == NULL)
			{
				MessageBox(gl_strErrorFailedToLoadTaskPriorities, gl_strError, MB_ICONERROR);
				__super::OnCancel();
			}

			lIndexHelper = m_cmbPriority.AddString(pPriority->szName);
			m_cmbPriority.SetItemData(lIndexHelper, pPriority->lID);

			if (m_recRecord.lPriorityID == pPriority->lID)
				m_cmbPriority.SetCurSel(lIndexHelper);
		}
	}
}

void CTasksDialog::LoadTaskStates()
{
	long lIndexHelper = 0;

	if (m_eRecordAction == RecordsActionView)
	{
		for (INT_PTR i = 0; i < m_oTaskStatesArray.GetCount(); i++, lIndexHelper++)
		{
			TASK_STATES* pTaskState = m_oTaskStatesArray.GetAt(i);
			if (pTaskState == NULL)
			{
				MessageBox(gl_strErrorFailedToLoadTaskStates, gl_strError, MB_ICONERROR);
				__super::OnCancel();
			}

			if (m_recRecord.lStateID != pTaskState->lID)
				continue;

			lIndexHelper = m_cmbState.AddString(pTaskState->szName);
			m_cmbState.SetItemData(lIndexHelper, pTaskState->lID);
			break;
		}

		m_cmbState.SetCurSel(ZERO);
	}
	else
	{
		for (long i = 0; i < m_oTaskStatesArray.GetCount(); i++, lIndexHelper++)
		{
			TASK_STATES* pTaskState = m_oTaskStatesArray.GetAt(i);
			if (pTaskState == NULL)
			{
				MessageBox(gl_strErrorFailedToLoadTaskStates, gl_strError, MB_ICONERROR);
				__super::OnCancel();
			}

			m_cmbState.AddString(pTaskState->szName);
			m_cmbState.SetItemData(lIndexHelper, pTaskState->lID);

			if (m_recRecord.lStateID == pTaskState->lID)
				m_cmbState.SetCurSel(lIndexHelper);
		}
	} // if
}

void CTasksDialog::LoadEmployees()
{
	long lIndexHelper = 0, lIndexAssignFrom = 0, lIndexAssignTo = 0;
	CString strTextHelper;

	BOOL bFirstComboLoaded = FALSE; // за да не се зареждат всички записи

	if (m_eRecordAction == RecordsActionView || theApp.GetCurrentUser().GetAccessLevel() == EmployeeAccessLevelTeamLeader)
	{
		for (INT_PTR i = 0; i < m_oEmployeesArray.GetCount(); i++)
		{
			EMPLOYEES* pEmployee = m_oEmployeesArray.GetAt(i);
			if (pEmployee == NULL)
			{
				MessageBox(gl_strErrorFailedToLoadEmployees, gl_strError, MB_ICONERROR);
				__super::OnCancel();
			}

			if (m_recRecord.lAssignFromID == pEmployee->lID)
			{
				strTextHelper.Format(_T("%s, %s, %s"), pEmployee->szFirstName, pEmployee->szMiddleName, pEmployee->szLastName);

				m_cmbAssignFrom.AddString(strTextHelper);
				m_cmbAssignFrom.SetItemData(lIndexAssignFrom, pEmployee->lID);

				lIndexAssignFrom++;

				if (bFirstComboLoaded)
					break;
				else bFirstComboLoaded = TRUE;

				continue;
			}

			if (m_recRecord.lAssignToID == pEmployee->lID)
			{
				strTextHelper.Format(_T("%s, %s, %s"), pEmployee->szFirstName, pEmployee->szMiddleName, pEmployee->szLastName);

				m_cmbAssignTo.AddString(strTextHelper);
				m_cmbAssignTo.SetItemData(lIndexAssignTo, pEmployee->lID);

				lIndexAssignTo++;

				if (bFirstComboLoaded)
					break;
				else bFirstComboLoaded = TRUE;
			}
		} // for

		m_cmbAssignFrom.SetCurSel(ZERO);
		m_cmbAssignTo.SetCurSel(ZERO);
	}
	else
	{
		for (long i = 0; i < m_oEmployeesArray.GetCount(); i++, lIndexHelper++)
		{
			EMPLOYEES* pEmployee = m_oEmployeesArray.GetAt(i);
			if (pEmployee == NULL)
			{
				MessageBox(gl_strErrorFailedToLoadEmployees, gl_strError, MB_ICONERROR);
				__super::OnCancel();
			}

			strTextHelper.Format(_T("%s, %s, %s"), pEmployee->szFirstName, pEmployee->szMiddleName, pEmployee->szLastName);

			lIndexHelper = m_cmbAssignFrom.AddString(strTextHelper);
			m_cmbAssignFrom.SetItemData(lIndexHelper, pEmployee->lID);

			if (m_recRecord.lAssignFromID == pEmployee->lID)
				m_cmbAssignFrom.SetCurSel(lIndexHelper);

			m_cmbAssignTo.AddString(strTextHelper);
			m_cmbAssignTo.SetItemData(lIndexHelper, pEmployee->lID);

			if (m_recRecord.lAssignToID == pEmployee->lID)
				m_cmbAssignTo.SetCurSel(lIndexHelper);
		}
	} // if
}
