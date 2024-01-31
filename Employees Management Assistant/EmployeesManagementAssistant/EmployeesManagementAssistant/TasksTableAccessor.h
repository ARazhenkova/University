
// TasksTableAccessor.h
//

#pragma once

#include "SmartTable.h"
#include "Tasks.h"

/////////////////////////////////////////////////////////////////////////////
// CTasksDataAccessor

/// <summary> Достъпване на таблицата на задачи. </summary>
class CTasksDataAccessor
{
	// Macros
	// ----------------

	BEGIN_ACCESSOR_MAP(CTasksDataAccessor, 2)
		BEGIN_ACCESSOR(ID_ACCESSOR, true)
			COLUMN_ENTRY(TableColumnID					, m_recTask.lID)
		END_ACCESSOR()
		BEGIN_ACCESSOR(DATA_ACCESSOR, true)
			COLUMN_ENTRY(TableColumnUpdateCounter		, m_recTask.lUpdateCounter)
			COLUMN_ENTRY(TableColumnName				, m_recTask.szName)
			COLUMN_ENTRY(TableColumnPriority			, m_recTask.lPriorityID)
			COLUMN_ENTRY(TableColumnState				, m_recTask.lStateID)
			COLUMN_ENTRY(TableColumnAssignFrom			, m_recTask.lAssignFromID)
			COLUMN_ENTRY(TableColumnAssignTo			, m_recTask.lAssignToID)
			COLUMN_ENTRY(TableColumnDescription			, m_recTask.szDescription)
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
		TableColumnPriority,
		TableColumnState,
		TableColumnAssignFrom,
		TableColumnAssignTo,
		TableColumnDescription,
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

	/// <summary> Данни за задача. </summary>
	TASKS m_recTask;
};

/////////////////////////////////////////////////////////////////////////////
// CTasksTableAccessor

/// <summary> Таблица на задачи. </summary>
class CTasksTableAccessor : public CSmartTable<CTasksDataAccessor, TASKS>
{
	// Macros
	// ----------------


	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------

public:

	/// <summary> Контруктор. </summary>
	CTasksTableAccessor();

	/// <summary> Деструктор. </summary>
	virtual ~CTasksTableAccessor();

	// Overrides
	// ----------------

private:

	/// <summary> Вземане на името на таблицата. </summary>
	/// <returns> Името на таблицата. </returns>
	const CString GetTableName() const override;

	/// <summary> Вземене на аксесора. </summary>
	/// <returns> Данните. </returns>
	TASKS& GetAccessor() override;

	/// <summary> Вземане на идентификатора на записа. </summary>
	/// <param name="recTask"> Записa. </param>	
	/// <returns> Идентификаторът на записа. </returns>
	const long GetRecordID(const TASKS& recTask) const override;

	/// <summary> Вземане на името на брояча на промени. </summary>
	/// <param name="recTask"> Записа, от който се взема брояча на промени. </param>	
	/// <returns> Броячът на промени. </returns>
	const long GetUpdateCounter(const TASKS& recTask) const override;

	/// <summary> Увеличаване на брояча на промени. </summary>
	void IncrementUpdateCounter(TASKS& recTask) override;

	// Methods
	// ----------------


	// Members
	// ----------------

};

/////////////////////////////////////////////////////////////////////////////
// CTasksArchiveTableAccessor

/// <summary> Таблица на задачи. </summary>
class CTasksArchiveTableAccessor : public CTasksTableAccessor
{
	// Macros
	// ----------------


	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------

public:

	/// <summary> Контруктор. </summary>
	CTasksArchiveTableAccessor();

	/// <summary> Деструктор. </summary>
	virtual ~CTasksArchiveTableAccessor();

	// Overrides
	// ----------------

private:

	/// <summary> Вземане на името на таблицата. </summary>
	/// <returns> Името на таблицата. </returns>
	const CString GetTableName() const override;

	// Methods
	// ----------------


	// Members
	// ----------------

};