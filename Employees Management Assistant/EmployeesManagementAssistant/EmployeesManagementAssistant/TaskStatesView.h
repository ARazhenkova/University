
// TaskStatesView.h
//

#pragma once

#include "SmartView.h"
#include "TaskStatesDocument.h"

/////////////////////////////////////////////////////////////////////////////
// CTaskStatesView

/// <summary> View за състояния на задача. </summary>
class CTaskStatesView : public CSmartView<CTaskStatesDocument, TASK_STATES>
{
	// Macros
	// ----------------

	DECLARE_DYNCREATE(CTaskStatesView)
	DECLARE_MESSAGE_MAP()

	// Constants
	// ----------------

private:

	/// <summary> Индекси на колоните. </summary>
	enum ColumnIndexes
	{
		ColumnIndexName = 0,
	};

	// Constructor / Destructor
	// ----------------

public:

	/// <summary> Контруктор. </summary>
	CTaskStatesView();

	/// <summary> Деструктор. </summary>
	virtual ~CTaskStatesView();

	// Overrides
	// ----------------

private:

	/// <summary> Добавяне на заглавни редове във View-то. </summary>
	BOOL SetColumnsHeader() override;

	/// <summary> Визуализиране на данни по колоните във View-то. </summary>
	/// <param name="lRecordIndex"> Номерът на елемента. </param>	
	/// <param name="recTaskState"> Запис за визуализиране. </param>	
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	BOOL SetItem(const long lRecordIndex, const TASK_STATES& recTaskState) override;

	/// <summary> Вземане на идентификатора на записа. </summary>
	/// <param name="recTaskState"> Записa. </param>	
	/// <returns> Идентификаторът на записа. </returns>
	const long GetRecordID(const TASK_STATES& recTaskState) const override;

	/// <summary> Вземане на идентификатора на записа. </summary>
	/// <param name="recTaskState"> Записa. </param>	
	/// <param name="RecordsAction"> Действие със записa. </param>	
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	BOOL OpenDialog(TASK_STATES& recTaskState, const RecordsActions RecordsAction) override;

	// Methods
	// ----------------


	// Members
	// ----------------

};

