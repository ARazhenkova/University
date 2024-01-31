
// TaskPrioritiesDocument.cpp
//

#include "pch.h"
#include "TaskPrioritiesDocument.h"

/////////////////////////////////////////////////////////////////////////////
// CTaskPrioritiesDocument

IMPLEMENT_DYNCREATE(CTaskPrioritiesDocument, CDocument)

// Constructor / Destructor
// ----------------

CTaskPrioritiesDocument::CTaskPrioritiesDocument()
{
}

CTaskPrioritiesDocument::~CTaskPrioritiesDocument()
{
}

// Overrides
// ----------------

BOOL CTaskPrioritiesDocument::GetAllPriorities(CTaskPrioritiesArray& oTaskPrioritiesArray)
{
	CTaskPrioritiesData oTaskPrioritiesData;
	return oTaskPrioritiesData.ReadAllRecords(oTaskPrioritiesArray);
}

// Methods
// ----------------
