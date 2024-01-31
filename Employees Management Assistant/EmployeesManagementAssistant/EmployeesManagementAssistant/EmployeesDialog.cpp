
// EmployeesDialog.cpp
//

#include "pch.h"
#include "EmployeesManagementAssistant.h"
#include "EmployeesDialog.h"
#include "Encryption.h"
#include "Resource.h"

/////////////////////////////////////////////////////////////////////////////
// CEmployeesDialog

IMPLEMENT_DYNAMIC(CEmployeesDialog, CDialog)

// Constructor / Destructor
// ----------------

CEmployeesDialog::CEmployeesDialog(EMPLOYEES& recEmployee, const RecordsActions& eRecordAction)
	: CSmartDialog(IDD, recEmployee, eRecordAction)
{
}

CEmployeesDialog::~CEmployeesDialog()
{
}

// Overrides
// ----------------

void CEmployeesDialog::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDB_EMPLOYEES_PERSONAL_KEY, m_edbPersonalKey);
	DDX_Control(pDX, IDC_CMB_EMPLOYEES_STATUS			, m_cmbStatus);
	DDX_Control(pDX, IDC_CMB_EMPLOYEES_ACCESS_LEVEL		, m_cmbAccessLevel);
	DDX_Control(pDX, IDC_EDB_EMPLOYEES_PASSWORD			, m_edbPassword);

	DDX_Control(pDX, IDC_EDB_EMPLOYEES_FIRST_NAME		, m_edbFirstName);
	DDX_Control(pDX, IDC_EDB_EMPLOYEES_MIDDLE_NAME		, m_edbMiddleName);
	DDX_Control(pDX, IDC_EDB_EMPLOYEES_LAST_NAME		, m_edbLastName);
	DDX_Control(pDX, IDC_EDB_EMPLOYEES_IDENTIFIER		, m_edbIdentifier);
	DDX_Control(pDX, IDC_EDB_EMPLOYEES_SALARY			, m_edbSalary);

	DDX_Control(pDX, IDC_EDB_EMPLOYEES_PERSONAL_PHONE_NUMBER, m_edbPersonalPhoneNumber);
	DDX_Control(pDX, IDC_EDB_EMPLOYEES_BUSINESS_PHONE_NUMBER, m_edbBusinessPhoneNumber);
	DDX_Control(pDX, IDC_EDB_EMPLOYEES_EMAIL_ADDRESS	, m_edbEmailAddress);

	DDX_Control(pDX, IDC_EDB_EMPLOYEES_HOME_ADDRESS		, m_edbHomeAddress);
	DDX_Control(pDX, IDC_EDB_EMPLOYEES_WORK_ADDRESS		, m_edbWorkAddress);

	DDX_Control(pDX, IDOK, m_btnOK);
}

void CEmployeesDialog::SetTextsLimit()
{  
	m_edbPassword.LimitText(CHAR_SIZE_128);
	m_edbFirstName.LimitText(CHAR_SIZE_64);
	m_edbMiddleName.LimitText(CHAR_SIZE_64);
	m_edbLastName.LimitText(CHAR_SIZE_64);
	m_edbIdentifier.LimitText(CHAR_SIZE_10);
}

void CEmployeesDialog::DisableAndHideControls()
{
	m_edbPassword.SetReadOnly(true);

	m_edbFirstName.SetReadOnly(true);
	m_edbMiddleName.SetReadOnly(true);
	m_edbLastName.SetReadOnly(true);
	m_edbIdentifier.SetReadOnly(true);
	m_edbSalary.SetReadOnly(true);

	m_edbPersonalPhoneNumber.SetReadOnly(true);
	m_edbBusinessPhoneNumber.SetReadOnly(true);
	m_edbEmailAddress.SetReadOnly(true);

	m_edbHomeAddress.SetReadOnly(true);
	m_edbWorkAddress.SetReadOnly(true);

	m_btnOK.ShowWindow(SW_HIDE);
}

BOOL CEmployeesDialog::SetDataToControls()
{
	m_edbPersonalKey.SetWindowTextW(m_recRecord.szPersonalKey);

	LoadStatuses();
	LoadAccessLevels();

	m_edbFirstName.SetWindowTextW(m_recRecord.szFirstName);
	m_edbMiddleName.SetWindowTextW(m_recRecord.szMiddleName);
	m_edbLastName.SetWindowTextW(m_recRecord.szLastName);
	m_edbIdentifier.SetWindowTextW(m_recRecord.szIdentifier);
	m_edbSalary.SetWindowTextW(CConvertToString::Convert(m_recRecord.dSalary, SALARY_PRECISION));

	m_edbPersonalPhoneNumber.SetWindowTextW(m_recRecord.szPersonalPhoneNumber);
	m_edbBusinessPhoneNumber.SetWindowTextW(m_recRecord.szBusinessPhoneNumber);
	m_edbEmailAddress.SetWindowTextW(m_recRecord.szEmailAddress);

	m_edbHomeAddress.SetWindowTextW(m_recRecord.szHomeAddress);
	m_edbWorkAddress.SetWindowTextW(m_recRecord.szWorkAddress);

	return TRUE;
}

void CEmployeesDialog::GetDataFormControls()
{
	CString strTextHelper;
	int lIndexHelper = 0;

	// Статус
	lIndexHelper = m_cmbStatus.GetCurSel();
	m_recRecord.sStatus = m_cmbStatus.GetItemData(lIndexHelper);

	// Ниво на достъп
	lIndexHelper = m_cmbAccessLevel.GetCurSel();
	m_recRecord.sAccessLevel = m_cmbAccessLevel.GetItemData(lIndexHelper);

	// Име
	m_edbFirstName.GetWindowTextW(strTextHelper);
	wcscpy_s(m_recRecord.szFirstName, strTextHelper);

	// Презиме
	m_edbMiddleName.GetWindowTextW(strTextHelper);
	wcscpy_s(m_recRecord.szMiddleName, strTextHelper);

	// Фамилия
	m_edbLastName.GetWindowTextW(strTextHelper);
	wcscpy_s(m_recRecord.szLastName, strTextHelper);

	// ЕГН
	m_edbIdentifier.GetWindowTextW(strTextHelper);
	wcscpy_s(m_recRecord.szIdentifier, strTextHelper);

	// Уникален ключ на потребителя
	if (m_eRecordAction == RecordsActionInsert)
	{
		strTextHelper = theApp.GetCurrentUser().PreparePersonalKey(m_recRecord.szIdentifier);
		wcscpy_s(m_recRecord.szPersonalKey, strTextHelper);
	}

	// Парола
	m_edbPassword.GetWindowTextW(m_strPasswordHelper);

	// Месечна заплата
	m_edbSalary.GetWindowTextW(strTextHelper);
	m_recRecord.dSalary = _ttof(strTextHelper);

	// Личен телефонен номер
	m_edbPersonalPhoneNumber.GetWindowTextW(strTextHelper);
	wcscpy_s(m_recRecord.szPersonalPhoneNumber, strTextHelper);

	// Служебен телефонен номер
	m_edbBusinessPhoneNumber.GetWindowTextW(strTextHelper);
	wcscpy_s(m_recRecord.szBusinessPhoneNumber, strTextHelper);

	// Имейл адрес
	m_edbEmailAddress.GetWindowTextW(strTextHelper);
	wcscpy_s(m_recRecord.szEmailAddress, strTextHelper);

	// Адрес на местоживеене
	m_edbHomeAddress.GetWindowTextW(strTextHelper);
	wcscpy_s(m_recRecord.szHomeAddress, strTextHelper);

	// Адрес на работното място
	m_edbWorkAddress.GetWindowTextW(strTextHelper);
	wcscpy_s(m_recRecord.szWorkAddress, strTextHelper);
}

BOOL CEmployeesDialog::Validate()
{
	// Парола
	if (!m_strPasswordHelper.IsEmpty())
	{
		if (_tcslen(m_strPasswordHelper) < CHAR_SIZE_8)
		{
			MessageBox(gl_strErrorIncorrectPasswordLength, gl_strError, MB_ICONERROR);
			return FALSE;
		}

		TCHAR szPasswordHelper[CHAR_SIZE_128 + 1];
		wcscpy_s(szPasswordHelper, m_strPasswordHelper);

		CString strNewPassword = _T("");
		if (!CEncryption::PBKDF2Hashing(szPasswordHelper, m_recRecord.szPersonalKey, strNewPassword))
			return FALSE;

		wcscpy_s(m_recRecord.szPassword, strNewPassword);
	}

	if (!ValidateMandatoryField(m_recRecord.szPassword, _T("парола")))
		return FALSE;

	if (!ValidateMandatoryField(m_recRecord.szFirstName, _T("име"))
		|| !ValidateTextOnly(m_recRecord.szFirstName, _T("име")))
		return FALSE;

	if (!ValidateMandatoryField(m_recRecord.szMiddleName, _T("презиме"))
		|| !ValidateTextOnly(m_recRecord.szMiddleName, _T("презиме")))
		return FALSE;

	if (!ValidateMandatoryField(m_recRecord.szLastName, _T("фамилия"))
		|| !ValidateTextOnly(m_recRecord.szLastName, _T("фамилия")))
		return FALSE;

	if (!ValidateMandatoryField(m_recRecord.szIdentifier, _T("ЕГН"))
		|| !ValidateIdentifier(m_recRecord.szIdentifier))
		return FALSE;

	if (!ValidateEmailAddress(m_recRecord.szEmailAddress))
		return FALSE;

	return TRUE;
}

void CEmployeesDialog::AfterValidation()
{
	if (m_recRecord.sStatus == EmployeeStatusActive && m_recRecord.sFailedLoginAttempts == ALLOWED_LOGIN_ATTEMPTS)
		m_recRecord.sFailedLoginAttempts = 0;
}

// Methods
// ----------------

void CEmployeesDialog::LoadStatuses()
{
	if (m_eRecordAction == RecordsActionView)
	{
		m_cmbStatus.AddString(CEmployeeStatus::GetText(m_recRecord.sStatus));
		m_cmbStatus.SetItemData(m_recRecord.sStatus, m_recRecord.sStatus);

		m_cmbStatus.SetCurSel(ZERO);
	}
	else
	{
		for (int i = 1; i < EMPLOYEES_STATUSES_COUNT; i++)
		{
			m_cmbStatus.AddString(CEmployeeStatus::GetText(i));
			m_cmbStatus.SetItemData(i - 1, i);

			if (m_recRecord.sStatus == i)
				m_cmbStatus.SetCurSel(i - 1);
		}

		if (m_eRecordAction == RecordsActionInsert)
			m_cmbStatus.SetCurSel(ZERO);
	} // if
}

void CEmployeesDialog::LoadAccessLevels()
{
	if (m_eRecordAction == RecordsActionView)
	{
		m_cmbAccessLevel.AddString(CEmployeeAccessLevel::GetText(m_recRecord.sAccessLevel));
		m_cmbAccessLevel.SetItemData(m_recRecord.sAccessLevel, m_recRecord.sAccessLevel);

		m_cmbAccessLevel.SetCurSel(ZERO);
	}
	else
	{
		for (int i = 1; i < EMPLOYEES_ACCESS_LEVELS_COUNT; i++)
		{
			m_cmbAccessLevel.AddString(CEmployeeAccessLevel::GetText(i));
			m_cmbAccessLevel.SetItemData(i - 1, i);

			if (m_recRecord.sAccessLevel == i)
				m_cmbAccessLevel.SetCurSel(i - 1);
		}

		if (m_eRecordAction == RecordsActionInsert)
			m_cmbAccessLevel.SetCurSel(ZERO);
	} // if
}
