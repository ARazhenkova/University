
// TasksDocument.h
//

#pragma once

#include "SmartDocument.h"
#include "TasksData.h"
#include "Employees.h"
#include "TaskPriorities.h"
#include "TaskStates.h"

/////////////////////////////////////////////////////////////////////////////
// CTasksDocument

/// <summary> Документ задачи. </summary>
class CTasksDocument : public CSmartDocument<CTasksData, TASKS>
{
	// Macros
	// ----------------

	DECLARE_DYNCREATE(CTasksDocument)

	// Constructor / Destructor
	// ----------------

public:

	/// <summary> Контруктор. </summary>
	CTasksDocument();

	/// <summary> Деструктор. </summary>
	virtual ~CTasksDocument();

	// Overrides
	// ----------------

	/// <summary> Зареждане на данни повторно. </summary>
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	BOOL RefreshData() override;

	// Methods
	// ----------------

public:

	/// <summary> Изчитане на приоритети на задача. </summary>
	/// <param name="oTaskPrioritiesArray"> Приоритети на задача. </param>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	BOOL GetTaskPriorities(CTaskPrioritiesArray& oTaskPrioritiesArray);

	/// <summary> Изчитане на статуси на задача. </summary>
	/// <param name="oTaskStatesArray"> Състояния на задача. </param>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	BOOL GetTaskStates(CTaskStatesArray& oTaskStatesArray);

	/// <summary> Изчитане на служителите. </summary>
	/// <param name="oEmployeesArray"> Служители. </param>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	BOOL GetEmployees(CEmployeesArray& oEmployeesArray);

	/// <summary> Търсене на името на приоритет по ID. </summary>
	/// <param name="lPriorityID"> ID. </param>
	/// <param name="lPriorityID"> Приоритет. </param>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	BOOL LookForPriority(const long lPriorityID, CString& strPriorityNam);

	/// <summary> Търсене на името на състояние по ID. </summary>
	/// <param name="lPriorityID"> ID. </param>
	/// <param name="lPriorityID"> Състояние. </param>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	BOOL LookForState(const long lStateID, CString& strStateNam);

private:

	/// <summary> Подготвяне на мап с приоритети, за по-бързо търсене. </summary>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	BOOL LoadPrioritiesMap();

	/// <summary> Подготвяне на мап със състояния, за по-бързо търсене. </summary>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	BOOL LoadStatesMap();

	// Members
	// ----------------

	/// <summary> Приоритети. </summary>
	CTaskPrioritiesMap m_oPrioritiesMap;

	/// <summary> Състояния.</summary>
	CTaskStatesMap m_oStatesMap;
};
