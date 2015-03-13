// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: GameApp.h
// Desrciption	: CGameApp declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once

#ifndef __GAMEAPP_H__
#define __GAMEAPP_H__

// Local Includes
#include "GameLogic.h"
#include "Sprite/Sprite.h"

class CGameApp {
	// Member Functions
public:
	CGameApp();
	virtual ~CGameApp();

	// These functions must be overidden by derived 
	// classes in order to instantiate them.
	virtual CGameLogic* VCreateGame() = 0;
	virtual std::string VGetIcon() = 0;
	virtual std::string VGetTitle() = 0;

	// These two functions are for initialization purposes only,
	// they should be overidden by derived classes to redefined
	// the window size and style.
	virtual CPoint VGetScreenSetupSize();
	virtual Uint32 VGetWindowStyle();

	virtual bool VInitialize(int _iFrameRate = g_kiFRAMES_PER_SEC);

	void MsgProc(const SDL_Event& event); // The message handler.

	// Game Application Functions
	void Update();
	void OnClose();				// Clean up.

	CSprite LoadSprite(const std::string& _krstrFileName);

	void RenderSprite(const CSprite& _sprite, const CPoint& _krPosition, int _iFrame = 0);
	void RenderSprite(const CSprite& _sprite, int _iX, int _iY, int _iFrame = 0);

	void CGameApp::DrawLine(const CPoint& _krPoint1, const CPoint& _krPoint2, 
						    int _iR, int _iG, int _iB, int _iA = SDL_ALPHA_OPAQUE);

	/*void RenderText(const std::string& _krstrText, 
					int _iX, int _iY, 
					TColour _colour, 
					int _iHeight, 
					const std::string& _krstrFont);*/

	void UpdateScreenSize(const CPoint& _screenSize);

	SDL_Renderer* GetRenderer();

	CPoint GetScreenSize() const;
	bool IsRunning() const;

	CPoint GetCursorPosition() const;
	bool IsDragging() const;

	void SetFrameRateShowing(bool _bIsShowing);
protected:
private:
	// Disallow copying.
	CGameApp(const CGameApp& _appOther);
	CGameApp& operator=(const CGameApp& _appOther);

	void Render();

	// Member Variables
public:
	CGameLogic* m_pGame;		// The game logic.

protected:
	SDL_Window* m_pWindow;		// The window.
	SDL_Renderer* m_pRenderer;	// The renderer.

	bool m_bIsRunning;			// True if the app is running, false otherwise.
	bool m_bShowFrameRate;		// True if the frame should be shown, false if not (debug only).
	CPoint m_screenSize;		// The app's screen size.
	float m_fDeltaTime;			// The time of the last tick.
	int m_iFrameRate;			// The frame rate to lock the game tick at in frames per second.
	
private:
};

extern CGameApp* g_pApp;

#endif