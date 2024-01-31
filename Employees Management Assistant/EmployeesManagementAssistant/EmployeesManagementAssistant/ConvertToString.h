
// ConvertToString.h
//

#pragma once

#include "pch.h"

/////////////////////////////////////////////////////////////////////////////
// CConvertToString

/// <summary> Преобразуване на различни типове в низ. </summary>
class CConvertToString
{
public:

	/// <summary> Преобразуване на число в низ. </summary>
	/// <param name="dValue"> Число. </param>
	/// <returns> Преобразуваният низа. </returns>
	static CString Convert(const short lValue)
	{
		CString strResult;
		
		strResult.Format(_T("%d"), lValue);

		return strResult;
	}

	/// <summary> Преобразуване на число в низ. </summary>
	/// <param name="dValue"> Число. </param>
	/// <returns> Преобразуваният низа. </returns>
	static CString Convert(const long lValue)
	{
		CString strResult;
		
		strResult.Format(_T("%d"), lValue);

		return strResult;
	}

	/// <summary> Преобразуване на дробно число в низ. </summary>
	/// <param name="dValue"> Дробно число. </param>
	/// <param name="sPrecision"> Прецизност след десетичната запетайка. </param>	
	/// <returns> Преобразуваният низа. </returns>
	static CString Convert(const double dValue, short sPrecision = INT_ERROR)
	{
		CString strResult;

		if (sPrecision == INT_ERROR)
		{
			strResult.Format(_T("%f"), dValue);
		}
		else
		{
			strResult.Format(_T("%.*f"), sPrecision, dValue);
		}

		return strResult;
	}
};
