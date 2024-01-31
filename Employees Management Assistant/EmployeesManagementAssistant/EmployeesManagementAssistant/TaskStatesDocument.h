
// TaskStatesDocument.h
//

#pragma once

#include "SmartDocument.h"
#include "TaskStatesData.h"

/////////////////////////////////////////////////////////////////////////////
// CTaskStatesDocument

/// <summary> Документ състояния на задача. </summary>
class CTaskStatesDocument : public CSmartDocument<CTaskStatesData, TASK_STATES>
{
	// Macros
	// ----------------

	DECLARE_DYNCREATE(CTaskStatesDocument)

	// Constructor / Destructor
	// ----------------

public:

	/// <summary> Контруктор. </summary>
	CTaskStatesDocument();

	/// <summary> Деструктор. </summary>
	virtual ~CTaskStatesDocument();

	// Overrides
	// ----------------


	// Methods
	// ----------------


	// Members
	// ----------------

};
