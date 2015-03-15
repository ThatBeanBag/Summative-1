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
#include "TicTacToeHumanView.h"

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

	CHumanView* pHumanView = new CTicTacToeHumanView();

	if (pHumanView) {
		// Create the shared pointer.
		TStrongGameViewPtr pStrongPtr(pHumanView);

		// Add the view.
		AddView(pStrongPtr);
	}

	// Return initialization successful.
	return true;
}

void CTicTacToeLogic::VUpdate(float _fDeltaTime)
{
	CGameLogic::VUpdate(_fDeltaTime);	// Updates the elapsed time.
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

void CTicTacToeLogic::CloseDelegateTest()
{
	g_pApp->DrawLine(CPoint(100, 100), CPoint(300, 300), 255, 0, 0);
}
