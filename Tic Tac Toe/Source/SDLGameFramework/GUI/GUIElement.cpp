// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2015 Media Design School
//
// File Name	: GUIElement.cpp
// Desrciption	: CGUIElement implementation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// PCH
#include "GameStd.h"

// Library Includes

// This Include
#include "GUIElement.h"

// Local Includes

CGUIElement::CGUIElement()
	:m_bIsShown(true),
	m_eAnchor(eTOP_LEFT)
{

}

CGUIElement::CGUIElement(const CRect& _krBoundingBox, EGUIAnchor _eAnchor)
	:m_boundingBox(_krBoundingBox),
	m_eAnchor(_eAnchor),
	m_bIsShown(true)
{

}

CGUIElement::CGUIElement(int _iBoxX, int _iBoxY, int _iBoxWidth, int _iBoxHeight, EGUIAnchor _eAnchor)
	:m_boundingBox(CRect(_iBoxX, _iBoxY, _iBoxWidth, _iBoxHeight)),
	m_eAnchor(_eAnchor),
	m_bIsShown(true)
{

}

CGUIElement::CGUIElement(const CPoint& _krPosition, EGUIAnchor _eAnchor)
	:m_boundingBox(CRect(_krPosition.m_iX, _krPosition.m_iY, 0, 0)),
	m_eAnchor(_eAnchor),
	m_bIsShown(true)
{

}

CGUIElement::~CGUIElement()
{

}

bool CGUIElement::VHandleEvents(const CAppMsg& _krMsg)
{
	return false;
}

void CGUIElement::Show()
{
	m_bIsShown = true;
}

void CGUIElement::Hide()
{
	m_bIsShown = false;
}

CPoint CGUIElement::GetWorldPosition() const 
{
	CPoint worldPosition;	// The position of the element in relation to the world (origin top left).
	CPoint screenSize = g_pApp->GetScreenSize(); // The current screen size.

	worldPosition.m_iX = m_boundingBox.m_iX;
	worldPosition.m_iY = m_boundingBox.m_iY;

	// Adjust the position so that it is anchored correctly.
	if (m_eAnchor == eTOP_RIGHT || m_eAnchor == eBOTTOM_RIGHT) {
		worldPosition.m_iX = screenSize.m_iX - (m_boundingBox.m_iX + m_boundingBox.m_iWidth);
	}

	if (m_eAnchor == eBOTTOM_LEFT || m_eAnchor == eBOTTOM_RIGHT) {
		worldPosition.m_iY = screenSize.m_iY - (m_boundingBox.m_iY + m_boundingBox.m_iHeight);
	}
	else {
		// No need to change the position of the button.
	}

	return worldPosition;
}

CRect CGUIElement::GetWorldRect() const
{
	CRect worldRect = m_boundingBox;			// The rectangle in relation to the world (origin top left).
	CPoint worldPosition = GetWorldPosition();	// The position of the element in relation to the world (origin top left).

	worldRect.m_iX = worldPosition.m_iX;
	worldRect.m_iY = worldPosition.m_iY;

	return worldRect;
}