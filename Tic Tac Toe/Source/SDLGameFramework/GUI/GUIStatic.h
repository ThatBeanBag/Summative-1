// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2015 Media Design School
//
// File Name	: GUIStatic.h
// Desrciption	: CGUIStatic declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once

#ifndef __GUISTATIC_H__
#define __GUISTATIC_H__

// Library Includes

// Local Includes
#include "GUIElement.h"

class CGUIStatic : public CGUIElement {
	// Member Functions
public:
	CGUIStatic(CSprite* _pSprite, const CRect& _kBoundingBox, EGUIAnchor _eAnchor = eTOP_LEFT);
	~CGUIStatic();

	// Draws the static image to the screen.
	virtual void VRender();
protected:
private:

	// Member Variables
public:
protected:
private:
	CSprite* m_pSprite;
};

#endif	// __GUISTATIC_H__