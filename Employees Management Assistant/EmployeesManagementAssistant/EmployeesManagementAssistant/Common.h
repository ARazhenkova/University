
// Common.h
//

#pragma once

#define NONE 0
#define ZERO 0

#define ALLOWED_LOGIN_ATTEMPTS 3

#define SALARY_PRECISION 2

#define CHAR_SIZE_6 6
#define CHAR_SIZE_8 8
#define CHAR_SIZE_10 10
#define CHAR_SIZE_15 15
#define CHAR_SIZE_16 16
#define CHAR_SIZE_32 32
#define CHAR_SIZE_64 64
#define CHAR_SIZE_128 128
#define CHAR_SIZE_256 256
#define CHAR_SIZE_512 512

/////////////////////////////////////////////////////////////////////////////
// RecordsActions

/// <summary> Действия със записи. </summary>
enum RecordsActions
{
	/// <summary> Преглед. </summary>
	RecordsActionView = 1,

	/// <summary> Добавяне. </summary>
	RecordsActionInsert,

	/// <summary> Редактиране. </summary>
	RecordsActionUpdate,

	/// <summary> Изтриване. </summary>
	RecordsActionDelete,
};

/////////////////////////////////////////////////////////////////////////////
// LockHints

/// <summary> Вид заключвания на SQL. </summary>
enum LockHints
{
	/// <summary> NOLOCK </summary>
	LockHintNoLock = 0,

	/// <summary> UPDLOCK </summary>
	LockHintUpdateLock = 1,

	/// <summary> ROWLOCK </summary>
	LockHintRowLock = 2
};
