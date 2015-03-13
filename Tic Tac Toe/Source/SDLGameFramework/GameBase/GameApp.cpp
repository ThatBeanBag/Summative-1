// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: GameApp.cpp
// Desrciption	: CGameApp implementation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// PCH
#include "GameStd.h"

// Library Includes
#include <time.h>	// For time(0)

// This Include
#include "GameApp.h"

// Local Includes

CGameApp* g_pApp = NULL;

CGameApp::CGameApp()
{
	g_pApp = this;					// This instance is the app of the game.
	m_pGame = NULL;

	m_pWindow = NULL;
	m_pRenderer = NULL;

	m_bIsRunning = false;			// The game is not running yet.
	m_bShowFrameRate = false;
	m_screenSize = CPoint(0,0);
	m_fDeltaTime = 0;
	m_iFrameRate = 0;
}

CGameApp::~CGameApp()
{

}

CPoint CGameApp::VGetScreenSetupSize()
{
	return CPoint(g_kiSCREEN_WIDTH, g_kiSCREEN_HEIGHT);
}

Uint32 CGameApp::VGetWindowStyle()
{
	return SDL_WINDOW_RESIZABLE;
}

bool CGameApp::VInitialize(int _iFrameRate)
{
	m_screenSize = VGetScreenSetupSize();
	m_iFrameRate = _iFrameRate;

	// Initialize SDL.
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		return false;
	}

	// Create the window.
	m_pWindow = SDL_CreateWindow(VGetTitle().c_str(),		// Title.
								 SDL_WINDOWPOS_CENTERED,	// X.
								 SDL_WINDOWPOS_CENTERED,	// Y.
								 m_screenSize.m_iX,			// Width.
								 m_screenSize.m_iY,			// Height.
								 VGetWindowStyle());		// Window flags.

	if(!m_pWindow) {
	// Failed to create the window.
		return false;
	}

	// Create the renderer.
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

	if(!m_pRenderer) {
	// Failed to create the window.
		return false;
	}

	// Get and set the icon.
	SDL_Surface* pIcon = NULL;

	// Load the icon from file.
	pIcon = IMG_Load(VGetIcon().c_str());

	if(pIcon) {
		SDL_SetWindowIcon(m_pWindow, pIcon);
	}

	// Seed the random number generator.
	srand(static_cast<unsigned int>(time(0)));

	m_pGame = VCreateGame();	// Creates and initializes the game.

	if(!m_pGame) {
		return false;
	}

	m_bIsRunning = true;	// The game is now running.

	// Return initialization succeeded.
	return true;
}

void CGameApp::MsgProc(const SDL_Event& event)
{
	switch(event.type) {
		case SDL_QUIT: {
			g_pApp->OnClose();
			break;
		}

		case SDL_WINDOWEVENT: {
			if(event.window.event == SDL_WINDOWEVENT_RESIZED) {
				m_screenSize.m_iX = event.window.data1;
				m_screenSize.m_iY = event.window.data2;
			}

			break;
		}

		//==================================================================
		// Input Events
		//==================================================================

		case SDL_MOUSEMOTION:		// Fall through.
		case SDL_MOUSEBUTTONDOWN:	// Fall through.
		case SDL_MOUSEBUTTONUP:		// Fall through.
		case SDL_KEYDOWN:			// Fall through.
		case SDL_KEYUP: {
			CAppMsg msg;

			msg.type = event.type;
			msg.x = event.motion.x;
			msg.y = event.motion.y;
			msg.button = event.button.button;
			msg.keycode = event.key.keysym.sym;

			if(m_pGame) {
				// Send the msg to the logic and views.
				m_pGame->VMsgProc(msg);
			}
			else {
			// No game.
			}

			break;
		}

		default: break;
	}
	//switch(_msg) {
	//	case WM_CREATE: {
	//		// Do initialization here...

	//		// Return success.
	//		return 0;
	//		break;
	//	}

	//	case WM_COMMAND: {
	//		break;
	//	}

	//	case WM_PAINT: {
	//		HDC hdc;
	//		PAINTSTRUCT ps;

	//		hdc = BeginPaint(_hWnd, &ps);

	//		// Do painting stuff here...

	//		EndPaint(_hWnd, &ps);

	//		// Return success.
	//		return 0;
	//		break;
	//	}
	//	
	//	case WM_SIZE: {
	//		// Get the new screen size.
	//		g_pApp->UpdateScreenSize(CPoint(LOWORD(_lParam), HIWORD(_lParam)));

	//		// Let windows handle the rest.
	//		break;
	//	}

	//	case WM_CLOSE: {
	//		return g_pApp->OnClose();
	//		break;
	//	}

	//	// User Input
	//	case WM_KEYDOWN:		// Fall through.
	//	case WM_KEYUP:			// Fall through.
	//	case WM_MOUSEMOVE:		// Fall through.
	//	case WM_LBUTTONDOWN:	// Fall through.
	//	case WM_LBUTTONUP:		// Fall through.
	//	case WM_RBUTTONDOWN:	// Fall through.
	//	case WM_RBUTTONUP: {
	//		if(g_pApp->m_pGame) {
	//		// The game logic is not NULL.
	//			// Get the game logic.
	//			CGameLogic* pGame = g_pApp->m_pGame;

	//			CAppMsg msg;
	//			msg.m_hWnd = _hWnd;
	//			msg.m_lParam = _lParam;
	//			msg.m_wParam = _wParam;
	//			msg.m_uMsg = _msg;

	//			if(pGame) {
	//				if(pGame->VMsgProc(msg)) {
	//					// Return success.
	//					return 0;
	//				}
	//				else {
	//					break;
	//				}
	//			}
	//			else {
	//				// Couldn't handle message.
	//				break;
	//			}
	//		}
	//		break;
	//	}

	//	default: {
	//		break;
	//	}

	//}

	return;
}

void CGameApp::Update()
{
	Uint32 startTime = SDL_GetTicks();

	SDL_RenderClear(m_pRenderer);

	if(m_pGame) {
		// Update the game logic.
		m_pGame->VUpdate(m_fDeltaTime);
	}

	Render();

	Uint32 elapsedTime = SDL_GetTicks() - startTime;

	// Lock the framerate.
	if(g_kiONE_SECOND / m_iFrameRate > static_cast<float>(elapsedTime)) {
		SDL_Delay(g_kiONE_SECOND / m_iFrameRate - elapsedTime);
	}

	m_fDeltaTime = (static_cast<float>(SDL_GetTicks() - startTime)) / g_kiONE_SECOND;
}

void CGameApp::Render()
{
	SDL_RenderPresent(m_pRenderer);
	SDL_UpdateWindowSurface(m_pWindow);
}

void CGameApp::OnClose()
{
	// Game is now NOT running.
	m_bIsRunning = false;
	
	// Deallocate the game.
	if(m_pGame) {
		delete m_pGame;
	}

	// Destroy the renderer.
	if(m_pRenderer) {
		SDL_DestroyRenderer(m_pRenderer);
		m_pRenderer = NULL;
	}

	// Destroy the window.
	if(m_pWindow) {
		SDL_DestroyWindow(m_pWindow);
		m_pWindow = NULL;
	}

	return;
}

CSprite CGameApp::LoadSprite(const std::string& _krstrFileName)
{
	SDL_Surface* pLoadedImage = NULL;

	pLoadedImage = IMG_Load(_krstrFileName.c_str());

	if(!pLoadedImage) {
	// Failed to load.
		return CSprite();
	}
	else {
	// Successul load.
		// Create and return the sprite.
		return CSprite(pLoadedImage);
	}

	// Free the surface, as it is no longer needed.
	SDL_FreeSurface(pLoadedImage);
}

void CGameApp::RenderSprite(const CSprite& _krSprite, const CPoint& _krPosition, int _iFrame)
{
	SDL_Rect sourceRect;
	SDL_Rect destRect;

	// Get the mask of the frame.
	CRect currentMask = _krSprite.GetMask(_iFrame);

	sourceRect.x = currentMask.m_iX;
	sourceRect.y = currentMask.m_iY;
	sourceRect.w = currentMask.m_iWidth;
	sourceRect.h = currentMask.m_iHeight;

	destRect.x = _krPosition.m_iX;
	destRect.y = _krPosition.m_iY;
	destRect.w = currentMask.m_iWidth;
	destRect.h = currentMask.m_iHeight;

	// Copy the image to the renderer.
	SDL_RenderCopy(m_pRenderer, _krSprite.GetSprite(), &sourceRect, &destRect);
}

void CGameApp::DrawLine(const CPoint& _krPoint1, const CPoint& _krPoint2, 
						int _iR, int _iG, int _iB, int _iA)
{
	// Change the render colour.
	SDL_SetRenderDrawColor(m_pRenderer, _iR, _iG, _iB, _iA);

	// Draw the line between the two points.
	SDL_RenderDrawLine(m_pRenderer, _krPoint1.m_iX, _krPoint1.m_iY, _krPoint2.m_iX, _krPoint2.m_iY);

	// Set the render colour back to it's default of black.
	SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
}

void CGameApp::RenderSprite(const CSprite& _krSprite, int _iX, int _iY, int _iFrame)
{
	// Just call the other overload of this function.
	CGameApp::RenderSprite(_krSprite, CPoint(_iX, _iY), _iFrame);
}

void CGameApp::UpdateScreenSize(const CPoint& _screenSize)
{
	m_screenSize = _screenSize;
}

SDL_Renderer* CGameApp::GetRenderer()
{
	return m_pRenderer;
}

CPoint CGameApp::GetScreenSize() const
{
	return m_screenSize;
}

bool CGameApp::IsRunning() const
{
	return m_bIsRunning;
}

void CGameApp::SetFrameRateShowing(bool _bIsShowing)
{
	m_bShowFrameRate = _bIsShowing;
}

