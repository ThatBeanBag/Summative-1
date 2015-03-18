// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2015 Media Design School
//
// File Name	: TicTacToeHumanView.h
// Desrciption	: CTicTacToeHumanView declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once

#ifndef __TICTACTOEHUMANVIEW_H__
#define __TICTACTOEHUMANVIEW_H__

// Library Includes

// Local Includes
#include "BoardState.h"

class CTicTacToeHumanView : public CHumanView {
	// Member Functions
public:
	CTicTacToeHumanView();
	virtual ~CTicTacToeHumanView();

	virtual void VUpdate(float _fDeltaTime);
	virtual void VRender(float _fDeltaTime);
	virtual bool VMsgProc(const CAppMsg& _krMsg);

	// Delegates Functions
	void MoveTopLeft();
	void MoveTopMiddle();
	void MoveTopRight();
	void MoveMiddleLeft();
	void MoveMiddleMiddle();
	void MoveMiddleRight();
	void MoveBottomLeft();
	void MoveBottomMiddle();
	void MoveBottomRight();
	void StartOverComputer();
	void StartOverPlayer();
	void Unbeatable();
	void Easy();
protected:
private:

	// Member Variables
public:
protected:
private:
	CSprite m_background;
	CSprite m_naughtSprite;
	CSprite m_crossSprite;
	CSprite m_youWinSprite;
	CSprite m_youLoseSprite;
	CSprite m_drawSprite;
	CBasicGUI m_guiBoard;
	CBasicGUI m_guiAi;
	CBasicGUI m_guiStart;
	CBasicGUI m_guiStartOver;

	CBoardState m_boardState;

	bool m_bComputerStart;
	bool m_bIsComputerEasy;
};

#endif // __TICTACTOEHUMANVIEW_H__