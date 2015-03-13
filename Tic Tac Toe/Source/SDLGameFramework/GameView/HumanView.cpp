// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: HumanView.h
// Desrciption	: CHumanView declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// PCH
#include "GameStd.h"

// Library Includes

// This Include
#include "HumanView.h"

// Local Includes

CHumanView::CHumanView()
	:m_objectId(g_kINVALID_OBJECT_ID),
	m_bIsDragging(false),
	m_bIsLMBDown(false),
	m_bIsRMBDown(false)
{
	m_cursorPosition = CPoint(0, 0);

	memset(m_bKeys, false, sizeof(m_bKeys));
}

CHumanView::~CHumanView()
{

}

void CHumanView::VUpdate(float _fDeltaTime)
{

}

void CHumanView::VRender(float _fDeltaTime)
{
}

bool CHumanView::VMsgProc(const CAppMsg& _krMsg)
{
	//==================================================================
	// Input Events
	//==================================================================
	switch(_krMsg.type) {
		case SDL_MOUSEMOTION: {
			// Update the current mouse position.
			m_cursorPosition.m_iX = _krMsg.x;
			m_cursorPosition.m_iY = _krMsg.y;

			if(m_bIsLMBDown && !m_bIsDragging) {
				CPoint offset = m_cursorPosition - m_dragStartingPosition;

				if(abs(offset.m_iX) > g_kiDRAG_THRESHOLD || abs(offset.m_iY) > g_kiDRAG_THRESHOLD) {
				// Offset is beyond the dragging threshold.
					// Begin dragging.
					m_bIsDragging = true;

					VOnBeginDragging();
				}
				else {
				// Drag threshold has not yet been reached (user might only be clicking).
				}
			}
			break;
		}

		case SDL_MOUSEBUTTONDOWN: {
			if(_krMsg.button == SDL_BUTTON_LEFT) {
			// Left mouse button pressed.
				m_bIsLMBDown = true;

				// We might be about to drag, store the current position.
				m_dragStartingPosition = m_cursorPosition;
			}
			else if(_krMsg.button  == SDL_BUTTON_RIGHT) {
			// Right mouse button pressed.
				m_bIsRMBDown = true;
			}
			else if(_krMsg.button  == SDL_BUTTON_MIDDLE) {
			// Middle mouse button pressed.
			}

			break;
		}
			
		case SDL_MOUSEBUTTONUP: {
			if(_krMsg.button  == SDL_BUTTON_LEFT) {
			// Left mouse button released.
				m_bIsLMBDown = false;

				// No longer are we dragging.
				if(m_bIsDragging) {
					m_bIsDragging = false;
					VOnEndDragging();
				}
			}
			else if(_krMsg.button  == SDL_BUTTON_RIGHT) {
			// Right mouse button released.
				m_bIsRMBDown = false;
			}
			else if(_krMsg.button  == SDL_BUTTON_MIDDLE) {
			// Middle mouse button released.
			}

			break;
		}
		
		case SDL_KEYDOWN: {
			m_bKeys[_krMsg.keycode] = true;

			break;
		}
		case SDL_KEYUP: {
			m_bKeys[_krMsg.keycode] = false;
			break;
		}
		default:break;
	}

	return false;
}

void CHumanView::VOnBeginDragging()
{
	// No implementation.
}

void CHumanView::VOnEndDragging()
{
	// No implementation.
}

void CHumanView::VAttach(TGameObjectId _id)
{
	m_objectId = _id;
}

CPoint CHumanView::GetCursorPosition() const
{
	return m_cursorPosition;
}

CPoint CHumanView::GetDragStartPosition() const
{
	return m_dragStartingPosition;
}

bool CHumanView::GetIsDragging() const
{
	return m_bIsDragging;
}

bool CHumanView::GetIsLMBDown() const
{
	return m_bIsLMBDown;
}

bool CHumanView::GetIsRMBDown() const
{
	return m_bIsRMBDown;
}
