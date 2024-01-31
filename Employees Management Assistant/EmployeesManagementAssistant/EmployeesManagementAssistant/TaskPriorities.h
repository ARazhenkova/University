
// TaskPriorities.h
//

#pragma once

#include "pch.h"

/////////////////////////////////////////////////////////////////////////////
// TASK_PRIORITIES

/// <summary> Данни за приоритет на задачи. </summary>
struct TASK_PRIORITIES
{
	/// <summary> Индентификатор на запис. </summary>
	long lID;

	/// <summary> Брояч на промени. </summary>
	long lUpdateCounter;

	/// <summary> Наименование. </summary>
	TCHAR szName[CHAR_SIZE_64 + 1];

	short sLevel;

	TASK_PRIORITIES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

typedef CSmartPtrArray<TASK_PRIORITIES> CTaskPrioritiesArray;
typedef CSmartMap<long, TASK_PRIORITIES> CTaskPrioritiesMap;
