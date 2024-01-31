
// EmployeesTableAccessor.cpp
//

#include "pch.h"
#include "EmployeesTableAccessor.h"

/////////////////////////////////////////////////////////////////////////////
// CEmployeesTableAccessor

// Constructor / Destructor
// ----------------

CEmployeesTableAccessor::CEmployeesTableAccessor()
{
}

CEmployeesTableAccessor::~CEmployeesTableAccessor()
{
}

// Overrides
// ----------------

const CString CEmployeesTableAccessor::GetTableName() const
{
	return _T("EMPLOYEES");
}

EMPLOYEES& CEmployeesTableAccessor::GetAccessor()
{
	return m_recEmployee;
}

const long CEmployeesTableAccessor::GetRecordID(const EMPLOYEES& recEmployee) const
{
	return recEmployee.lID;
}

const long CEmployeesTableAccessor::GetUpdateCounter(const EMPLOYEES& recEmployee) const
{
	return recEmployee.lUpdateCounter;
}

void CEmployeesTableAccessor::IncrementUpdateCounter(EMPLOYEES& recEmployee)
{
	recEmployee.lUpdateCounter++;
}

// Methods
// ----------------
