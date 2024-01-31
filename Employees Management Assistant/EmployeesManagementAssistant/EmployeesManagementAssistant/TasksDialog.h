
// TasksDialog.h
//

#pragma once

#include "SmartDialog.h"
#include "Resource.h"
#include "Tasks.h"
#include "TaskPriorities.h"
#include "TaskStates.h"
#include "Employees.h"

/////////////////////////////////////////////////////////////////////////////
// CTasksDialog

/// <summary> Диалог за задачи. </summary>
class CTasksDialog : public CSmartDialog<TASKS>
{
	// Macros
	// ----------------

	DECLARE_DYNAMIC(CTasksDialog)

	// Constants
	// ----------------

private:

	enum { IDD = IDD_TASKS_DIALOG };

	// Constructor / Destructor
	// ----------------

public:

	/// <summary> Контруктор. </summary>
	/// <param name="recTask"> Запис. </param>
	/// <param name="oTaskPrioritiesArray"> Приоритети. </param>
	/// <param name="oTaskStatesArray"> Състояния. </param>
	/// <param name="oEmployeesArray"> Служители. </param>
	/// <param name="eRecordAction"> Действия със записи. </param>
	CTasksDialog(TASKS& recTask
		, const CTaskPrioritiesArray& oTaskPrioritiesArray
		, const CTaskStatesArray& oTaskStatesArray
		, const CEmployeesArray& oEmployeesArray
		, const RecordsActions& eRecordAction);

	/// <summary> Деструктор. </summary>
	virtual ~CTasksDialog();

	// Overrides
	// ----------------

private:

	/// <summary> Асоцииране на вътрешните променливи с ID-то на контролите. </summary>
	void DoDataExchange(CDataExchange* pDX) override;

	/// <summary> Задаване на лимит на текстовите полета. </summary>
	void SetTextsLimit() override;

	/// <summary> Засивяване и скриване на данните по контролите. </summary>
	void DisableAndHideControls() override;

	/// <summary> При инициализиране на диалога. </summary>
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	BOOL OnInitDialog() override;

	/// <summary> Зареждане на данните по контролите. </summary>
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	BOOL SetDataToControls() override;

	/// <summary> Зареждане на данните от контролите. </summary>
	void GetDataFormControls() override;

	/// <summary> Валидиране на данните. </summary>
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	BOOL Validate() override;

	// Methods
	// ----------------

private:

	/// <summary> Зареждане на приоритетите в контола. </summary>
	void LoadTaskPriorities();

	/// <summary> Зареждане на състоянията в контола. </summary>
	void LoadTaskStates();

	/// <summary> Зареждане на служителите в контоли. </summary>
	void LoadEmployees();

	// Members
	// ----------------

private:

	/// <summary> Приоритети. </summary>
	const CTaskPrioritiesArray& m_oTaskPrioritiesArray;

	/// <summary> Състояния. </summary>
	const CTaskStatesArray& m_oTaskStatesArray;

	/// <summary> Служители. </summary>
	const CEmployeesArray& m_oEmployeesArray;

	/// <summary> Име. </summary>
	CEdit m_edbName;

	/// <summary> Приоритет. </summary>
	CComboBox m_cmbPriority;

	/// <summary> Състояние. </summary>
	CComboBox m_cmbState;

	/// <summary> Назначена от. </summary>
	CComboBox m_cmbAssignFrom;

	/// <summary> Назначена на. </summary>
	CComboBox m_cmbAssignTo;

	/// <summary> Описание. </summary>
	CEdit m_edbDescription;

	CButton m_btnOK;
};
