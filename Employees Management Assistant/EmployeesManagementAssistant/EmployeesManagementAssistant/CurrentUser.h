
// CurrentUser.h
//

#pragma once

#include "EmployeesTableAccessor.h"

/////////////////////////////////////////////////////////////////////////////
// CCurrentUser

class CCurrentUser
{
	// Macros
	// ----------------


	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------

public:

	/// <summary> Контруктор. </summary>
	CCurrentUser();

	/// <summary> Деструктор. </summary>
	virtual~CCurrentUser();

	// Overrides
	// ----------------


	// Methods
	// ----------------

public:

	/// <summary> Първоначална инициализация. </summary>
	/// <param name="lID"> Идентификационният номер на текущият потребител. </param>	
	/// <param name="eAccessLevel"> Нивото на достъп. </param>	
	void Initialize(const long lID, const EmployeeAccessLevels eAccessLevel);

	/// <summary> Достъпване на идентификационния номер на текущият потребител. </summary>
	/// <returns> Идентификационният номер на текущият потребител. </returns>
	const long GetID() const;

	/// <summary> Достъпване на нивото на достъп. </summary>
	/// <returns> Новото на достъп. </returns>
	const EmployeeAccessLevels GetAccessLevel() const;

	/// <summary> Подготвяне на уникален ключа за потребителя. Дължина му е 128 бита или 16 байта 
	/// и е съставен от текуща дата + последните 5 цифри на ЕГН-то. </summary>
	/// <returns> Уникален ключ на потребителя. </returns>
	CString PreparePersonalKey(const TCHAR* pIdentifier);

	// Members
	// ----------------

private:

	/// <summary> Идентификационният номер на текущият потребител. </summary>
	long m_lID;

	/// <summary> Нивото на достъп. </summary>
	EmployeeAccessLevels m_eAccessLevel;
};
