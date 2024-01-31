
// TasksDocument.cpp
//

#include "pch.h"
#include "EmployeesManagementAssistant.h"
#include "TasksDocument.h"
#include "EmployeesData.h"
#include "TaskPrioritiesData.h"
#include "TaskStatesData.h"

/////////////////////////////////////////////////////////////////////////////
// CTasksDocument

IMPLEMENT_DYNCREATE(CTasksDocument, CDocument)

// Constructor / Destructor
// ----------------

CTasksDocument::CTasksDocument()
{
}

CTasksDocument::~CTasksDocument()
{
}

// Overrides
// ----------------

/// <summary> Зареждане на данни повторно. </summary>
/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
BOOL CTasksDocument::RefreshData()
{
	m_RecordsArray.DeleteAll();

	if (theApp.GetCurrentUser().GetAccessLevel() == EmployeeAccessLevelDirector
		|| theApp.GetCurrentUser().GetAccessLevel() == EmployeeAccessLevelAdmin)
	{
		if (!__super::RefreshData())
			return FALSE;
	}
	else
	{
		if (!CTasksData().ReadRecordsByEmployeeID(theApp.GetCurrentUser().GetID(), m_RecordsArray))
			return FALSE;
	}

	LoadPrioritiesMap();
	LoadStatesMap();

	return TRUE;
}

// Methods
// ----------------

BOOL CTasksDocument::GetTaskPriorities(CTaskPrioritiesArray& oTaskPrioritiesArray)
{
	CTaskPrioritiesData oTaskPrioritiesData;
	return oTaskPrioritiesData.ReadAllRecords(oTaskPrioritiesArray);
}

BOOL CTasksDocument::GetTaskStates(CTaskStatesArray& oTaskStatesArray)
{
	CTaskStatesData oTaskStatesData;
	return oTaskStatesData.ReadAllRecords(oTaskStatesArray);
}

BOOL CTasksDocument::GetEmployees(CEmployeesArray& oEmployeesArray)
{
	CEmployeesData oEmployeesData;
	return oEmployeesData.ReadAllRecords(oEmployeesArray);
}

BOOL CTasksDocument::LookForPriority(const long lPriorityID, CString& strPriorityName)
{
	TASK_PRIORITIES* pPriority = NULL;

	if (m_oPrioritiesMap.Lookup(lPriorityID, pPriority) == 0)
		return FALSE;

	if (pPriority == NULL)
		return FALSE;

	strPriorityName.Format(_T("%s"), pPriority->szName);

	return TRUE;
}

BOOL CTasksDocument::LookForState(const long lStateID, CString& strStateName)
{
	TASK_STATES* pState = NULL;

	if (m_oStatesMap.Lookup(lStateID, pState) == 0)
		return FALSE;

	if (pState == NULL)
		return FALSE;

	strStateName.Format(_T("%s"), pState->szName);

	return TRUE;
}

BOOL CTasksDocument::LoadPrioritiesMap()
{
	CTaskPrioritiesArray oTaskPrioritiesArray;
	if (!GetTaskPriorities(oTaskPrioritiesArray))
		return FALSE;

	for (INT_PTR i = 0; i < oTaskPrioritiesArray.GetCount(); i++)
	{
		TASK_PRIORITIES* pPriority = oTaskPrioritiesArray.GetAt(i);
		if (pPriority == NULL)
			return FALSE;

		TASK_PRIORITIES* pNewPriority = new TASK_PRIORITIES;
		*pNewPriority = *pPriority;
		m_oPrioritiesMap.SetAt(pNewPriority->lID, pNewPriority);
	}

	return TRUE;
}

BOOL CTasksDocument::LoadStatesMap()
{
	CTaskStatesArray oTaskStatesArray;
	if (!GetTaskStates(oTaskStatesArray))
		return FALSE;

	for (INT_PTR i = 0; i < oTaskStatesArray.GetCount(); i++)
	{
		TASK_STATES* pState = oTaskStatesArray.GetAt(i);
		if (pState == NULL)
			return FALSE;

		TASK_STATES* pNewState = new TASK_STATES;
		*pNewState = *pState;
		m_oStatesMap.SetAt(pNewState->lID, pNewState);
	}

	return TRUE;
}
