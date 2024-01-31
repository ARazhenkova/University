
// EmployeesDocument.cpp
//

#include "pch.h"
#include "EmployeesDocument.h"

/////////////////////////////////////////////////////////////////////////////
// CEmployeesDocument

IMPLEMENT_DYNCREATE(CEmployeesDocument, CDocument)

// Constructor / Destructor
// ----------------

CEmployeesDocument::CEmployeesDocument()
{
}

CEmployeesDocument::~CEmployeesDocument()
{
}

// Overrides
// ----------------


// Methods
// ----------------

BOOL CEmployeesDocument::DeleteRecord(const long& lID, EMPLOYEES& recEmployee)
{
	// Обновяване в базата данни
	CEmployeesData oEmployeesData;
	if (!oEmployeesData.DeleteRecordByID(lID, recEmployee))
		return FALSE;

	// Обновяване в масива от данни
	INT_PTR nIndex = m_RecordsArray.Search(lID);
	if (nIndex == INT_ERROR)
		return FALSE;

	m_RecordsArray.DeleteAt(nIndex);

	// Обновяване на заредените градове
	__super::UpdateAllViews(NULL, RecordsActionDelete, (CObject*)&lID);

	return TRUE;
}
