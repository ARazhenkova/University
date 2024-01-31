
// TaskPrioritiesData.h
//

#pragma once

#include "SmartDataAccessor.h"
#include "TaskStatesTableAccessor.h"

/////////////////////////////////////////////////////////////////////////////
// CTaskPrioritiesData

/// <summary> За работа с данни на състояния на задача. </summary>
class CTaskStatesData : public CSmartDataAccessor<CTaskStatesTableAccessor, TASK_STATES>
{
	// Macros
	// ----------------


	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------

public:

	/// <summary> Контруктор. </summary>
	CTaskStatesData();

	/// <summary> Деструктор. </summary>
	virtual ~CTaskStatesData();

	// Overrides
	// ----------------


	// Methods
	// ----------------


	// Members
	// ----------------

};