
// TasksData.cpp
//

#include "pch.h"
#include "TasksData.h"
#include "TaskStatesData.h"
#include "TasksArchiveData.h"

/////////////////////////////////////////////////////////////////////////////
// CTasksData

// Constructor / Destructor
// ----------------

CTasksData::CTasksData()
{

}

CTasksData::~CTasksData()
{
}

// Overrides
// ----------------
BOOL CTasksData::UpdateRecordByID(const long lID
	, TASKS& recTask
	, const LockHints& eLockHint /* = LockHintUpdateLock */
	, const CString& strConditions /* = _T("") */)
{
	TASK_STATES recTaskState;
	BOOL bHasRecord = FALSE;
	CString strCustomCondition = _T("");
	strCustomCondition.Format(_T("WHERE ID = %d %s"), recTask.lStateID, strConditions);

	if (!CTaskStatesData().ReadRecord(recTaskState, bHasRecord, LockHintNoLock, strCustomCondition))
		return FALSE;

	if (!bHasRecord)
		return FALSE;

	if (recTaskState.sIsForAchive)
	{
		if (!DeleteRecordByID(lID))
			return FALSE;

		if (!CTasksArchiveData().InsertRecord(recTask))
			return FALSE;

		recTask.lID = lID;
	}
	else
	{
		if (!__super::UpdateRecordByID(lID, recTask))
			return FALSE;
	}

	return TRUE;
}

// Methods
// ----------------

BOOL CTasksData::ReadRecordsByEmployeeID(const long lID, CTasksArray& oTasksArray)
{
	CString strCondition;
	strCondition.Format(_T("WHERE [ASSIGN_TO_ID] = %d"), lID);

	if (!ReadRecords(oTasksArray, _T("TOP(1) *"), LockHintNoLock, strCondition))
		return FALSE;

	return TRUE;
}
