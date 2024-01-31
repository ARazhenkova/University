
// Employees.cpp
//

#include "pch.h"
#include "Employees.h"

/////////////////////////////////////////////////////////////////////////////
// EmployeeStatuses

/// <summary> Статус на служител като текст. </summary>
CString CEmployeeStatus::GetText(const short sStatus)
{
	switch(sStatus)
	{
		case EmployeeStatusActive:
			return _T("АКТИВЕН");

		case EmployeeStatusBlocked:
			return _T("БЛОКИРАН");

		case EmployeeStatusInactive:
			return _T("НЕАКТИВЕН");

		default:
			return gl_strNotDefined;
	}
}

/////////////////////////////////////////////////////////////////////////////
// EmploeeAccessLevels

CString CEmployeeAccessLevel::GetText(const short sStatus)
{
	switch (sStatus)
	{
		case EmployeeAccessLevelEmployee:
			return _T("Служител");

		case EmployeeAccessLevelTeamLeader:
			return _T("Ръководител");

		case EmployeeAccessLevelDirector:
			return _T("Директор");

		case EmployeeAccessLevelAdmin:
			return _T("Администратор");

		default:
			return gl_strNotDefined;
	}
}
