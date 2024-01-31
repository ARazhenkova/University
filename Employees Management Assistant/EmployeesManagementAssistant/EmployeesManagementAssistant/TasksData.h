
// TasksData.h
//

#pragma once

#include "SmartDataAccessor.h"
#include "TasksTableAccessor.h"

/////////////////////////////////////////////////////////////////////////////
// CTasksData

/// <summary> За работа с данни на задача. </summary>
class CTasksData : public CSmartDataAccessor<CTasksTableAccessor, TASKS>
{
	// Macros
	// ----------------


	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------

public:

	/// <summary> Контруктор. </summary>
	CTasksData();

	/// <summary> Деструктор. </summary>
	virtual ~CTasksData();

	// Overrides
	// ----------------

	/// <summary> Актуализация на запис по ID. </summary>
	/// <param name="lID"> Идентификационен номер на записа.</param>
	/// <param name="recTask"> Данни. </param>
	/// <param name="eLockHint"> Вид заключване. </param>
	/// <param name="strConditions"> Условие на селекта. </param>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	virtual BOOL UpdateRecordByID(const long lID
		, TASKS& recTask
		, const LockHints& eLockHint = LockHintUpdateLock
		, const CString& strConditions = _T("")) override;

	// Methods
	// ----------------

	/// <summary> Търсене на задачи в системата по ID на влезлия потребител. </summary>
	/// <param name="lID"> ID-то, по което ще се търси. </param>
	/// <param name="recEmployee"> Намерените записи, ако има такъва. </param>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	BOOL ReadRecordsByEmployeeID(const long lID, CTasksArray& oTasksArray);

	// Members
	// ----------------

};