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

#pragma once

#ifndef __HUMANVIEW_H__
#define __HUMANVIEW_H__

// Library Includes

// Local Includes
#include "GameView.h"

class CHumanView : public IGameView {
	// Member Functions
public:
	CHumanView();
	virtual ~CHumanView();

	virtual void VUpdate(float _fDeltaTime);
	virtual void VRender(float _fDeltaTime);
	virtual bool VMsgProc(const CAppMsg& _krMsg);

	virtual void VOnBeginDragging();
	virtual void VOnEndDragging();

	virtual void VAttach(TGameObjectId _id);

	// Accessors
	CPoint GetCursorPosition() const;
	CPoint GetDragStartPosition() const;
	bool GetIsDragging() const;
	bool GetIsLMBDown() const;
	bool GetIsRMBDown() const;
protected:
private:

	// Member Variables
public:
protected:
	TGameObjectId m_objectId;

	// Input
	bool m_bKeys[256];	// The states of each key (up or down).

	CPoint m_cursorPosition;		// The current cursor position.
	CPoint m_dragStartingPosition;	// The position at which a drag may have begun.
	bool m_bIsDragging;				// True if the user is holding down LMB and moving mouse around, false otherwise.
	bool m_bIsLMBDown;				// True if the left mouse button is down, false otherwise.
	bool m_bIsRMBDown;				// True if the right mouse button is down, false otherwise.
private:
};

#endif