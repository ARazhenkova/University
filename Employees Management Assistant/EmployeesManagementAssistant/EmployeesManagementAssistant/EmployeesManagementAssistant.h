
// EmployeesManagementAssistant.h
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"
#include "CurrentUser.h"
#include "EmployeesTableAccessor.h"

/////////////////////////////////////////////////////////////////////////////
// CEmployeesManagementAssistantApp

class CEmployeesManagementAssistantApp : public CWinAppEx
{
	// Macros
	// ----------------

	DECLARE_MESSAGE_MAP()

	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------

public:

	/// <summary> Контруктор. </summary>
	CEmployeesManagementAssistantApp() noexcept;

	// Overrides
	// ----------------

public:

	void PreLoadState() override;

	BOOL InitInstance() override;

	void LoadCustomState() override;

	int ExitInstance() override;

	// Methods
	// ----------------

public:

	/// <summary> Достъпване на данните на текущия потребител. </summary>
	/// <returns> Данни на текущия потребител. </returns>
	CCurrentUser& GetCurrentUser();

private:

	/// <summary> Инициализиране на документите. </summary>
	/// <param name="strDocumentName"> Име на документа. </param>
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	BOOL InitDocuments();

	/// <summary> Визуализиране на View. </summary>
	/// <param name="strDocumentName"> Име на документа. </param>
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	BOOL ViewCaller(const CString& strDocumentName);

	/// <summary> Вход в системата. </summary>
	/// <returns> TRUE при успешно изпълнение и FALSE при грешка. </returns>
	BOOL Login();

	// Message Handlers
	// ----------------

protected:

	/// <summary> Преглед на профила логнатия служител. </summary>
	afx_msg void OnCommandEmployeeProfile();

	/// <summary> Преглед на служители. </summary>
	afx_msg void OnCommandEmployeesView();
	afx_msg void OnUpdateCommandUIEmployeesView(CCmdUI* pCmdUI);

	/// <summary> Преглед на задачи. </summary>
	afx_msg void OnCommandTasksView();
	afx_msg void OnUpdateCommandUITasksView(CCmdUI* pCmdUI);

	/// <summary> Преглед на приоритети на задачи. </summary>
	afx_msg void OnCommandTaskPrioritiesView();
	afx_msg void OnUpdateCommandUITaskPrioritiesView(CCmdUI* pCmdUI);

	/// <summary> Преглед на състояния на задачи. </summary>
	afx_msg void OnCommandTaskStatesView();
	afx_msg void OnUpdateCommandUITaskStatesView(CCmdUI* pCmdUI);

	// Members
	// ----------------

private:

	/// <summary> Данни на текущия потребител. </summary>
	CCurrentUser m_oCurrentUser;
};

extern CEmployeesManagementAssistantApp theApp;
