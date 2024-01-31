
// Messages.h
//

#pragma

#include "pch.h"

//const CString gl_ServerConfigPath = _T("C:\\Program Files\\EmployeesManagementAssistant\\db\\ServerConfig.ini");
const CString gl_ServerConfigPath = _T(".\\db\\ServerConfig.ini");

const CString gl_strError								= _T("Грешка");
const CString gl_strWarning								= _T("Предупреждение");
const CString gl_strMissingData							= _T("Липсващи данни");

const CString gl_strNotDefined							= _T("Неопределен");

const CString gl_strFailedToOpenDatabaseConnection 		= _T("Неуспешна създадена връзка към сървъра.");
const CString gl_strFaildToCreateSession				= _T("Неуспешно отваряне на сесия.");
const CString gl_strFailedToExecuteQuery 				= _T("Неуспешно изпълнение на заявката.");
const CString gl_strFailedToReadRecord 					= _T("Неуспешен прочит на запис.");
const CString gl_strRecordNotFound 						= _T("Записът не е намерен.");
const CString gl_strLockHintNotFound					= _T("Ненамерено SQL заключване.");
const CString gl_strUpdateCounterDiscrepancy			= _T("Записът е бил преждевременно променен.");
const CString gl_strUpdatedRecordFailed					= _T("Неуспешно обновен запис.");
const CString gl_strInsertRecordFailed					= _T("Неуспешно добавен запис.");
const CString gl_strDeleteRecordFailed					= _T("Неуспешно изтрит запис.");

const CString gl_strErrorLoadingData					= _T("Данните не могат да бъдат заредени.");
const CString gl_strErrorDataInsertFailed				= _T("Данните не могат да бъдат добавени.");
const CString gl_strErrorDataUpdateFailed				= _T("Данните не могат да бъдат редактирани.");
const CString gl_strErrorDataDeleteFailed				= _T("Данните не могат да бъдат изтрити.");
const CString gl_strErrorNoSelectedData					= _T("Няма избран запис.");
const CString gl_strErrorRecordNotFound					= _T("Записът не беше намерен.");
const CString gl_strValidationError						= _T("Некоректно въведени данни.");
const CString gl_strErrorOppeningRegister				= _T("Неуспешно зареждане на регистъра.");

const CString gl_strErrorEmptyMandatoryField			= _T("Има непопълнено задължително поле: %s.");
const CString gl_strErrorIncorrectEmailAddress			= _T("Некоректен имейл.");
const CString gl_strErrorIncorrectIdentifier			= _T("Некоректно ЕГН.");
const CString gl_strErrorIncorrectTextField				= _T("Некоректно текстово поле %s. Могат да се въвеждат само букви на кирилица.");
const CString gl_strErrorFailedToLoadTaskPriorities		= _T("Възникна грешка при зареждане на приоритетите на задачи.");
const CString gl_strErrorFailedToLoadTaskStates			= _T("Възникна грешка при зареждане на състоянията на задачи.");
const CString gl_strErrorFailedToLoadEmployees			= _T("Възникна грешка при зареждане на служителите.");
const CString gl_strErrorNoPriorities					= _T("Няма настроени приоритети на задача в системата.");
const CString gl_strErrorNoStates						= _T("Няма настроени състояния на задача в системата.");
const CString gl_strErrorNotEnoughEmployees				= _T("Няма достатъчно регистрирани служители в системата.");
const CString gl_strErrorNoEmployees					= _T("Няма регистрирани служители в системата.");
const CString gl_strErrorIncorrectCredentials			= _T("Неправилно ЕГН или парола.");
const CString gl_strErrorIncorrectPasswordLength		= _T("Паролата трябва да бъде поне 8 символа.");
const CString gl_strErrorBlockedAccount					= _T("Акаутът е блокиран. За повече информация се обърнете към системен администратор.");
const CString gl_strErrorIncorrectTaskAssigning			= _T("Служителят, който е назначил задачата и служителя, на когото е назначена, не мога да бъдат един и същ служител.");
