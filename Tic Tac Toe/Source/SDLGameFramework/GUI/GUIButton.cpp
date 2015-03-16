// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2015 Media Design School
//
// File Name	: GUIButton.cpp
// Desrciption	: CGUIButton implementation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// PCH
#include "GameStd.h"

// Library Includes

// This Include
#include "GUIButton.h"

// Local Includes

CGUIButton::CGUIButton(CSprite* _pSprite, const CRect& _krRect, TButtonDelegate _delegate, EGUIAnchor _eAnchor)
	:CGUIElement(_krRect, _eAnchor),
	m_pSprite(_pSprite),
	m_delegate(_delegate),
	m_eState(eOUT)
{

}

CGUIButton::~CGUIButton()
{

}

void CGUIButton::HandleEvents(const CAppMsg& _krMsg)
{
	CPoint cursorPosition(_krMsg.x, _krMsg.y);

	switch (_krMsg.type) {
	case SDL_MOUSEMOTION: {
		if (IsPointInside(GetWorldRect(), cursorPosition)) {
			m_eState = eHOVER;
		}
		else if (m_eState != ePRESSED) {
			m_eState = eOUT;
		}
		else {
			// Keep the state as ePRESSED, we don't want to overwrite it.
		}

		break;
	}

	case SDL_MOUSEBUTTONDOWN: {
		if (IsPointInside(GetWorldRect(), cursorPosition)) {
			m_eState = ePRESSED;
		}

		break;
	}

	case SDL_MOUSEBUTTONUP: {
		if (IsPointInside(GetWorldRect(), cursorPosition)) {
			// Call the delegate.
			m_delegate();
		}

		break;
	}
	default:break;
	}
}

void CGUIButton::VShow()
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

	if (iFrame >= m_pSprite->GetAllMasks().size()) {
		iFrame = m_pSprite->GetAllMasks().size() - 1;
	}

	g_pApp->RenderSprite(*m_pSprite, GetWorldPosition(), iFrame);
}
