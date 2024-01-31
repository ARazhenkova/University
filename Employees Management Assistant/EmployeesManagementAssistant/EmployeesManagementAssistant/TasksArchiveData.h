
// TasksArchiveData.h
//

#pragma once

#include "SmartDataAccessor.h"
#include "TasksTableAccessor.h"

/////////////////////////////////////////////////////////////////////////////
// CTasksArchiveData

/// <summary> За работа с данни на задача. </summary>
class CTasksArchiveData : public CSmartDataAccessor<CTasksArchiveTableAccessor, TASKS>
{
	// Macros
	// ----------------


	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------

public:

	/// <summary> Контруктор. </summary>
	CTasksArchiveData();

	/// <summary> Деструктор. </summary>
	virtual ~CTasksArchiveData();

	// Overrides
	// ----------------


	// Methods
	// ----------------


	// Members
	// ----------------

};