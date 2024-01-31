
// LoginDialog.cpp
//

#include "pch.h"
#include "LoginDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CLoginDialog

IMPLEMENT_DYNAMIC(CLoginDialog, CDialog)

// Constructor / Destructor
// ----------------

CLoginDialog::CLoginDialog(EMPLOYEES& recEmployee) : CSmartDialog(IDD, recEmployee, (RecordsActions)0)
	, m_recEmployee(recEmployee)
{
}

CLoginDialog::~CLoginDialog()
{
}

// Overrides
// ----------------

BOOL CLoginDialog::OnInitDialog()
{
	__super::OnInitDialog();

	SetTextsLimit();

	return TRUE;
}

void CLoginDialog::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDB_LOGIN_IDENTIFIER	, m_edbIdentifier);
	DDX_Control(pDX, IDC_EDB_LOGIN_PASSWORD		, m_edbPassword);
	DDX_Control(pDX, IDOK, m_btnOK);
}

void CLoginDialog::OnOK()
{
	GetDataFormControls();

	if (!Validate())
		return;

	CDialog::OnOK();
}

void CLoginDialog::SetTextsLimit()
{
	m_edbIdentifier.LimitText(CHAR_SIZE_10);
	m_edbPassword.LimitText(CHAR_SIZE_128);
}

void CLoginDialog::GetDataFormControls()
{
	CString strTextHelper;

	// Име
	m_edbIdentifier.GetWindowTextW(strTextHelper);
	wcscpy_s(m_recEmployee.szIdentifier, strTextHelper);

	// Парола
	m_edbPassword.GetWindowTextW(strTextHelper);
	wcscpy_s(m_recEmployee.szPassword, strTextHelper);
}

BOOL CLoginDialog::Validate()
{
	if (!ValidateMandatoryField(m_recEmployee.szIdentifier, _T("ЕГН"))
		|| !ValidateIdentifier(m_recEmployee.szIdentifier))
		return FALSE;

	if (!ValidateMandatoryField(m_recEmployee.szPassword, _T("парола")))
		return FALSE;

	if (_tcslen(m_recEmployee.szPassword) < CHAR_SIZE_8)
	{
		MessageBox(gl_strErrorIncorrectCredentials, gl_strError, MB_ICONERROR);
		return FALSE;
	}

	return TRUE;
}

// Methods
// ----------------
