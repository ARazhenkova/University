
// DateTime.h
//

#pragma once

#include "pch.h"

/////////////////////////////////////////////////////////////////////////////
// CDateTime

/// <summary> За работа с дата и час. </summary>
class CDateTime
{

public:

	/// <summary> Вземане на текущата дата като низ. </summary>
	/// <returns> Преобразуваният низа. </returns>
	static CString CurrentDataTimeToString()
	{
		try
		{
			CString strResult;
			COleDateTime oDateTime = COleDateTime::GetCurrentTime();

			int nDay = oDateTime.GetDay();
			if (nDay < 10) 
				strResult.Format(_T("0%d"), nDay);
			else 
				strResult.Format(_T("%d"), nDay);

			int nMonth = oDateTime.GetMonth();
			if (nMonth < 10)
				strResult.Format(_T("%s-0%d"), strResult, nMonth);
			else
				strResult.Format(_T("%s-%d"), strResult, nMonth);

			int nYear = oDateTime.GetYear();
			strResult.Format(_T("%s-%d"), strResult, nYear);

			int nHour = oDateTime.GetHour();
			if (nHour < 10)
				strResult.Format(_T("%s 0%d"), strResult, nHour);
			else
				strResult.Format(_T("%s %d"), strResult, nHour);

			int nMinute = oDateTime.GetMinute();
			if (nMinute < 10)
				strResult.Format(_T("%s:0%d"), strResult, nMinute);
			else
				strResult.Format(_T("%s:%d"), strResult, nMinute);

			int nSecond = oDateTime.GetSecond();
			if (nSecond < 10)
				strResult.Format(_T("%s:0%d"), strResult, nSecond);
			else
				strResult.Format(_T("%s:%d"), strResult, nSecond);

			return strResult;
		}
		catch (...)
		{
			return _T("");
		}
	}
};
