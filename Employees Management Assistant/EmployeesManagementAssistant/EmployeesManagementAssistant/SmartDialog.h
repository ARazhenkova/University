
// SmartDialog.h
//

#pragma once

#include "pch.h"

/////////////////////////////////////////////////////////////////////////////
// CSmartDialog

/// <summary> Шаблонен клас за диалог. </summary>
template<typename RECORD_TYPE>
class CSmartDialog : public CDialog
{
	// Macros
	// ----------------


	// Constructor / Destructor
	// ----------------

public:

	/// <summary> Контруктор. </summary>
	/// <param name="nIDD"> IID на диалога. </param>
	/// <param name="recRecord"> Запис. </param>
	/// <param name="eRecordAction"> Действия със записи. </param>
	CSmartDialog(int nIDD, RECORD_TYPE& recRecord, const RecordsActions& eRecordAction = RecordsActionView)
		: CDialog(nIDD, NULL)
		, m_recRecord(recRecord)
		, m_eRecordAction(eRecordAction)
	{
	}

	/// <summary> Деструктор. </summary>
	virtual ~CSmartDialog()
	{
	}

	// Overrides
	// ----------------

protected:
	
	/// <summary> При инициализиране на диалога. </summary>
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	virtual BOOL OnInitDialog() override
	{
		__super::OnInitDialog();

		try
		{
			SetTextsLimit();

			if (m_eRecordAction == RecordsActionView)
			{
				CString strTittle;
				GetWindowTextW(strTittle);
				strTittle.Format(_T("Преглед на %s"), strTittle);
				SetWindowTextW(strTittle);

				DisableAndHideControls();

				if (!SetDataToControls())
					return FALSE;
			}
			else if (m_eRecordAction == RecordsActionInsert)
			{
				CString strTittle;
				GetWindowTextW(strTittle);
				strTittle.Format(_T("Добавяне на %s"), strTittle);
				SetWindowTextW(strTittle);

				if (!SetDataToControls())
					return FALSE;
			}
			else if (m_eRecordAction == RecordsActionUpdate)
			{
				CString strTittle;
				GetWindowTextW(strTittle);
				strTittle.Format(_T("Редактиране на %s"), strTittle);
				SetWindowTextW(strTittle);

				if (!SetDataToControls())
					return FALSE;
			}
		}
		catch (...)
		{
			MessageBox(gl_strErrorLoadingData, gl_strError, MB_ICONERROR);
			return FALSE;
		}

		return TRUE;
	}

	/// <summary> При натискане на бутона "Потвърди". </summary>
	virtual void OnOK() override
	{
		try
		{
			GetDataFormControls();

			if (!Validate())
				return;

			AfterValidation();
		}
		catch (...)
		{
			MessageBox(gl_strErrorLoadingData, gl_strError, MB_ICONERROR);
			return;
		}

		__super::OnOK();
	}

	// Methods
	// ----------------

protected:

	/// <summary> Задаване на лимит на текстовите полета. </summary>
	virtual void SetTextsLimit() {  }

	/// <summary> Засивяване и скриване на данните по контролите. </summary>
	virtual void DisableAndHideControls() {  };

	/// <summary> Зареждане на данните по контролите. </summary>
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	virtual BOOL SetDataToControls() { return TRUE; };

	/// <summary> Зареждане на данните от контролите. </summary>
	virtual void GetDataFormControls() {  };

	/// <summary> Валидиране на данните. </summary>
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	virtual BOOL Validate()	{ return TRUE; }

	/// <summary> Действия след валидиране на данните. </summary>
	virtual void AfterValidation() {  }

	/* ВАЛИДАЦИЯ */

	/// <summary> Валидиране на данните в задължително поле. </summary>
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	BOOL ValidateMandatoryField(const TCHAR* pFieldText, const CString& fieldName) 
	{
		if (pFieldText[ZERO] == _T('\0'))
		{
			CString strError;
			strError.Format(gl_strErrorEmptyMandatoryField, fieldName);
			MessageBox(strError, gl_strError, MB_ICONERROR);
			return FALSE;
		}

		return TRUE; 
	}

	/// <summary> Валидиране на данните в задължително поле. </summary>
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	BOOL ValidateTextOnly(const TCHAR* pFieldText, const CString& fieldName)
	{
		if (pFieldText[ZERO] != _T('\0'))
		{
			CString strRegex = _T("^([а-я-А-Я][а-я-А-Я]*)+$");

			CT2CA pszRegex(strRegex);
			CT2CA pszFieldText(pFieldText);

			if (!std::regex_match(std::string(pszFieldText), std::regex(pszRegex)))
			{
				CString strError;
				strError.Format(gl_strErrorIncorrectTextField, fieldName);
				MessageBox(strError, gl_strError, MB_ICONERROR);
				return FALSE;
			}
		} // if

		return TRUE; 
	}

	/// <summary> Валидиране ЕГН-то. </summary>
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	BOOL ValidateIdentifier(const TCHAR* pField)
	{
		if (_tcslen(pField) != CHAR_SIZE_10)
		{
			MessageBox(gl_strErrorIncorrectIdentifier, gl_strError, MB_ICONERROR);
			return FALSE;
		}

		return TRUE;
	}

	/// <summary> Валидиране на имейл. </summary>
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	BOOL ValidateEmailAddress(const TCHAR* pEmailAddress)
	{
		BOOL bResult = TRUE;

		if (pEmailAddress[ZERO] != _T('\0'))
		{
			CString strRegex = _T("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

			CT2CA pszRegex(strRegex);
			CT2CA pszEmail(pEmailAddress);

			if (!std::regex_match(std::string(pszEmail), std::regex(pszRegex)))
			{
				MessageBox(gl_strErrorIncorrectEmailAddress, gl_strError, MB_ICONERROR);
				return FALSE;
			}
		}

		return bResult;
	}

	// Members
	// ----------------

protected:

	///<summary> Запис. </summary>
	RECORD_TYPE& m_recRecord;

	/// <summary> Действия със записи. </summary>
	const RecordsActions& m_eRecordAction;
};
