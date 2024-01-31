
// TaskPrioritiesData.cpp
//

#include "pch.h"
#include "TaskPrioritiesData.h"

/////////////////////////////////////////////////////////////////////////////
// CTaskPrioritiesData

// Constructor / Destructor
// ----------------

CTaskPrioritiesData::CTaskPrioritiesData()
{

}

CTaskPrioritiesData::~CTaskPrioritiesData()
{
}

// Overrides
// ----------------

BOOL CTaskPrioritiesData::ReadAllRecords(CTaskPrioritiesArray& oTaskPrioritiesArray
	, const LockHints& eLockHint /* = LockHintNoLock */
	, const CString& strConditions /* = _T("") */)
{
	CString strCustomConditions = _T("ORDER BY LEVEL ASC");
	strCustomConditions.Format(_T("%s %s"), strConditions, strCustomConditions);

	return CTaskPrioritiesTableAccessor().ReadRecords(oTaskPrioritiesArray, _T("*"), eLockHint, strCustomConditions);
}

// Methods
// ----------------
