
// TasksView.h
//

#pragma once

#include "SmartView.h"
#include "TasksDocument.h"

/////////////////////////////////////////////////////////////////////////////
// CTasksView

/// <summary> View за задачи. </summary>
class CTasksView : public CSmartView<CTasksDocument, TASKS>
{
	// Macros
	// ----------------

	DECLARE_DYNCREATE(CTasksView)
	DECLARE_MESSAGE_MAP()

	// Constants
	// ----------------

private:

	/// <summary> Индекси на колоните. </summary>
	enum ColumnIndexes
	{
		ColumnIndexName = 0,
		ColumnIndexPriority,
		ColumnIndexState,
	};

	// Constructor / Destructor
	// ----------------

public:

	/// <summary> Контруктор. </summary>
	CTasksView();

	/// <summary> Деструктор. </summary>
	virtual ~CTasksView();

	// Overrides
	// ----------------

private:

	/// <summary> Добавяне на заглавни редове във View-то. </summary>
	BOOL SetColumnsHeader() override;

	/// <summary> Визуализиране на данни по колоните във View-то. </summary>
	/// <param name="lRecordIndex"> Номерът на елемента. </param>	
	/// <param name="recTask"> Запис за визуализиране. </param>	
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	BOOL SetItem(const long lRecordIndex, const TASKS& recTask) override;

	/// <summary> Вземане на идентификатора на записа. </summary>
	/// <param name="recTask"> Записa. </param>	
	/// <returns> Идентификаторът на записа. </returns>
	const long GetRecordID(const TASKS& recTask) const override;

	/// <summary> Вземане на идентификатора на записа. </summary>
	/// <param name="recTask"> Записa. </param>	
	/// <param name="RecordsAction"> Действие със записa. </param>	
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	BOOL OpenDialog(TASKS& recTask, const RecordsActions RecordsAction) override;

	// Methods
	// ----------------

	/// <summary> Подготвяне на приоритетите. </summary>
	/// <param name="oTaskPrioritiesArray"> Приоритети. </param>	
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	BOOL PrepareTaskPriorities(CTaskPrioritiesArray& oTaskPrioritiesArray);

	/// <summary> Подготвяне на състоянията. </summary>
	/// <param name="oTaskStatesArray"> Състояния. </param>	
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	BOOL PrepareTaskStates(CTaskStatesArray& oTaskStatesArray);

	/// <summary> Подготвяне на служителите. </summary>
	/// <param name="oEmployeesArray"> Служители. </param>	
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	BOOL PrepareEmployees(CEmployeesArray& oEmployeesArray);

	// Message Handlers
	// ----------------

	/// <summary> При натискане на добавяне от контекстното меню. </summary>
	afx_msg void OnUpdateCommandUIInsert(CCmdUI* pCmdUI);

	/// <summary> При натискане на редактиране от контекстното меню. </summary>
	afx_msg void OnUpdateCommandUIUpdate(CCmdUI* pCmdUI);

	/// <summary> При натискане на изтриване от контекстното меню. </summary>
	afx_msg void OnUpdateCommandUIDelete(CCmdUI* pCmdUI);

	// Members
	// ----------------

};

