// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: Console.cpp
// Desrciption	: RedirectIOToConsole implementation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//


// PCH
#include "GameStd.h"

// Library Includes
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <fstream>

// This Include
#include "Console.h"

// Local Includes

// Prepare for gross code.

#ifdef _DEBUG
	void RedirectIOToConsole()
	{
		static const WORD kMAX_CONSOLE_LINES = 500;

		int iConHandle;
		long lStdHandle;

		CONSOLE_SCREEN_BUFFER_INFO conInfo;
		FILE* pFile;

		// Allocate the console for the this application.
		AllocConsole();

		// Set the size of the console so that we can scroll through text. 
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &conInfo);
		conInfo.dwSize.Y = kMAX_CONSOLE_LINES;
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), conInfo.dwSize);

		// Redirect STDOUT to the console.
		lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);	// NOTE: static_cast doesn't work, have to use c-style cast.
		iConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
		pFile = _fdopen(iConHandle, "w");
		*stdout = *pFile;
		setvbuf(stdout, NULL, _IONBF, 0);

		// Redirect STDIN to the console.
		lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
		iConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
		pFile = _fdopen(iConHandle, "r");
		*stdin = *pFile;
		setvbuf(stdin, NULL, _IONBF, 0);

		// Redirect STDERR to the console.
		lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
		iConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
		pFile = _fdopen(iConHandle, "w");
		*stderr = *pFile;
		setvbuf(stderr, NULL, _IONBF, 0);

		// Redirect cout, wcout, cin, wcin, cerr, wcerr, clog and wclog to the console.
		std::ios::sync_with_stdio();
	}
#endif