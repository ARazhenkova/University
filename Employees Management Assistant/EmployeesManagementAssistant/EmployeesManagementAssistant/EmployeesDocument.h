
// EmployeesDocument.h
//

#pragma once

#include "SmartDocument.h"
#include "EmployeesData.h"

/////////////////////////////////////////////////////////////////////////////
// CEmployeesDocument

/// <summary> Документ служители. </summary>
class CEmployeesDocument : public CSmartDocument<CEmployeesData, EMPLOYEES>
{
	// Macros
	// ----------------

	DECLARE_DYNCREATE(CEmployeesDocument)

	// Constructor / Destructor
	// ----------------

public:

	/// <summary> Контруктор. </summary>
	CEmployeesDocument();

	/// <summary> Деструктор. </summary>
	virtual ~CEmployeesDocument();

	// Overrides
	// ----------------


	// Methods
	// ----------------

	/// <summary> Изтриване на запис. </summary>
	/// <param name="lID"> Идентификационният номер на записа. </param>
	/// <param name="recEmployee"> Записът. </param>
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	BOOL DeleteRecord(const long& lID, EMPLOYEES& recEmployee);

	// Members
	// ----------------

};
