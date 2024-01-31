
// TaskStatesDialog.h
//

#pragma once

#include "SmartDialog.h"
#include "Resource.h"
#include "TaskStates.h"

/////////////////////////////////////////////////////////////////////////////
// CTaskStatesDialog

/// <summary> Диалог за състояния на задача. </summary>
class CTaskStatesDialog : public CSmartDialog<TASK_STATES>
{
	// Macros
	// ----------------

	DECLARE_DYNAMIC(CTaskStatesDialog)

	// Constants
	// ----------------

private:

	enum { IDD = IDD_TASK_STATES_DIALOG };

	// Constructor / Destructor
	// ----------------

public:

	/// <summary> Контруктор. </summary>
	/// <param name="recTaskState"> Запис. </param>
	/// <param name="eRecordAction"> Действия със записи. </param>
	CTaskStatesDialog(TASK_STATES& recTaskState, const RecordsActions& eRecordAction);

	/// <summary> Деструктор. </summary>
	virtual ~CTaskStatesDialog();

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


	// Members
	// ----------------

private:

	/// <summary> Име. </summary>
	CEdit m_edbName;

	/// <summary> Дали да се архивира записа при това състояние. </summary>
	CButton m_chbIsForArchive;

	CButton m_btnOK;
};
