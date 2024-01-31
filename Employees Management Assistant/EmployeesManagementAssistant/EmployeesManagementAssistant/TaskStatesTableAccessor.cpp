
// TaskStatesTableAccessor.cpp
//

#include "pch.h"
#include "TaskStatesTableAccessor.h"

/////////////////////////////////////////////////////////////////////////////
// CTaskStatesTableAccessor

// Constructor / Destructor
// ----------------

CTaskStatesTableAccessor::CTaskStatesTableAccessor()
{
}

CTaskStatesTableAccessor::~CTaskStatesTableAccessor()
{
}

// Overrides
// ----------------

const CString CTaskStatesTableAccessor::GetTableName() const
{
	return _T("TASK_STATES");
}

TASK_STATES& CTaskStatesTableAccessor::GetAccessor()
{
	return m_recTaskState;
}

const long CTaskStatesTableAccessor::GetRecordID(const TASK_STATES& recTaskState) const
{
	return recTaskState.lID;
}

const long CTaskStatesTableAccessor::GetUpdateCounter(const TASK_STATES& recTaskState) const
{
	return recTaskState.lUpdateCounter;
}

void CTaskStatesTableAccessor::IncrementUpdateCounter(TASK_STATES& recTaskState)
{
	recTaskState.lUpdateCounter++;
}

// Methods
// ----------------
