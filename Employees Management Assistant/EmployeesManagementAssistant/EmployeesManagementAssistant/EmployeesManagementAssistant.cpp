
// EmployeesManagementAssistant.cpp
//

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "pch.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "EmployeesManagementAssistant.h"
#include "LoginDialog.h"

#include "EmployeesDocument.h"
#include "TasksDocument.h"
#include "TaskPrioritiesDocument.h"
#include "TaskStatesDocument.h"

#include "EmployeesView.h"
#include "TasksView.h"
#include "TaskPrioritiesView.h"
#include "TaskStatesView.h"
#include "EmployeesDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CEmployeesManagementAssistantApp

BEGIN_MESSAGE_MAP(CEmployeesManagementAssistantApp, CWinAppEx)
	ON_COMMAND(ID_EMPLOYEE_PROFILE, &OnCommandEmployeeProfile)
	ON_COMMAND(ID_EMPLOYEES_VIEW, &OnCommandEmployeesView)
	ON_UPDATE_COMMAND_UI(ID_EMPLOYEES_VIEW, OnUpdateCommandUIEmployeesView)
	ON_COMMAND(ID_TASKS_VIEW, &OnCommandTasksView)
	ON_UPDATE_COMMAND_UI(ID_TASKS_VIEW, OnUpdateCommandUITasksView)
	ON_COMMAND(ID_TASK_PRIORITIES_VIEW, &OnCommandTaskPrioritiesView)
	ON_UPDATE_COMMAND_UI(ID_TASK_PRIORITIES_VIEW, OnUpdateCommandUITaskPrioritiesView)
	ON_COMMAND(ID_TASK_STATES_VIEW, &OnCommandTaskStatesView)
	ON_UPDATE_COMMAND_UI(ID_TASK_STATES_VIEW, OnUpdateCommandUITaskStatesView)
END_MESSAGE_MAP()

CEmployeesManagementAssistantApp theApp;

// Constructor / Destructor
// ----------------

CEmployeesManagementAssistantApp::CEmployeesManagementAssistantApp() noexcept
{

	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("EmployeesManagementAssistant.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// Overrides
// ----------------

void CEmployeesManagementAssistantApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;

	bNameValid = strName.LoadString(IDR_LIST_VIEW_CONTEXT_MENU);
	ASSERT(bNameValid);

	// Добавяне на контектно меню
	GetContextMenuManager()->AddMenu(strName, IDR_LIST_VIEW_CONTEXT_MENU);
}

BOOL CEmployeesManagementAssistantApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// AfxInitRichEdit2() is required to use RichEdit control
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)


	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	InitDocuments();

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	//CCommandLineInfo cmdInfo;
	//ParseCommandLine(cmdInfo);



	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	//if (!ProcessShellCommand(cmdInfo))
	//	return FALSE;
	// The main window has been initialized, so show and update it
	//pMainFrame->ShowWindow(m_nCmdShow);
	//pMainFrame->UpdateWindow();
	CDateTime::CurrentDataTimeToString();
	if (!Login())
		return FALSE;

	return TRUE;
}

void CEmployeesManagementAssistantApp::LoadCustomState()
{
}

int CEmployeesManagementAssistantApp::ExitInstance()
{
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// Methods
// ----------------

BOOL CEmployeesManagementAssistantApp::Login()
{
	EMPLOYEES recEmployeeInput;
	BOOL bIsEmployeeFoundAndValidated = FALSE;

	for (short i = 0; i < ALLOWED_LOGIN_ATTEMPTS; i++)
	{
		CLoginDialog oLoginDialog(recEmployeeInput);
		if (oLoginDialog.DoModal() != IDOK)
			return FALSE;
		
		BOOL bIsBlocked = FALSE;

		if (!CEmployeesData().CheckLoginCredentials(recEmployeeInput, bIsBlocked))
		{
			if (bIsBlocked)
			{
				MessageBox(NULL, gl_strErrorBlockedAccount, gl_strError, MB_ICONERROR);
				return FALSE;
			}

			else
				MessageBox(NULL, gl_strErrorIncorrectCredentials, gl_strError, MB_ICONERROR);

			continue;
		}
		
		bIsEmployeeFoundAndValidated = TRUE;
		break;
	}

	return bIsEmployeeFoundAndValidated;
}

CCurrentUser& CEmployeesManagementAssistantApp::GetCurrentUser()
{
	return m_oCurrentUser;
}

BOOL CEmployeesManagementAssistantApp::InitDocuments()
{
	CMultiDocTemplate* pDocTemplate;

	/////////////////////////////////////////////////////////////////////////////

	pDocTemplate = new CMultiDocTemplate(IDR_EmployeesTYPE,
		RUNTIME_CLASS(CEmployeesDocument),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CEmployeesView));

	if (!pDocTemplate)
		return FALSE;

	AddDocTemplate(pDocTemplate);

	/////////////////////////////////////////////////////////////////////////////

	pDocTemplate = new CMultiDocTemplate(IDR_TasksTYPE,
		RUNTIME_CLASS(CTasksDocument),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CTasksView));

	if (!pDocTemplate)
		return FALSE;

	AddDocTemplate(pDocTemplate);

	/////////////////////////////////////////////////////////////////////////////

	pDocTemplate = new CMultiDocTemplate(IDR_TaskPrioritiesTYPE,
		RUNTIME_CLASS(CTaskPrioritiesDocument),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CTaskPrioritiesView));

	if (!pDocTemplate)
		return FALSE;

	AddDocTemplate(pDocTemplate);

	/////////////////////////////////////////////////////////////////////////////

	pDocTemplate = new CMultiDocTemplate(IDR_TaskStatesTYPE,
		RUNTIME_CLASS(CTaskStatesDocument),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CTaskStatesView));

	if (!pDocTemplate)
		return FALSE;

	AddDocTemplate(pDocTemplate);

	/////////////////////////////////////////////////////////////////////////////

	return TRUE;
}

BOOL CEmployeesManagementAssistantApp::ViewCaller(const CString& strDocumentName)
{
	POSITION pos = m_pDocManager->GetFirstDocTemplatePosition();
	while (pos)
	{
		// Извличане на документа
		CDocTemplate* pTemplate = m_pDocManager->GetNextDocTemplate(pos);
		if (pTemplate == NULL)
			return FALSE;

		// Извличане на името на документа
		CString strName;
		if (pTemplate->GetDocString(strName, CDocTemplate::fileNewName) == 0)
			return FALSE;

		// Проверка дали е търсеният документ
		if (strName == strDocumentName)
			pTemplate->OpenDocumentFile(NULL);
	}

	return TRUE;
}

// Message Handlers
// ----------------

void CEmployeesManagementAssistantApp::OnCommandEmployeeProfile()
{
	EMPLOYEES recEmployee;
	if (!CEmployeesData().ReadRecordByID(GetCurrentUser().GetID(), recEmployee))
	{
		MessageBox(NULL, gl_strErrorLoadingData, gl_strError, MB_ICONERROR);
		return;
	}

	CEmployeesDialog oEmployeesDialog(recEmployee, RecordsActionView);
	oEmployeesDialog.DoModal();
}

void CEmployeesManagementAssistantApp::OnCommandEmployeesView()
{
	if (!ViewCaller(_T("Employees")))
		MessageBox(NULL, gl_strErrorOppeningRegister, gl_strError, MB_ICONERROR);
}

void CEmployeesManagementAssistantApp::OnUpdateCommandUIEmployeesView(CCmdUI* pCmdUI)
{
	if (GetCurrentUser().GetAccessLevel() == EmployeeAccessLevelDirector
		|| GetCurrentUser().GetAccessLevel() == EmployeeAccessLevelAdmin)
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
}

void CEmployeesManagementAssistantApp::OnCommandTasksView()
{
	if (!ViewCaller(_T("Tasks")))
		MessageBox(NULL, gl_strErrorOppeningRegister, gl_strError, MB_ICONERROR);
}

void CEmployeesManagementAssistantApp::OnUpdateCommandUITasksView(CCmdUI* pCmdUI)
{
	if (GetCurrentUser().GetAccessLevel() == EmployeeAccessLevelTeamLeader
		|| GetCurrentUser().GetAccessLevel() == EmployeeAccessLevelDirector
		|| GetCurrentUser().GetAccessLevel() == EmployeeAccessLevelAdmin)
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
}

void CEmployeesManagementAssistantApp::OnCommandTaskPrioritiesView()
{
	if (!ViewCaller(_T("TaskPriorities")))
		MessageBox(NULL, gl_strErrorOppeningRegister, gl_strError, MB_ICONERROR);
}

void CEmployeesManagementAssistantApp::OnUpdateCommandUITaskPrioritiesView(CCmdUI* pCmdUI)
{
	if (GetCurrentUser().GetAccessLevel() == EmployeeAccessLevelDirector
		|| GetCurrentUser().GetAccessLevel() == EmployeeAccessLevelAdmin)
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
}

void CEmployeesManagementAssistantApp::OnCommandTaskStatesView()
{
	if (!ViewCaller(_T("TaskStates")))
		MessageBox(NULL, gl_strErrorOppeningRegister, gl_strError, MB_ICONERROR);
}

void CEmployeesManagementAssistantApp::OnUpdateCommandUITaskStatesView(CCmdUI* pCmdUI)
{
	if (GetCurrentUser().GetAccessLevel() == EmployeeAccessLevelDirector
		|| GetCurrentUser().GetAccessLevel() == EmployeeAccessLevelAdmin)
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
}
