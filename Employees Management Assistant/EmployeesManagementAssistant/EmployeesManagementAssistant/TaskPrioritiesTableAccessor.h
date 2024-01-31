
// TaskPrioritiesTableAccessor.h
//

#pragma once

#include "SmartTable.h"
#include "TaskPriorities.h"

/////////////////////////////////////////////////////////////////////////////
// CTasksDataAccessor

/// <summary> Достъпване на таблицата на състояния на задача. </summary>
class CTaskPrioritiesDataAccessor
{
	// Macros
	// ----------------

	BEGIN_ACCESSOR_MAP(CTaskPrioritiesDataAccessor, 2)
		BEGIN_ACCESSOR(ID_ACCESSOR, true)
			COLUMN_ENTRY(TableColumnID					, m_recTaskPriority.lID)
		END_ACCESSOR()
		BEGIN_ACCESSOR(DATA_ACCESSOR, true)
			COLUMN_ENTRY(TableColumnUpdateCounter		, m_recTaskPriority.lUpdateCounter)
			COLUMN_ENTRY(TableColumnName				, m_recTaskPriority.szName)
			COLUMN_ENTRY(TableColumnLevel				, m_recTaskPriority.sLevel)
		END_ACCESSOR()
	END_ACCESSOR_MAP()

	// Constants
	// ----------------

private:

	enum TableColumns
	{
		TableColumnID = 1,
		TableColumnUpdateCounter,
		TableColumnName,
		TableColumnLevel,
	};

	// Constructor / Destructor
	// ----------------


	// Overrides
	// ----------------


	// Methods
	// ----------------


	// Members
	// ----------------

protected:

	/// <summary> Данни за приоритет на задача. </summary>
	TASK_PRIORITIES m_recTaskPriority;
};

/////////////////////////////////////////////////////////////////////////////
// CTasksTableAccessor

/// <summary> Таблица на приоритети на задача. </summary>
class CTaskPrioritiesTableAccessor : public CSmartTable<CTaskPrioritiesDataAccessor, TASK_PRIORITIES>
{
	// Macros
	// ----------------


	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------

public:

	/// <summary> Контруктор. </summary>
	CTaskPrioritiesTableAccessor();

	/// <summary> Деструктор. </summary>
	virtual ~CTaskPrioritiesTableAccessor();

	// Overrides
	// ----------------

private:

	/// <summary> Вземане на името на таблицата. </summary>
	/// <returns> Името на таблицата. </returns>
	const CString GetTableName() const override;

	/// <summary> Вземене на аксесора. </summary>
	/// <returns> Данните. </returns>
	TASK_PRIORITIES& GetAccessor() override;

	/// <summary> Вземане на идентификатора на записа. </summary>
	/// <param name="recTaskPriority"> Записa. </param>	
	/// <returns> Идентификаторът на записа. </returns>
	const long GetRecordID(const TASK_PRIORITIES& recTaskPriority) const override;

	/// <summary> Вземане на името на брояча на промени. </summary>
	/// <param name="recTaskPriority"> Записа, от който се взема брояча на промени. </param>	
	/// <returns> Броячът на промени. </returns>
	const long GetUpdateCounter(const TASK_PRIORITIES& recTaskPriority) const override;

	/// <summary> Увеличаване на брояча на промени. </summary>
	void IncrementUpdateCounter(TASK_PRIORITIES& recTaskPriority) override;

	// Methods
	// ----------------


	// Members
	// ----------------

};
