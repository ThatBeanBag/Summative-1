// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2015 Media Design School
//
// File Name	: GUIButton.h
// Desrciption	: CGUIButton declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once

#ifndef __GUIBUTTON_H__
#define __GUIBUTTON_H__

// Library Includes

// Local Includes
#include "GUIElement.h"
#include "../3rdParty/fastdelegate/FastDelegate.h"

enum CGUIButtonState {
	eOUT,			// Cursor is outside the button's box.
	eHOVER,			// Cursor is hovering over the button's box.
	ePRESSED		// Cursor is pressed.
};

typedef fastdelegate::FastDelegate0<> TButtonDelegate;

class CGUIButton : public CGUIElement {
	// Member Functions
public:
	CGUIButton(CSprite* _pSprite, const CRect& _krRect, TButtonDelegate _delegate, EGUIAnchor _eAnchor = eTOP_LEFT);
	~CGUIButton();

	// Calls the delegate if _krCursorPosition is within the m_buttonRect rectangle.
	// Checks to see if mouse is hovering over the button and changes the sprite mask appropriately.
	virtual void HandleEvents(const CAppMsg& _krMsg);

	// Draws the button to the screen.
	virtual void VShow();
protected:
private:

	// Member Variables
public:
protected:
private:
	CSprite* m_pSprite;			// The image of the button.
	TButtonDelegate m_delegate;	// The delegate to call if the button is clicked on.

	CGUIButtonState m_eState;		// The state of the button (out, hover or pressed).
};

#endif	// __BUTTON_H__