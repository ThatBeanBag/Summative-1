// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2015 Media Design School
//
// File Name	: TicTacToeLogic.h
// Desrciption	: TicTacToeLogic declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once

#ifndef __TICTACTOELOGIC_H__
#define __TICTACTOELOGIC_H__

// Library Includes

// Local Includes
#include "BoardState.h"

class CTicTacToeLogic : public CGameLogic {
	// Member Functions
public:
	CTicTacToeLogic();

	virtual ~CTicTacToeLogic();

	// Initializes all Tic Tac Toe logic specific subsystems and variables.
	// Also calls CGameLogic::VInit().
	virtual bool VInit();

	// Updates the Tic Tac Toe logic and it's subsystems and calls CGameLogic::VUpdate().
	virtual void VUpdate(float _fDeltaTime);

	// Manages the effect of the state change within the tic tac toe logic then calls
	// CGameLogic::VChangeState() to update the internal state representation.
	virtual void VChangeState(EGameState _eState);
protected:
private:

	// Member Variables
public:
protected:
private:
};

#endif // __TICTACTOELOGIC_H__