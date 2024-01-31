
// TaskStatesTableAccessor.h
//

#pragma once

#include "SmartTable.h"
#include "TaskStates.h"

/////////////////////////////////////////////////////////////////////////////
// CTasksDataAccessor

/// <summary> Достъпване на таблицата на приоритети на задача. </summary>
class CTaskStatesDataAccessor
{
	// Macros
	// ----------------

	BEGIN_ACCESSOR_MAP(CTaskStatesDataAccessor, 2)
		BEGIN_ACCESSOR(ID_ACCESSOR, true)
			COLUMN_ENTRY(TableColumnID					, m_recTaskState.lID)
		END_ACCESSOR()
		BEGIN_ACCESSOR(DATA_ACCESSOR, true)
			COLUMN_ENTRY(TableColumnUpdateCounter		, m_recTaskState.lUpdateCounter)
			COLUMN_ENTRY(TableColumnName				, m_recTaskState.szName)
			COLUMN_ENTRY(TableColumnIsForAchive			, m_recTaskState.sIsForAchive)
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
		TableColumnIsForAchive,
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

	/// <summary> Данни за състояние на задача. </summary>
	TASK_STATES m_recTaskState;
};

/////////////////////////////////////////////////////////////////////////////
// CTasksTableAccessor

/// <summary> Таблица на състояния на задача. </summary>
class CTaskStatesTableAccessor : public CSmartTable<CTaskStatesDataAccessor, TASK_STATES>
{
	// Macros
	// ----------------


	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------

public:

	/// <summary> Контруктор. </summary>
	CTaskStatesTableAccessor();

	/// <summary> Деструктор. </summary>
	virtual ~CTaskStatesTableAccessor();

	// Overrides
	// ----------------

private:

	/// <summary> Вземане на името на таблицата. </summary>
	/// <returns> Името на таблицата. </returns>
	const CString GetTableName() const override;

	/// <summary> Вземене на аксесора. </summary>
	/// <returns> Данните. </returns>
	TASK_STATES& GetAccessor() override;

	/// <summary> Вземане на идентификатора на записа. </summary>
	/// <param name="recTaskState"> Записa. </param>	
	/// <returns> Идентификаторът на записа. </returns>
	const long GetRecordID(const TASK_STATES& recTaskState) const override;

	/// <summary> Вземане на името на брояча на промени. </summary>
	/// <param name="recTaskState"> Записа, от който се взема брояча на промени. </param>	
	/// <returns> Броячът на промени. </returns>
	const long GetUpdateCounter(const TASK_STATES& recTaskState) const override;

	/// <summary> Увеличаване на брояча на промени. </summary>
	void IncrementUpdateCounter(TASK_STATES& recTaskState) override;

	// Methods
	// ----------------


	// Members
	// ----------------

};
