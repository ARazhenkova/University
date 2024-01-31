
// Tasks.h
//

#pragma once

#include "pch.h"

/////////////////////////////////////////////////////////////////////////////
// TASKS

/// <summary> Данни за задача. </summary>
struct TASKS
{
	/// <summary> Индентификатор на запис. </summary>
	long lID;

	/// <summary> Брояч на промени. </summary>
	long lUpdateCounter;

	/// <summary> Наименование. </summary>
	TCHAR szName[CHAR_SIZE_64 + 1];

	/// <summary> Приоритет. </summary>
	long lPriorityID;

	/// <summary> Състояние. </summary>
	long lStateID;

	/// <summary> Назначена от. </summary>
	long lAssignFromID;

	/// <summary> Назначена на. </summary>
	long lAssignToID;

	/// <summary> Описание. </summary>
	TCHAR szDescription[CHAR_SIZE_512 + 1];

	TASKS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

typedef CSmartPtrArray<TASKS> CTasksArray;
