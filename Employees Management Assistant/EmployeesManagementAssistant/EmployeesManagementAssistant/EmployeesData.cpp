
// EmployeesData.cpp
//

#include "pch.h"
#include "EmployeesData.h"
#include "EmployeesManagementAssistant.h"
#include "Encryption.h"

/////////////////////////////////////////////////////////////////////////////
// CEmployeesData

// Constructor / Destructor
// ----------------

CEmployeesData::CEmployeesData()
{
}

CEmployeesData::~CEmployeesData()
{
}

// Overrides
// ----------------


// Methods
// ----------------

BOOL CEmployeesData::ReadAllRecords(CEmployeesArray& oEmployeesArray
	, const LockHints& eLockHint /* = LockHintNoLock */
	, const CString& strConditions /* = _T("") */)
{
	CString strCustomConditions = _T("ORDER BY FIRST_NAME, MIDDLE_NAME, LAST_NAME ASC");
	strCustomConditions.Format(_T("%s %s"), strConditions, strCustomConditions);

	return CEmployeesTableAccessor().ReadRecords(oEmployeesArray, _T("*"), eLockHint, strCustomConditions);
}

BOOL CEmployeesData::ReadRecordByID(const long lID, EMPLOYEES& recEmployee)
{
	CString strCondition;
	strCondition.Format(_T("WHERE [ID] = %d"), lID);

	BOOL bHasRecord = FALSE;
	if (!ReadRecord(recEmployee, bHasRecord, LockHintNoLock, strCondition))
		return FALSE;

	if (!bHasRecord)
		return FALSE;

	return TRUE;
}

BOOL CEmployeesData::ReadRecordByIdentifier(const TCHAR* pIdentifer, EMPLOYEES& recEmployee, BOOL& bIsBlocked)
{
	CString strCondition;
	strCondition.Format(_T("WHERE [IDENTIFIER] = '%s' AND [STATUS_ID] != %d"), pIdentifer, EmployeeStatusInactive);

	BOOL bHasRecord = FALSE;
	if (!ReadRecord(recEmployee, bHasRecord, LockHintNoLock, strCondition))
		return FALSE;

	if (!bHasRecord)
		return FALSE;

	// Проверка дали е блокиран
	if (recEmployee.sStatus == EmployeeStatusBlocked)
	{
		bIsBlocked = TRUE;
		return FALSE;
	}

	return TRUE;
}

BOOL CEmployeesData::DeleteRecordByID(const long lID
	, EMPLOYEES& recEmployee
	, const CString& strConditions /* = _T("") */)
{
	if (theApp.GetCurrentUser().GetID() == lID)
		return FALSE;

	if (!__super::DeleteRecordByID(lID))
	{
		recEmployee.sStatus = EmployeeStatusInactive;
		if (!UpdateRecordByID(lID, recEmployee))
			return FALSE;
	}

	return TRUE;
}

BOOL CEmployeesData::ValidatePassword(const TCHAR* pPersonalKey, const TCHAR* pSavedPassword, const TCHAR* pEnteredPassword)
{
	// Хеширане на въведената парола
	CString strPassordHelper;
	if (!CEncryption::PBKDF2Hashing(pEnteredPassword, pPersonalKey, strPassordHelper))
		return FALSE;
	TCHAR szEnteredPassword[CHAR_SIZE_256];
	wcscpy_s(szEnteredPassword, strPassordHelper);

	// Проверка дали паролата съвпада с въведената
	if (StrCmpI(pSavedPassword, szEnteredPassword) != 0)
		return FALSE;

	return TRUE;
}

BOOL CEmployeesData::CheckLoginCredentials(const EMPLOYEES& recEmployeeInput, BOOL& bIsBlocked)
{
	EMPLOYEES recEmployee;
	if (!ReadRecordByIdentifier(recEmployeeInput.szIdentifier, recEmployee, bIsBlocked))
		return FALSE;

	if (!ValidatePassword(recEmployee.szPersonalKey, recEmployee.szPassword, recEmployeeInput.szPassword))
	{
		// Увеличаване на брояча за неуспешни опити за влизане в системата
		recEmployee.sFailedLoginAttempts += 1;

		// Ако е достигнат масксималният брой за опити за влизане в системата, се блокира 
		if (recEmployee.sFailedLoginAttempts == ALLOWED_LOGIN_ATTEMPTS)
		{
			recEmployee.sStatus = EmployeeStatusBlocked;
			bIsBlocked = TRUE;
		}

		// Запазване на промените
		if (!UpdateRecordByID(recEmployee.lID, recEmployee))
			PostQuitMessage(0);

		return FALSE;
	}

	// Нулиране на брояча за неуспешни опити за влизане в системата
	if (recEmployee.sFailedLoginAttempts != 0)
	{
		recEmployee.sFailedLoginAttempts = 0;
		if (!UpdateRecordByID(recEmployee.lID, recEmployee))
			PostQuitMessage(0);
	}

	// Запазване на данни за логнатия потребител
	theApp.GetCurrentUser().Initialize(recEmployee.lID, (EmployeeAccessLevels)recEmployee.sAccessLevel);

	return TRUE;
}
