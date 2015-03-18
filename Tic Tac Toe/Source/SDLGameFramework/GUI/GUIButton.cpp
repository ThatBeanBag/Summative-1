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

CGUIButton::CGUIButton(CSprite* _pSprite, const CRect& _krRect, const TButtonDelegate& _krDelegate, EGUIAnchor _eAnchor)
	:CGUIElement(_krRect, _eAnchor),
	m_pSprite(_pSprite),
	m_delegate(_krDelegate),
	m_eState(eOUT)
{

}

CGUIButton::~CGUIButton()
{

}

void CGUIButton::VRender()
{
	if (!m_bIsShown) {
		// Don't show if this button is not enabled.
		return;
	}

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

	if (iFrame >= static_cast<int>(m_pSprite->GetAllMasks().size())) {
		iFrame = m_pSprite->GetAllMasks().size() - 1;
	}

	g_pApp->RenderSprite(*m_pSprite, GetWorldPosition(), iFrame);
}

bool CGUIButton::VHandleEvents(const CAppMsg& _krMsg)
{
	// Don't handle events if this button is not shown.
	if (!m_bIsShown) {
		return false;
	}

	CPoint cursorPosition(_krMsg.x, _krMsg.y);

	switch (_krMsg.type) {
	case SDL_MOUSEMOTION: {
		if (IsPointInside(GetWorldRect(), cursorPosition) && m_eState != ePRESSED) {
			m_eState = eHOVER;
		}
		else {
			m_eState = eOUT;
		}

		break;
	}

	case SDL_MOUSEBUTTONDOWN: {
		if (_krMsg.button == SDL_BUTTON_LEFT) {
			if (IsPointInside(GetWorldRect(), cursorPosition)) {
				m_eState = ePRESSED;
			}
		}

		break;
	}

	case SDL_MOUSEBUTTONUP: {
		if (_krMsg.button == SDL_BUTTON_LEFT) {
			if (IsPointInside(GetWorldRect(), cursorPosition)) {
				// Call the delegate.
				m_delegate();

				return true;
			}
		}

		break;
	}
	default:break;
	}

	return false;
}

void CGUIButton::VHide()
{
	CGUIElement::VHide();

	m_eState = eOUT;
}
