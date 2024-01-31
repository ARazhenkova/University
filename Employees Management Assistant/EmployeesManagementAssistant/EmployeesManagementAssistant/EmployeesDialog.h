
// EmployeesDialog.h
//

#pragma once

#include "SmartDialog.h"
#include "Resource.h"
#include "Employees.h"

/////////////////////////////////////////////////////////////////////////////
// CEmployeesDialog

/// <summary> Диалог за служители. </summary>
class CEmployeesDialog : public CSmartDialog<EMPLOYEES>
{
	// Macros
	// ----------------

	DECLARE_DYNAMIC(CEmployeesDialog)

	// Constants
	// ----------------

private:

	enum { IDD = IDD_EMPLOYEES_DIALOG };

	// Constructor / Destructor
	// ----------------

public:

	/// <summary> Контруктор. </summary>
	/// <param name="recEmployee"> Запис. </param>
	/// <param name="eRecordAction"> Действия със записи. </param>
	CEmployeesDialog(EMPLOYEES& recEmployee, const RecordsActions& eRecordAction);

	/// <summary> Деструктор. </summary>
	virtual ~CEmployeesDialog();

	// Overrides
	// ----------------

private:

	/// <summary> Асоцииране на вътрешните променливи с ID-то на контролите. </summary>
	void DoDataExchange(CDataExchange* pDX) override;

	/// <summary> Задаване на лимит на текстовите полета. </summary>
	void SetTextsLimit() override;
	
	/// <summary> Засивяване и скриване на данните по контролите. </summary>
	void DisableAndHideControls() override;

	/// <summary> Зареждане на данните по контролите. </summary>
	BOOL SetDataToControls() override;

	/// <summary> Зареждане на данните от контролите. </summary>
	void GetDataFormControls() override;

	/// <summary> Валидиране на данните. </summary>
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	BOOL Validate() override;

	/// <summary> Действия след валидиране на данните. </summary>
	void AfterValidation() override;

	// Methods
	// ----------------

private:

	/// <summary> Зареждане на стаусите. </summary>
	void LoadStatuses();

	/// <summary> Зареждане на нивата на достъп. </summary>
	void LoadAccessLevels();

	// Members
	// ----------------

private:

	CString m_strPasswordHelper;

	/* СИСТЕМНИ ДАННИ */

	/// <summary> Уникален ключ на потребителя. </summary>
	CEdit m_edbPersonalKey;

	/// <summary> Статус. </summary>
	CComboBox m_cmbStatus; // EmployeeStatuses

	/// <summary> Ниво на достъп. </summary>
	CComboBox m_cmbAccessLevel; // EmploeeAccessLevels

	/// <summary> Парола. </summary>
	CEdit m_edbPassword;

	/// <summary> Брояч на неуспешните опити за влизане в системата. </summary>
	CEdit m_edbFailedLoginAttempts;

	/* ОСНОВНИ ДАННИ */

	/// <summary> Име. </summary>
	CEdit m_edbFirstName;

	/// <summary> Презиме. </summary>
	CEdit m_edbMiddleName;

	/// <summary> Фамилия. </summary>
	CEdit m_edbLastName;

	/// <summary> ЕГН. </summary>
	CEdit m_edbIdentifier;

	/// <summary> Месечна заплата. </summary>
	CEdit m_edbSalary;

	/// <summary> Личен телефонен номер. </summary>
	CEdit m_edbPersonalPhoneNumber;

	/// <summary> Служебен телефонен номер. </summary>
	CEdit m_edbBusinessPhoneNumber;

	/// <summary> Имейл адрес. </summary>
	CEdit m_edbEmailAddress;

	/// <summary> Адрес на местоживеене. </summary>
	CEdit m_edbHomeAddress;

	/// <summary> Адрес на работното място. </summary>
	CEdit m_edbWorkAddress;

	CButton m_btnOK;
};
