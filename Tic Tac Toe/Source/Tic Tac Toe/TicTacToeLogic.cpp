// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2015 Media Design School
//
// File Name	: TicTacToeLogic.cpp
// Desrciption	: TicTacToeLogic implementation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// PCH
#include "TicTacToeStd.h"

// Library Includes

// This Include
#include "TicTacToeLogic.h"

// Local Includes

CTicTacToeLogic::CTicTacToeLogic()
{

}

CTicTacToeLogic::~CTicTacToeLogic()
{

}

bool CTicTacToeLogic::VInit()
{
	// Initialize the base game logic first.
	if (!CGameLogic::VInit()) {
	// Failed to initialize base game logic.
		// Return initialization failed.
		return false;
	}



	// Return initialization successful.
	return true;
}

void CTicTacToeLogic::VUpdate(float _fDeltaTime)
{
	CGameLogic::VUpdate(_fDeltaTime);	// Updates the elapsed time.

	CBoardState boardState;

	boardState.GetWinner();
}

void CTicTacToeLogic::VChangeState(EGameState _eState)
{
	switch (_eState) {

		default: {
			break;
		}
	}

	CGameLogic::VChangeState(_eState);
}

