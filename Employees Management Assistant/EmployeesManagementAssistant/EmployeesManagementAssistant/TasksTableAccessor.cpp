
// TasksTableAccessor.cpp
//

#include "pch.h"
#include "TasksTableAccessor.h"

/////////////////////////////////////////////////////////////////////////////
// CTasksTableAccessor

// Constructor / Destructor
// ----------------

CTasksTableAccessor::CTasksTableAccessor()
{
}

CTasksTableAccessor::~CTasksTableAccessor()
{
}

// Overrides
// ----------------

const CString CTasksTableAccessor::GetTableName() const
{
	return _T("TASKS");
}

TASKS& CTasksTableAccessor::GetAccessor()
{
	return m_recTask;
}

const long CTasksTableAccessor::GetRecordID(const TASKS& recTask) const
{
	return recTask.lID;
}

const long CTasksTableAccessor::GetUpdateCounter(const TASKS& recTask) const
{
	return recTask.lUpdateCounter;
}

void CTasksTableAccessor::IncrementUpdateCounter(TASKS& recTask)
{
	recTask.lUpdateCounter++;
}

// Methods
// ----------------

/////////////////////////////////////////////////////////////////////////////
// CTasksTableAccessor

// Constructor / Destructor
// ----------------

CTasksArchiveTableAccessor::CTasksArchiveTableAccessor()
{
}

CTasksArchiveTableAccessor::~CTasksArchiveTableAccessor()
{
}

// Overrides
// ----------------

const CString CTasksArchiveTableAccessor::GetTableName() const
{
	return _T("TASKS_ARCHIVE");
}

// Methods
// ----------------
