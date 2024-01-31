
// EmployeesData.h
//

#pragma once

#include "SmartDataAccessor.h"
#include "EmployeesTableAccessor.h"

/////////////////////////////////////////////////////////////////////////////
// CEmployeesData

/// <summary> За работа с данни на служител. </summary>
class CEmployeesData : public CSmartDataAccessor<CEmployeesTableAccessor, EMPLOYEES>
{
	// Macros
	// ----------------


	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------
	
public:

	/// <summary> Контруктор. </summary>
	CEmployeesData();

	/// <summary> Деструктор. </summary>
	virtual ~CEmployeesData();

	// Overrides
	// ----------------


	// Methods
	// ----------------

	/// <summary> Изчитане на всички записи. </summary>
	/// <param name="oEmployeesArray"> Данни. </param>
	/// <param name="eLockHint"> Вид заключване. </param>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	BOOL ReadAllRecords(CEmployeesArray& oEmployeesArray
		, const LockHints& eLockHint = LockHintNoLock
		, const CString& strConditions = _T("")) override;

	/// <summary> Търсене на служителя в системата по ID. </summary>
	/// <param name="lID"> ID-то, по което ще се търси. </param>
	/// <param name="recEmployee"> Намереният запис, ако има такъв. </param>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	BOOL ReadRecordByID(const long lID, EMPLOYEES& recEmployee);

	/// <summary> Търсене на служителя в системата по ЕГН. </summary>
	/// <param name="pIdentifer"> ЕГН-то, по което ще се търси. </param>
	/// <param name="recEmployee"> Намереният запис, ако има такъв. </param>
	/// <param name="bIsBlocked"> Дали служителят е със статус БЛОКИРАН. </param>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	BOOL ReadRecordByIdentifier(const TCHAR* pIdentifer, EMPLOYEES &recEmployee, BOOL& bIsBlocked);

	/// <summary> Изтриване на запис по ID. Ако не може да се изтрие, се слага статус НЕАКТИВЕН. </summary>
	/// <param name="lID"> Идентификационен номер на записа. </param>
	/// <param name="recEmployee"> Записът. </param>
	/// <param name="strConditions"> Условие на селекта. </param>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	BOOL DeleteRecordByID(const long lID
		, EMPLOYEES& recEmployee
		, const CString& strConditions = _T(""));

	/// <summary> Проверка дали паролата съвпада с въведената. </summary>
	/// <param name="pPersonalKey"> Уникален ключ на потребителя. </param>
	/// <param name="pSavedPassword"> Паролата от базата данни. </param>
	/// <param name="pEnteredPassword"> Въведената парола. </param>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	BOOL ValidatePassword(const TCHAR* pPersonalKey, const TCHAR* pSavedPassword, const TCHAR* pEnteredPassword);

	/// <summary> Валидиране на данните за вход в системата. </summary>
	/// <param name="recEmployeeInput"> Входните данни. </param>
	/// <param name="bIsBlocked"> Дали служителят е със статус БЛОКИРАН. </param>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	BOOL CheckLoginCredentials(const EMPLOYEES& recEmployeeInput, BOOL& bIsBlocked);

	// Members
	// ----------------

};