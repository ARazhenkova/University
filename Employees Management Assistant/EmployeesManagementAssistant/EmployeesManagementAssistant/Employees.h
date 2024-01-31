
// Employees.h
//

#pragma once

#include "pch.h"

/////////////////////////////////////////////////////////////////////////////
// EmployeeStatuses

#define EMPLOYEES_STATUSES_COUNT 4

/// <summary> Статуси на служител. </summary>
enum EmployeeStatuses : short
{
	/// <summary> Неопределен. </summary>
	EmployeeStatusUndefined = 0,

	/// <summary> Активен. </summary>
	EmployeeStatusActive,

	/// <summary> Блокиран. </summary>
	EmployeeStatusBlocked,

	/// <summary> Неактивен. </summary>
	EmployeeStatusInactive,
};

/// <summary> Статус на служител като текст. </summary>
class CEmployeeStatus
{
public:
	/// <summary> Връща статуса на служител като текст. </summary>
	/// <param name="sStatus"> Статус. </param>	
	/// <returns> Статусът на служител като текст. </returns>
	static CString GetText(const short sStatus);
};

/////////////////////////////////////////////////////////////////////////////
// EmploeeAccessLevels

#define EMPLOYEES_ACCESS_LEVELS_COUNT 5

/// <summary> Нива на достъп на служител. </summary>
enum EmployeeAccessLevels : short
{
	/// <summary> Неопределен. </summary>
	EmployeeAccessLevelUndefined = 0,

	/// <summary> Служител. </summary>
	EmployeeAccessLevelEmployee,

	/// <summary> Ръководител. </summary>
	EmployeeAccessLevelTeamLeader,

	/// <summary> Директор. </summary>
	EmployeeAccessLevelDirector,

	/// <summary> Администратор. </summary>
	EmployeeAccessLevelAdmin,
};

/// <summary> Нива на достъп на служител като текст. </summary>
class CEmployeeAccessLevel
{
public:
	/// <summary> Връща нивото на достъп на служител като текст. </summary>
	/// <param name="sAccessLevel"> Нивото на достъп. </param>	
	/// <returns> Нивото на достъп на служител като текст. </returns>
	static CString GetText(const short sAccessLevel);
};

/////////////////////////////////////////////////////////////////////////////
// EMPLOYEES

/// <summary> Данни за служител. </summary>
struct EMPLOYEES
{
	/* СИСТЕМНИ ДАННИ */

	/// <summary> Индентификатор на запис. </summary>
	long lID;

	/// <summary> Брояч на промени. </summary>
	long lUpdateCounter;

	/// <summary> Уникален ключ на потребителя. </summary>
	TCHAR szPersonalKey[CHAR_SIZE_16 + 1];

	/// <summary> Статус. </summary>
	short sStatus; // EmployeeStatuses

	/// <summary> Ниво на достъп. </summary>
	short sAccessLevel; // EmploeeAccessLevels

	/// <summary> Парола. </summary>
	TCHAR szPassword[CHAR_SIZE_256 + 1];

	/// <summary> Брояч на неуспешните опити за влизане в системата. </summary>
	short sFailedLoginAttempts;

	/* ОСНОВНИ ДАННИ */

	/// <summary> Име. </summary>
	TCHAR szFirstName[CHAR_SIZE_64 + 1];

	/// <summary> Презиме. </summary>
	TCHAR szMiddleName[CHAR_SIZE_64 + 1];

	/// <summary> Фамилия. </summary>
	TCHAR szLastName[CHAR_SIZE_64 + 1];

	/// <summary> ЕГН. </summary>
	TCHAR szIdentifier[CHAR_SIZE_10 + 1];

	/// <summary> Месечна заплата. </summary>
	double dSalary;

	/// <summary> Личен телефонен номер. </summary>
	TCHAR szPersonalPhoneNumber[CHAR_SIZE_15 + 1];

	/// <summary> Служебен телефонен номер. </summary>
	TCHAR szBusinessPhoneNumber[CHAR_SIZE_15 + 1];

	/// <summary> Имейл адрес. </summary>
	TCHAR szEmailAddress[CHAR_SIZE_256];

	/// <summary> Адрес на местоживеене. </summary>
	TCHAR szHomeAddress[CHAR_SIZE_256];

	/// <summary> Адрес на работното място. </summary>
	TCHAR szWorkAddress[CHAR_SIZE_256];

	EMPLOYEES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

typedef CSmartPtrArray<EMPLOYEES> CEmployeesArray;
