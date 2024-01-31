
// TaskPrioritiesData.h
//

#pragma once

#include "SmartDataAccessor.h"
#include "TaskPrioritiesTableAccessor.h"

/////////////////////////////////////////////////////////////////////////////
// CTaskPrioritiesData

/// <summary> За работа с данни на приоритети на задача. </summary>
class CTaskPrioritiesData : public CSmartDataAccessor<CTaskPrioritiesTableAccessor, TASK_PRIORITIES>
{
	// Macros
	// ----------------


	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------

public:

	/// <summary> Контруктор. </summary>
	CTaskPrioritiesData();

	/// <summary> Деструктор. </summary>
	virtual ~CTaskPrioritiesData();

	// Overrides
	// ----------------

	/// <summary> Изчитане на всички записи. </summary>
	/// <param name="oTaskPrioritiesArray"> Данни. </param>
	/// <param name="eLockHint"> Вид заключване. </param>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	BOOL ReadAllRecords(CTaskPrioritiesArray& oTaskPrioritiesArray
		, const LockHints& eLockHint = LockHintNoLock
		, const CString& strConditions = _T("")) override;

	// Methods
	// ----------------


	// Members
	// ----------------

};