
// CurrentUser.cpp
//

#include "pch.h"
#include "CurrentUser.h"

/////////////////////////////////////////////////////////////////////////////
// CCurrentUser

CCurrentUser::CCurrentUser() : m_lID(0), m_eAccessLevel(EmployeeAccessLevelUndefined)
{
}

CCurrentUser::~CCurrentUser()
{

}

// Overrides
// ----------------


// Methods
// ----------------

void CCurrentUser::Initialize(const long lID, const EmployeeAccessLevels eAccessLevel)
{
	m_lID = lID;
	m_eAccessLevel = eAccessLevel;
}

const long CCurrentUser::GetID() const
{
	return m_lID;
}

const EmployeeAccessLevels CCurrentUser::GetAccessLevel() const
{
	return m_eAccessLevel;
}

CString CCurrentUser::PreparePersonalKey(const TCHAR* pIdentifier)
{
	CString strSalt;
	COleDateTime oDateTime = COleDateTime::GetCurrentTime();

	strSalt.Format(_T("%f"), oDateTime.m_dt);
	strSalt.Replace(_T("."), _T("-"));
	strSalt.Format(_T("%s-%c%c%c"), strSalt, pIdentifier[9], pIdentifier[8], pIdentifier[7]);

	return strSalt;
}
