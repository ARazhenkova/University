
// Encryption.h
//

#pragma once

#include "pch.h"
//#include <ctime>
#include <bcrypt.h>
//#include <ocdb.h>

#pragma comment(lib, "bcrypt.lib")
#include <Windows.h>
#include <string>
#include <iostream>
#include "atlenc.h"

#define HASHING_LENGTH 128
#define HASHING_SALT_LENGTH 16
#define ITERATIONS 10000

#define BASE64_SIZE ceil(4 * (HASHING_LENGTH / 3) + 1)

/////////////////////////////////////////////////////////////////////////////
// CEncryption

/// <summary> Криптиране. </summary>
class CEncryption
{
	// Macros
	// ----------------


	// Constants
	// ----------------
	

	// Constructor / Destructor
	// ----------------

public:

	/// <summary> Контруктор. </summary>
	CEncryption()
	{

	}

	/// <summary> Деструктор. </summary>
	virtual ~CEncryption()
	{
	}

	// Overrides
	// ----------------


	// Methods
	// ----------------

public:

	/// <summary> Хеширане на текст с SHA-512. </summary>
	/// <param name="pPassword"> Нехеширан текст. </param>
	/// <param name="strEncryptedPassword"> Хеширан текст. </param>
	/// <returns> TRUE при успех и FALSE при грешка. </returns>
	static BOOL PBKDF2Hashing(const TCHAR* pPassword, const TCHAR* pSalt, CString& strEncryptedPassword)
	{
		CT2CA pszPassword(pPassword);
		CT2CA pszSalt(pSalt);

		std::string strPassword = pszPassword;
		std::string strSalt = pszSalt;

		BYTE DerivedKey[HASHING_LENGTH];
		BCRYPT_ALG_HANDLE handle;

		NTSTATUS Status = BCryptOpenAlgorithmProvider(&handle, BCRYPT_SHA512_ALGORITHM, NULL, BCRYPT_ALG_HANDLE_HMAC_FLAG);
		if (Status != 0)
			return FALSE;
		
		Status = BCryptDeriveKeyPBKDF2(handle, (BYTE*)strPassword.data(), strPassword.length(), (BYTE*)strSalt.data(), HASHING_SALT_LENGTH, ITERATIONS, DerivedKey, HASHING_LENGTH, 0);
		if (Status != 0)
			return FALSE;

		Status = BCryptCloseAlgorithmProvider(handle, 0);
		if (Status != 0)
			return FALSE;

		// Декодиране
		char Dest[256];
		int DestLen = 256;
		BOOL rc = Base64Encode(DerivedKey, sizeof(DerivedKey), Dest, &DestLen);
		Dest[DestLen] = '\0';

		strEncryptedPassword.Format(_T("%s"), CString(Dest));

		return TRUE;
	}

	// Members
	// ----------------

};
