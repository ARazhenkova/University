
// LoginDialog.h
//

#pragma once

#include "SmartDialog.h"
#include "Resource.h"
#include "Employees.h"

/////////////////////////////////////////////////////////////////////////////
// CLoginDialog

/// <summary> Диалог за вход в системата. </summary>
class CLoginDialog : public CSmartDialog<EMPLOYEES>
{
	// Macros
	// ----------------

	DECLARE_DYNAMIC(CLoginDialog)

	// Constants
	// ----------------

private:

	enum { IDD = IDD_LOGIN_DIALOG };

	// Constructor / Destructor
	// ----------------

public:

	/// <summary> Контруктор. </summary>
	/// <param name="recEmployee"> Служител. </param>
	CLoginDialog(EMPLOYEES& recEmployee);

	/// <summary> Деструктор. </summary>
	virtual ~CLoginDialog();

	// Overrides
	// ----------------

private:

	/// <summary> При инициализиране на диалога. </summary>
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	BOOL OnInitDialog() override;

	/// <summary> Асоцииране на вътрешните променливи с ID-то на контролите. </summary>
	void DoDataExchange(CDataExchange* pDX) override;

	/// <summary> При натискане на бутона "Потвърди". </summary>
	void OnOK() override;

	/// <summary> Задаване на лимит на текстовите полета. </summary>
	void SetTextsLimit() override;

	/// <summary> Зареждане на данните от контролите. </summary>
	void GetDataFormControls() override;

	/// <summary> Валидиране на данните. </summary>
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	BOOL Validate() override;

	// Methods
	// ----------------


	// Members
	// ----------------

public:

	/// <summary> Влезлият в системата служител. </summary>
	EMPLOYEES& m_recEmployee;

	/// <summary> ЕГН. </summary>
	CEdit m_edbIdentifier;

	/// <summary> Парола. </summary>
	CEdit m_edbPassword;

	CButton m_btnOK;
};
