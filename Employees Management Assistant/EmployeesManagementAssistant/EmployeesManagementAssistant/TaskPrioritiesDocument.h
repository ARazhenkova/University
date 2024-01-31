
// TaskPrioritiesDocument.h
//

#pragma once

#include "SmartDocument.h"
#include "TaskPrioritiesData.h"

/////////////////////////////////////////////////////////////////////////////
// CTaskPrioritiesDocument

/// <summary> Документ приоритети на задача. </summary>
class CTaskPrioritiesDocument : public CSmartDocument<CTaskPrioritiesData, TASK_PRIORITIES>
{
	// Macros
	// ----------------

	DECLARE_DYNCREATE(CTaskPrioritiesDocument)

	// Constructor / Destructor
	// ----------------

public:

	/// <summary> Контруктор. </summary>
	CTaskPrioritiesDocument();

	/// <summary> Деструктор. </summary>
	virtual ~CTaskPrioritiesDocument();

	// Overrides
	// ----------------


	// Methods
	// ----------------

public:

	/// <summary> Изчитане на приоритети на задача. </summary>
	/// <param name="oTaskPrioritiesArray"> Приоритети на задача. </param>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	BOOL GetAllPriorities(CTaskPrioritiesArray& oTaskPrioritiesArray);

	// Members
	// ----------------

};
