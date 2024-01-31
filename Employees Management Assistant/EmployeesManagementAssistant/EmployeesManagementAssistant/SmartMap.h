
// SmartMap.h
//

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CSmartMap

/// <summary> Надграждане на базовия клас за мап. </summary>
template<typename KEY, typename VALUE>
class CSmartMap : public CMap<KEY, KEY, VALUE*, VALUE*>
{
	// Macros
	// ----------------


	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------
	
public:

	/// <summary> Контруктор. </summary>
	CSmartMap()
	{
	}

	/// <summary> Деструктор. </summary>
	virtual ~CSmartMap()
	{
		DeleteAll();
	}

	// Methods
	// ----------------
	
public:

	/// <summary> Изтриване на всички елементи. </summary>
	void DeleteAll()
	{
		POSITION oPosition = this->GetStartPosition();
		KEY key = 0;
		VALUE* value = NULL;
		while (oPosition)
		{
			this->GetNextAssoc(oPosition, key, value);
			delete value;
			value = NULL;
		}
		this->RemoveAll();
	}

	// Members
	// ----------------
};