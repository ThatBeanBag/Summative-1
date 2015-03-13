// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: GameView.h
// Desrciption	: CGameView declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once

#ifndef __GAMEVIEW_H__
#define __GAMEVIEW_H__

// Library Includes

// Local Includes

struct CAppMsg {
	Uint32 type;			// Type of the event.
	Sint32 x;				// X coordinate
	Sint32 y;				// Y coordinate
	Uint8 button;			// The button that changed.
	Uint8 clicks;			// Amount of clicks. 
	SDL_Keycode keycode;	// The virtual key code that was pressed/released.

};

class IGameView {
	// Member Functions
public:
	virtual void VUpdate(float _fDeltaTime) = 0;
	virtual void VRender(float _fDeltaTime) = 0;
	virtual bool VMsgProc(const CAppMsg& _krMsg) = 0;

	virtual void VAttach(TGameObjectId _id) = 0;
protected:
private:

	// Member Variables
public:
protected:
private:
};

//
typedef shared_ptr<IGameView> TStrongGameViewPtr;

// Game views are implemented in a list data structure
// for ease of insertion and deletion.
typedef std::list<TStrongGameViewPtr> TGameViewList;

#endif