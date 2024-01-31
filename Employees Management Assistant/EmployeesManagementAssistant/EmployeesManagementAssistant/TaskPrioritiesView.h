
// TaskPrioritiesView.h
//

#pragma once

#include "SmartView.h"
#include "TaskPrioritiesDocument.h"

/////////////////////////////////////////////////////////////////////////////
// CTaskPrioritiesView

/// <summary> View за приоритети на задача. </summary>
class CTaskPrioritiesView : public CSmartView<CTaskPrioritiesDocument, TASK_PRIORITIES>
{
	// Macros
	// ----------------

	DECLARE_DYNCREATE(CTaskPrioritiesView)
	DECLARE_MESSAGE_MAP()

	// Constants
	// ----------------

private:

	/// <summary> Индекси на колоните. </summary>
	enum ColumnIndexes
	{
		ColumnIndexName = 0,
		ColumnIndexLevel,
	};

	// Constructor / Destructor
	// ----------------

public:

	/// <summary> Контруктор. </summary>
	CTaskPrioritiesView();

	/// <summary> Деструктор. </summary>
	virtual ~CTaskPrioritiesView();

	// Overrides
	// ----------------

private:

	/// <summary> Добавяне на заглавни редове във View-то. </summary>
	BOOL SetColumnsHeader() override;

	/// <summary> Визуализиране на данни по колоните във View-то. </summary>
	/// <param name="lRecordIndex"> Номерът на елемента. </param>	
	/// <param name="recTaskPriority"> Запис за визуализиране. </param>	
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	BOOL SetItem(const long lRecordIndex, const TASK_PRIORITIES& recTaskPriority) override;

	/// <summary> Вземане на идентификатора на записа. </summary>
	/// <param name="recTaskPriority"> Записa. </param>	
	/// <returns> Идентификаторът на записа. </returns>
	const long GetRecordID(const TASK_PRIORITIES& recTaskPriority) const override;

	/// <summary> Вземане на идентификатора на записа. </summary>
	/// <param name="recTaskPriority"> Записa. </param>	
	/// <param name="RecordsAction"> Действие със записa. </param>	
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	BOOL OpenDialog(TASK_PRIORITIES& recTaskPriority, const RecordsActions RecordsAction) override;

	// Methods
	// ----------------


	// Members
	// ----------------

};

