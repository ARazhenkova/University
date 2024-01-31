
// TaskStates.h
//

#pragma once

#include "pch.h"

/////////////////////////////////////////////////////////////////////////////
// TASK_STATES

/// <summary> Данни за състояние на задачи. </summary>
struct TASK_STATES
{
	/// <summary> Индентификатор на запис. </summary>
	long lID;

	/// <summary> Брояч на промени. </summary>
	long lUpdateCounter;

	/// <summary> Наименование. </summary>
	TCHAR szName[CHAR_SIZE_64 + 1];

	/// <summary> Дали да се архивира записа при това състояние. </summary>
	short sIsForAchive;

	TASK_STATES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

typedef CSmartPtrArray<TASK_STATES> CTaskStatesArray;
typedef CSmartMap<long, TASK_STATES> CTaskStatesMap;
