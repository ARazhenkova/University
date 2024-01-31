
// TaskPrioritiesDialog.cpp
//

#include "pch.h"
#include "EmployeesManagementAssistant.h"
#include "TaskPrioritiesDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CTaskPrioritiesDialog

IMPLEMENT_DYNAMIC(CTaskPrioritiesDialog, CDialog)

// Constructor / Destructor
// ----------------

CTaskPrioritiesDialog::CTaskPrioritiesDialog(TASK_PRIORITIES& recTaskPriority
	, CTaskPrioritiesArray& oTaskPrioritiesArray
	, const RecordsActions& eRecordAction)
	: CSmartDialog(IDD, recTaskPriority, eRecordAction)
	, m_oTaskPrioritiesArray(oTaskPrioritiesArray)
{
}

CTaskPrioritiesDialog::~CTaskPrioritiesDialog()
{
}

// Overrides
// ----------------

void CTaskPrioritiesDialog::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDB_TASK_PRIORITIES_NAME, m_edbName);
	DDX_Control(pDX, IDC_CMB_TASK_PRIORITIES_LEVEL, m_cmbLevels);
	DDX_Control(pDX, IDOK, m_btnOK);
}

void CTaskPrioritiesDialog::SetTextsLimit()
{
	m_edbName.LimitText(CHAR_SIZE_64);
}

void CTaskPrioritiesDialog::DisableAndHideControls()
{
	m_edbName.SetReadOnly(true);
	m_btnOK.ShowWindow(SW_HIDE);
}

BOOL CTaskPrioritiesDialog::SetDataToControls()
{
	m_edbName.SetWindowTextW(m_recRecord.szName);

	if (LoadLevels())
		return FALSE;

	return TRUE;
}

void CTaskPrioritiesDialog::GetDataFormControls()
{
	CString strTextHelper;

	// Име
	m_edbName.GetWindowTextW(strTextHelper);
	wcscpy_s(m_recRecord.szName, strTextHelper);

	// Ниво
	long lIndexHelper = m_cmbLevels.GetCurSel();
	m_recRecord.sLevel = m_cmbLevels.GetItemData(lIndexHelper);
}

BOOL CTaskPrioritiesDialog::Validate()
{
	if (!ValidateMandatoryField(m_recRecord.szName, _T("заглавие")))
		return FALSE;

	return TRUE;
}

// Methods
// ----------------

BOOL CTaskPrioritiesDialog::LoadLevels()
{
	if (m_eRecordAction == RecordsActionView)
	{
		m_cmbLevels.AddString(CConvertToString::Convert(m_recRecord.sLevel));
		m_cmbLevels.SetItemData(ZERO, m_recRecord.sLevel);

		m_cmbLevels.SetCurSel(ZERO);
	}
	else
	{
		BOOL bIsPriorityLevelAlreadyExist = FALSE;
		for (short i = 1, k = 0; i <= 99; i++)
		{
			for (INT_PTR j = 0; j < m_oTaskPrioritiesArray.GetCount(); j++)
			{
				TASK_PRIORITIES* pPriorities = m_oTaskPrioritiesArray.GetAt(j);
				if (pPriorities == NULL)
					return FALSE;

				if (pPriorities->sLevel == i && pPriorities->sLevel != m_recRecord.sLevel)
				{
					bIsPriorityLevelAlreadyExist = TRUE;
					break;
				}
			}

			if (bIsPriorityLevelAlreadyExist)
			{
				bIsPriorityLevelAlreadyExist = FALSE;
				continue;
			}

			m_cmbLevels.AddString(CConvertToString::Convert(i));
			m_cmbLevels.SetItemData(k, i);

			if (m_recRecord.sLevel == i)
				m_cmbLevels.SetCurSel(k);

			k++;
		}

		if (m_eRecordAction == RecordsActionInsert)
			m_cmbLevels.SetCurSel(ZERO);
	} // if

	return TRUE;
}
