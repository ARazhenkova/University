
// EmployeesView.h
//

#pragma once

#include "SmartView.h"
#include "EmployeesDocument.h"

/////////////////////////////////////////////////////////////////////////////
// CEmployeesView

/// <summary> View за служители. </summary>
class CEmployeesView : public CSmartView<CEmployeesDocument, EMPLOYEES>
{
	// Macros
	// ----------------

	DECLARE_DYNCREATE(CEmployeesView)
	DECLARE_MESSAGE_MAP()

	// Constants
	// ----------------

private:

	/// <summary> Индекси на колоните. </summary>
	enum ColumnIndexes 
	{ 
		ColumnIndexFirstName = 0, 
		ColumnIndexMiddleName,
		ColumnIndexLastName,
		ColumnIndexIdentifier,
	};

	// Constructor / Destructor
	// ----------------

public:

	/// <summary> Контруктор. </summary>
	CEmployeesView();

	/// <summary> Деструктор. </summary>
	virtual ~CEmployeesView();

	// Overrides
	// ----------------

private:

	/// <summary> Добавяне на заглавни редове във View-то. </summary>
	BOOL SetColumnsHeader() override;

	/// <summary> Визуализиране на данни по колоните във View-то. </summary>
	/// <param name="lRecordIndex"> Номерът на елемента. </param>	
	/// <param name="recEmployee"> Запис за визуализиране. </param>	
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	BOOL SetItem(const long lRecordIndex, const EMPLOYEES& recEmployee) override;

	/// <summary> Вземане на идентификатора на записа. </summary>
	/// <param name="recEmployee"> Записa. </param>	
	/// <returns> Идентификаторът на записа. </returns>
	const long GetRecordID(const EMPLOYEES& recEmployee) const override;

	/// <summary> Вземане на идентификатора на записа. </summary>
	/// <param name="recEmployee"> Записa. </param>	
	/// <param name="RecordsAction"> Действие със записa. </param>	
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	BOOL OpenDialog(EMPLOYEES& recEmployee, const RecordsActions RecordsAction) override;

	// Methods
	// ----------------

	// Message Handlers
	// ----------------

	/// <summary> При натискане на изтриване от контекстното меню. </summary>
	afx_msg void OnCommandDelete();

	// Members
	// ----------------

};

