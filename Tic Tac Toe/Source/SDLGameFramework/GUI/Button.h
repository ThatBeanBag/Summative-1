// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2015 Media Design School
//
// File Name	: Button.h
// Desrciption	: CButton declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once

#ifndef __BUTTON_H__
#define __BUTTON_H__

// Library Includes

// Local Includes
#include "../3rdParty/fastdelegate/FastDelegate.h"

enum EAnchor {
	eTOP_LEFT,
	eTOP_RIGHT,
	eBOTTOM_LEFT,
	eBOTTOM_RIGHT
};

enum CButtonState {
	eOUT,			// Cursor is outside the button's box.
	eHOVER,			// Cursor is hovering over the button's box.
	ePRESSED		// Cursor is pressed.
};

typedef fastdelegate::FastDelegate0<> TButtonDelegate;

class CButton {
	// Member Functions
public:
	CButton(CSprite* _pSprite, const CRect& _krRect, TButtonDelegate _delegate,  EAnchor _eAnchor = eTOP_LEFT);
	~CButton();

	void OnPressed(const CPoint& _krCursorPosition);

	// Calls the delegate if _krCursorPosition is within the m_buttonRect rectangle.
	void OnRelease(const CPoint& _krCursorPosition);

	// Checks to see if mouse is hovering over the button and changes the sprite mask appropriately.
	void OnMouseMove(const CPoint& _krCursorPosition);

	// Moves the position of the object based on it's anchor point and the new size of the window.
	void OnScreenResize(const CPoint& _krNewSize);

	// Draws the button to the screen.
	void Render();
protected:
private:

	// Member Variables
public:
protected:
private:
	CSprite* m_pSprite;			// The image of the button.
	CRect m_buttonRect;			// The rectangular box that defines the collision for mouse over and on click events.
	TButtonDelegate m_delegate;	// The delegate to call if the button is clicked on.
	EAnchor m_eAnchor;			// Defines where to anchor the position of the button from.

	CButtonState m_eState;		// The state of the button (out, hover or pressed).
};

#endif	// __BUTTON_H__