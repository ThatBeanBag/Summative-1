// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: GameStd.cpp
// Desrciption	: GameStd implementation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// Library Includes
#include <limits>	// For FLT_MAX.

// This Include
#include "GameStd.h"	// Creates the GameStd.pch file.

// Local Includes

const int g_kiOPAQUE = 255;
const int g_kiTRANSPARENT = 0;

const int g_kiSCREEN_WIDTH = 600;
const int g_kiSCREEN_HEIGHT = 600;

const int g_kiFRAMES_PER_SEC = 120;
const int g_kiONE_SECOND = 1000;

const int g_kiDRAG_THRESHOLD = 5;

const float g_kfINFINITY = FLT_MAX;

const TColour g_kWHITE = RGB(255, 255, 255);
const TColour g_kBLACK = RGB(0, 0, 0);
const TColour g_kGREEN = RGB(0, 255, 0);