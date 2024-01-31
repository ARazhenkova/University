
// DatabaseAccessor.cpp
//

#include "pch.h"
#include "DatabaseAccessor.h"
#include "Encryption.h"

CDatabaseAccessor* CDatabaseAccessor::_pConnection = NULL;

/////////////////////////////////////////////////////////////////////////////
// CDatabaseAccessor

// Constructor / Destructor
// ----------------

CDatabaseAccessor::CDatabaseAccessor()
{
	m_eDBConnectionStatus = DBConnectionStatusDisconnected;
	
	TCHAR szDataSource				[CHAR_SIZE_128];
	TCHAR szInitialCatalog			[CHAR_SIZE_128];
	TCHAR szEncryptData				[CHAR_SIZE_6];
	TCHAR szUserID					[CHAR_SIZE_128];
	TCHAR szPassword				[CHAR_SIZE_128];

	GetPrivateProfileString(_T("Data Source")	, _T("Server name")			, _T("")	, szDataSource			, CHAR_SIZE_128		, gl_ServerConfigPath);
	GetPrivateProfileString(_T("Data Source")	, _T("Database name")		, _T("")	, szInitialCatalog		, CHAR_SIZE_128		, gl_ServerConfigPath);
	GetPrivateProfileString(_T("Data Source")	, _T("Encrypt data")		, _T("")	, szEncryptData			, CHAR_SIZE_6		, gl_ServerConfigPath);
	GetPrivateProfileString(_T("Credentials")	, _T("Login")				, _T("")	, szUserID				, CHAR_SIZE_128		, gl_ServerConfigPath);
	GetPrivateProfileString(_T("Credentials")	, _T("Password")			, _T("")	, szPassword			, CHAR_SIZE_128		, gl_ServerConfigPath);

	CString strInitializationString;
	strInitializationString.Format(_T("Provider=SQLOLEDB;Data Source=%s;Password=%s;Persist Security Info=True;User ID=%s;Initial Catalog=%s;Use Encryption for Data=%s;Trust Server Certificate=%s")
		, szDataSource, szPassword, szUserID, szInitialCatalog, szEncryptData, szEncryptData);

	HRESULT	hResult = m_oDataSource.OpenFromInitializationString(strInitializationString);

	if (SUCCEEDED(hResult))
		m_eDBConnectionStatus = DBConnectionStatusConnected;
}

CDatabaseAccessor::~CDatabaseAccessor()
{
	if (m_eDBConnectionStatus == DBConnectionStatusConnected)
		m_oDataSource.Close();

	if (_pConnection != NULL)
	{
		delete _pConnection;
		_pConnection = NULL;
	}
}

// Overrides
// ----------------


// Methods
// ----------------

CDatabaseAccessor* CDatabaseAccessor::GetInstance()
{
	if (_pConnection == NULL) 
	{
		_pConnection = new CDatabaseAccessor();
	}
	
	return _pConnection;
}

CDataSource CDatabaseAccessor::GetDataSource() const
{
	return m_oDataSource;
}

const DBConnectionStatuses CDatabaseAccessor::GetConnectionStatus() const
{
	return m_eDBConnectionStatus;
}
