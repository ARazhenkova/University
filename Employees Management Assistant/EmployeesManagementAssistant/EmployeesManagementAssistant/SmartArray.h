
// SmartArray.h
//

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CSmartArray

/// <summary> Надграждане на базовия клас за масив. </summary>
template<typename TYPE>
class CSmartPtrArray : public CTypedPtrArray<CPtrArray, TYPE*>
{
	// Macros
	// ----------------


	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------
	
public:
	
	/// <summary> Контруктор. </summary>
	CSmartPtrArray()
	{
		
	}
	
	/// <summary> Деструктор. </summary>
	virtual ~CSmartPtrArray()
	{
		DeleteAll();
	}

	// Overrides
	// ----------------


	// Methods
	// ----------------
	
public:

	/// <summary> Изтриване на всички елементи от масива. </summary>
	void DeleteAll()
	{
		for (INT_PTR i = 0; i < this->GetCount(); i++)
		{
			delete this->GetAt(i);
			this->SetAt(i, NULL);
		}
		this->RemoveAll();
	}

	/// <summary> Изтриване на елемент от масива. </summary>
	/// <param name="Index"> Индекса на елемента за изтриване. </param>
	void DeleteAt(const INT_PTR Index)
	{
		delete this->GetAt(Index);
		this->SetAt(Index, NULL);
		this->RemoveAt(Index);
	}

	/// <summary> Търсене на елемент в масива. </summary>
	/// <param name="lID"> Идентификационен номер, по който ще се търси. </param>
	/// <param name="recType"> Намереният елемент. </param>
	INT_PTR Search(const long lID)
	{
		for (INT_PTR i = 0; i < this->GetCount(); i++)
		{
			TYPE* pTYPE = this->GetAt(i);
			if (pTYPE == NULL)
				return INT_ERROR;

			if (pTYPE->lID != lID)
				continue;

			return i;
		}

		return INT_ERROR;
	}

	// Members
	// ----------------

};