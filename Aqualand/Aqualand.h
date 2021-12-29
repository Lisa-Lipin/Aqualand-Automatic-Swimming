/**
 * \file Aqualand.h
 *
 * \author Elizabeth Lipin
 *
 * main header file for the Aqualand application
 */
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


/**
* See Aqualand.cpp for the implementation of this class
*/
class CAqualandApp : public CWinApp
{
public:
	CAqualandApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

private:
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken = 0;
};
/// the App itself
extern CAqualandApp theApp;
