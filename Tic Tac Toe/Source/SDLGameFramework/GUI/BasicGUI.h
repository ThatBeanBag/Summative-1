// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2015 Media Design School
//
// File Name	: BasicGUI.h
// Desrciption	: CBasicGUI declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once 

#ifndef __BASICGUI_H__
#define __BASICGUI_H__

// Library Includes

// Local Includes
#include "GUIButton.h"

class CBasicGUI {
	// Member Functions
public:
	CBasicGUI();
	~CBasicGUI();

	// Calls OnPressed() for all buttons and statics in the GUI.
	void OnPressed(const CPoint& _krCursorPosition);

	// Calls OnRelease() for all buttons and statics in the GUI.
	void OnRelease(const CPoint& _krCursorPosition);

	// Calls OnMouseMove() for all buttons and statics in the GUI.
	void OnMouseMove(const CPoint& _krCursorPosition);

	// Calls OnScreenResize for all buttons and statics in the GUI.
	void OnScreenResize(const CPoint& _krNewSize);
protected:
private:

	// Member Variables
public:
protected:
private:
	std::vector<CGUIButton> m_buttons;
	std::vector<CGUIStatic> m_statics;
	std::vector<CSprite> m_sprites;
};

#endif // __BASICGUI_H__

