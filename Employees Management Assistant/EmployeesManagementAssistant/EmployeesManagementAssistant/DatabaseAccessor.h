
// DatabaseAccessor.h
//

#pragma once

/////////////////////////////////////////////////////////////////////////////
// DBConnectionStatuses

/// <summary> Статуси на връзката с базата данни. </summary>
enum DBConnectionStatuses
{
	DBConnectionStatusDisconnected = 0,
	DBConnectionStatusConnected = 1,
};

/////////////////////////////////////////////////////////////////////////////
// CDatabaseAccessor

/// <summary> Осъществяване на връзка с базата данни </summary>
class CDatabaseAccessor
{
	// Macros
	// ----------------


	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------
	
protected:

	/// <summary> Контруктор. </summary>
	CDatabaseAccessor();

public:

	/// <summary> Деструктор. </summary>
	virtual ~CDatabaseAccessor();

	// Overrides
	// ----------------


	// Methods
	// ----------------
	
public:

	/// <summary> Предотвратяване на копиране на връзката с базата данни. </summary>
	CDatabaseAccessor(CDatabaseAccessor& other) = delete;

	/// <summary> Предотвратяване на присвояване на връзката с базата данни. </summary>
	void operator=(const CDatabaseAccessor& other) = delete;

	/// <summary> Достъпване на връзката с базата данни. </summary>
	/// <returns> Връзката с базата данни. </returns>
	static CDatabaseAccessor* GetInstance();

	/// <summary> Достъпване на източника на данни. </summary>
	/// <returns> Източникът на данни. </returns>
	CDataSource GetDataSource() const;

	/// <summary> Статусът на връзката с базата данни. </summary>
	/// <returns> Връща статуса на връзката с базата данни. </returns>
	const DBConnectionStatuses GetConnectionStatus() const;

	// Members
	// ----------------
	
protected:

	/// <summary> Връзката с базата данни. </summary>
	static CDatabaseAccessor* _pConnection;

private:

	/// <summary> Инстанция на връзката с източника нa данни. </summary>
	CDataSource m_oDataSource;

	/// <summary> Статус на връзката с базата данни. </summary>
	DBConnectionStatuses m_eDBConnectionStatus;
};