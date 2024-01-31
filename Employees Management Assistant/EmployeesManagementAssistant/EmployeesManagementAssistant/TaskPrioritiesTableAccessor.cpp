
// TaskPrioritiesTableAccessor.cpp
//

#include "pch.h"
#include "TaskPrioritiesTableAccessor.h"

/////////////////////////////////////////////////////////////////////////////
// CTaskPrioritiesTableAccessor

// Constructor / Destructor
// ----------------

CTaskPrioritiesTableAccessor::CTaskPrioritiesTableAccessor()
{
}

CTaskPrioritiesTableAccessor::~CTaskPrioritiesTableAccessor()
{
}

// Overrides
// ----------------

const CString CTaskPrioritiesTableAccessor::GetTableName() const
{
	return _T("TASK_PRIORITIES");
}

TASK_PRIORITIES& CTaskPrioritiesTableAccessor::GetAccessor()
{
	return m_recTaskPriority;
}

const long CTaskPrioritiesTableAccessor::GetRecordID(const TASK_PRIORITIES& recTaskPriority) const
{
	return recTaskPriority.lID;
}

const long CTaskPrioritiesTableAccessor::GetUpdateCounter(const TASK_PRIORITIES& recTaskPriority) const
{
	return recTaskPriority.lUpdateCounter;
}

void CTaskPrioritiesTableAccessor::IncrementUpdateCounter(TASK_PRIORITIES& recTaskPriority)
{
	recTaskPriority.lUpdateCounter++;
}

// Methods
// ----------------
