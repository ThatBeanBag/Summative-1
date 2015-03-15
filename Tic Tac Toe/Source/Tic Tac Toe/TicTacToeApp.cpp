// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2015 Media Design School
//
// File Name	: TicTacToeApp.cpp
// Desrciption	: TicTacToeApp implementation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// PCH
#include "TicTacToeStd.h"

// Library Includes

// This Include
#include "TicTacToeApp.h"

// Local Includes
#include "TicTacToeLogic.h"

CTicTacToeApp g_ticTacToeApp;	// g_pApp will become this.

CTicTacToeApp::CTicTacToeApp()
{

}

CGameLogic* CTicTacToeApp::VCreateGame()
{
	// Create the game logic.
	CGameLogic* pGame = new CTicTacToeLogic();

	// Initialize the game.
	if (pGame->VInit()) {
	// Initialization successful.
		return pGame;
	}
	else {
	// Failed to initialize, return NULL pointer - CGameApp will handle the rest.
		return NULL;
	}

	return pGame;
}

std::string CTicTacToeApp::VGetIcon()
{
	return std::string("Tic Tac Toe.ico");
}

std::string CTicTacToeApp::VGetTitle()
{
	return std::string("Tic Tac Toe");
}

CPoint CTicTacToeApp::VGetScreenSetupSize()
{
	return CPoint(g_kiTICTACTOE_SCREEN_WIDTH, g_kiTICTACTOE_SCREEN_HEIGHT);
}

Uint32 CTicTacToeApp::VGetWindowStyle()
{
	return SDL_WINDOW_SHOWN;
}
