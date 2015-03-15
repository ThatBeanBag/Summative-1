// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2015 Media Design School
//
// File Name	: Button.h
// Desrciption	: Button declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// PCH
#include "GameStd.h"

// Library Includes

// This Include
#include "Button.h"

// Local Includes

CButton::CButton(CSprite* _pSprite, const CRect& _krRect, TButtonDelegate _delegate, EAnchor _eAnchor)
	:m_pSprite(_pSprite),
	m_buttonRect(_krRect),
	m_delegate(_delegate),
	m_eAnchor(_eAnchor),
	m_eState(eOUT)
{
	OnScreenResize(g_pApp->GetScreenSize());

}

CButton::~CButton() 
{

}

void CButton::OnPressed(const CPoint& _krCursorPosition)
{
	m_eState = ePRESSED;
}

void CButton::OnRelease(const CPoint& _krCursorPosition)
{
	if (IsPointInside(m_buttonRect, _krCursorPosition)) {
		// Call the delegate.
		m_delegate();
	}
}

void CButton::OnMouseMove(const CPoint& _krCursorPosition)
{
	if (IsPointInside(m_buttonRect, _krCursorPosition)) {
		m_eState = eHOVER;
	}
	else if (m_eState != ePRESSED) {
		m_eState = eOUT;
	}
	else {
		// Keep the state as ePRESSED, we don't want to overwrite it.
	}
}

void CButton::OnScreenResize(const CPoint& _krNewSize)
{
	// Adjust the position so that it is anchored correctly.
	if (m_eAnchor == eTOP_RIGHT || m_eAnchor == eBOTTOM_RIGHT) {
		m_buttonRect.m_iX = _krNewSize.m_iX - (m_buttonRect.m_iX + m_buttonRect.m_iWidth);
	}
	
	if (m_eAnchor == eBOTTOM_LEFT || m_eAnchor == eBOTTOM_RIGHT) {
		m_buttonRect.m_iY = _krNewSize.m_iY - (m_buttonRect.m_iY + m_buttonRect.m_iHeight);
	}
	else {
		// No need to change the position of the button.
	}
}

void CButton::Render()
{
	int iFrame = 0;

	if (m_eState == eOUT) {
		iFrame = 1;
	}
	else if (m_eState == eHOVER) {
		iFrame = 2;
	}
	else if (m_eState == ePRESSED) {
		iFrame = 3;
	}

	// Make sure we are inbounds, if the m_pSprite doesn't have 3 frames.
	//iFrame = iFrame % (m_pSprite->GetAllMasks().size() - 1);

	g_pApp->RenderSprite(*m_pSprite, CPoint(m_buttonRect.m_iX, m_buttonRect.m_iY), iFrame);
}
