// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: GameStd.h
// Desrciption	: GameStd declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

//---------------------------------------------------------
// GameStd.h:
//
// This file is a precompiled header and includes many 
// standard files that are used frequently.
//
// It also defines many useful constants and typedefs that 
// are used throughout the code base.
//---------------------------------------------------------

#pragma once
//
#ifndef __GAMESTD_H__
#define __GAMESTD_H__

// Library Includes
//#include <Windows.h>
//#include <WindowsX.h>
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <memory>
#include <assert.h>
#include <vector>
#include <list>
#include <map>
#include <string>

#include <tinyxml.h>
#include <vld.h>	// Leak detection.

using std::tr1::shared_ptr;
using std::tr1::static_pointer_cast;

// Useful Constants
extern const int g_kiOPAQUE;
extern const int g_kiTRANSPARENT;

extern const int g_kiSCREEN_WIDTH;
extern const int g_kiSCREEN_HEIGHT;

extern const int g_kiFRAMES_PER_SEC;
extern const int g_kiONE_SECOND;

extern const int g_kiDRAG_THRESHOLD;

extern const float g_kfINFINITY;

// Useful Typedefs
typedef COLORREF TColour;

extern const TColour g_kBLACK;
extern const TColour g_kWHITE;
extern const TColour g_kGREEN;

// Local Includes
#include "Utilities\Point.h"
#include "Utilities\Rect.h"
#include "Utilities\Utilities.h"
#include "Events\EventManager.h"
#include "GameBase\GameApp.h"

#endif