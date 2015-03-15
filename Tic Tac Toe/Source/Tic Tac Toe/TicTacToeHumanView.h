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

class CTicTacToeHumanView : public CHumanView {
	// Member Functions
public:
	CTicTacToeHumanView();
	virtual ~CTicTacToeHumanView();

	virtual void VUpdate(float _fDeltaTime);
	virtual bool VMsgProc(const CAppMsg& _krMsg);
protected:
private:

	// Member Variables
public:
protected:
private:
	CSprite m_background;
	CSprite m_sprite;
	CSprite m_sprite2;
	CButton m_buttonTest;
	CButton m_buttonTest2;
};

#endif // __TICTACTOEHUMANVIEW_H__