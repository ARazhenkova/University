
// EmployeesTableAccessor.h
//

#pragma once

#include "SmartTable.h"
#include "Employees.h"

/////////////////////////////////////////////////////////////////////////////
// CEmployeesDataAccessor

/// <summary> Достъпване на таблицата на служители. </summary>
class CEmployeesDataAccessor
{
	// Macros
	// ----------------

	BEGIN_ACCESSOR_MAP(CEmployeesDataAccessor, 2)
		BEGIN_ACCESSOR(ID_ACCESSOR, true)
			COLUMN_ENTRY(TableColumnID						, m_recEmployee.lID)
		END_ACCESSOR()
		BEGIN_ACCESSOR(DATA_ACCESSOR, true)
			COLUMN_ENTRY(TableColumnUpdateCounter			, m_recEmployee.lUpdateCounter)
			COLUMN_ENTRY(TableColumnPersonalKey				,m_recEmployee.szPersonalKey)
			COLUMN_ENTRY(TableColumnStatus					, m_recEmployee.sStatus)
			COLUMN_ENTRY(TableColumnAccessLevel				, m_recEmployee.sAccessLevel)
			COLUMN_ENTRY(TableColumnPassword				, m_recEmployee.szPassword)
			COLUMN_ENTRY(TableColumnFailedLoginAttempts		, m_recEmployee.sFailedLoginAttempts)

			COLUMN_ENTRY(TableColumnFirstName				, m_recEmployee.szFirstName)
			COLUMN_ENTRY(TableColumnMiddleName				, m_recEmployee.szMiddleName)
			COLUMN_ENTRY(TableColumnLastName				, m_recEmployee.szLastName)
			COLUMN_ENTRY(TableColumnIdentifier				, m_recEmployee.szIdentifier)
			COLUMN_ENTRY(TableColumnSalary					, m_recEmployee.dSalary)

			COLUMN_ENTRY(TableColumnPersonalPhoneNumber		, m_recEmployee.szPersonalPhoneNumber)
			COLUMN_ENTRY(TableColumnBusinessPhoneNumber		, m_recEmployee.szBusinessPhoneNumber)
			COLUMN_ENTRY(TableColumnEmailAddress			, m_recEmployee.szEmailAddress)

			COLUMN_ENTRY(TableColumnHomeAddress				, m_recEmployee.szHomeAddress)
			COLUMN_ENTRY(TableColumnWorkAddress				, m_recEmployee.szWorkAddress)
		END_ACCESSOR()
	END_ACCESSOR_MAP()

	// Constants
	// ----------------

private:

	enum TableColumns
	{
		TableColumnID = 1,
		TableColumnUpdateCounter,
		TableColumnPersonalKey,
		TableColumnStatus,
		TableColumnAccessLevel,
		TableColumnPassword,
		TableColumnFailedLoginAttempts,

		TableColumnFirstName,
		TableColumnMiddleName,
		TableColumnLastName,
		TableColumnIdentifier,
		TableColumnSalary,

		TableColumnPersonalPhoneNumber,
		TableColumnBusinessPhoneNumber,
		TableColumnEmailAddress,

		TableColumnHomeAddress,
		TableColumnWorkAddress,
	};

	// Constructor / Destructor
	// ----------------


	// Overrides
	// ----------------


	// Methods
	// ----------------


	// Members
	// ----------------

protected:

	/// <summary> Данни за служител. </summary>
	EMPLOYEES m_recEmployee;
};

/////////////////////////////////////////////////////////////////////////////
// CEmployeesTableAccessor

/// <summary> Таблица на служители. </summary>
class CEmployeesTableAccessor : public CSmartTable<CEmployeesDataAccessor, EMPLOYEES>
{
	// Macros
	// ----------------


	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------

public:

	/// <summary> Контруктор. </summary>
	CEmployeesTableAccessor();

	/// <summary> Деструктор. </summary>
	virtual ~CEmployeesTableAccessor();

	// Overrides
	// ----------------

private:

	/// <summary> Вземане на името на таблицата. </summary>
	/// <returns> Името на таблицата. </returns>
	const CString GetTableName() const override;

	/// <summary> Вземене на аксесора. </summary>
	/// <returns> Данните. </returns>
	EMPLOYEES& GetAccessor() override;

	/// <summary> Вземане на идентификатора на записа. </summary>
	/// <param name="recEmployee"> Записa. </param>	
	/// <returns> Идентификаторът на записа. </returns>
	const long GetRecordID(const EMPLOYEES& recEmployee) const override;

	/// <summary> Вземане на името на брояча на промени. </summary>
	/// <param name="recEmployee"> Записа, от който се взема брояча на промени. </param>	
	/// <returns> Броячът на промени. </returns>
	const long GetUpdateCounter(const EMPLOYEES& recEmployee) const override;

	/// <summary> Увеличаване на брояча на промени. </summary>
	void IncrementUpdateCounter(EMPLOYEES& recEmployee) override;

	// Methods
	// ----------------


	// Members
	// ----------------

};
