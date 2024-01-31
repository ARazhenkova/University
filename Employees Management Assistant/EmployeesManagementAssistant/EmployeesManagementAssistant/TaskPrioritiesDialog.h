
// TasksDialog.h
//

#pragma once

#include "SmartDialog.h"
#include "Resource.h"
#include "TaskPriorities.h"

/////////////////////////////////////////////////////////////////////////////
// CTaskPrioritiesDialog

/// <summary> Диалог за приоритети на задача. </summary>
class CTaskPrioritiesDialog : public CSmartDialog<TASK_PRIORITIES>
{
	// Macros
	// ----------------

	DECLARE_DYNAMIC(CTaskPrioritiesDialog)

	// Constants
	// ----------------

private:

	enum { IDD = IDD_TASK_PRIORITIES_DIALOG };

	// Constructor / Destructor
	// ----------------

public:

	/// <summary> Контруктор. </summary>
	/// <param name="recTaskPriority"> Запис. </param>
	/// <param name="oTaskPrioritiesArray"> Вече въведените приоритети. </param>
	/// <param name="eRecordAction"> Действия със записи. </param>
	CTaskPrioritiesDialog(TASK_PRIORITIES& recTaskPriority
		, CTaskPrioritiesArray& oTaskPrioritiesArray
		, const RecordsActions& eRecordAction);

	/// <summary> Деструктор. </summary>
	virtual ~CTaskPrioritiesDialog();

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

	/// <summary> Зареждане на нивата на приоритет. </summary>
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	BOOL LoadLevels();

	// Members
	// ----------------

private:

	/// <summary> Вече въведените приоритети. </summary>
	CTaskPrioritiesArray& m_oTaskPrioritiesArray;

	/// <summary> Име. </summary>
	CEdit m_edbName;

	/// <summary> Нива. </summary>
	CComboBox m_cmbLevels;

	CButton m_btnOK;
};
