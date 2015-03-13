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

#ifndef __GAMELOGIC_H__
#define __GAMELOGIC_H__

// Library Includes

// Local Includes
#include "Sprite/Sprite.h"
#include "../Renderer/Renderer.h"
#include "../Physics/Physics.h"
#include "../Events/EventManager.h"
#include "../GameObject/ObjectFactory.h"
#include "../GameView/HumanView.h"
#include "../GameView/GameView.h"

enum EGameState {
	GS_Invalid,
	GS_Initializing,
	GS_TitleScreen,
	GS_MainMenu,
	GS_HighScore,
	GS_Options,
	GS_Running
};

typedef std::map<TGameObjectId, CGameObject*> TGameObjectMap;

class CGameLogic {
	// Member Functions
public:
	CGameLogic();
	virtual ~CGameLogic();

	virtual bool VInit();
	virtual void VUpdate(float _fDeltaTime);
	virtual void VChangeState(EGameState _eState);
	
	virtual bool VMsgProc(const CAppMsg& _krMsg);

	void Render(float _fDeltaTime);		// Renders the views.

	CRenderer* GetRenderer();
	CPhysics* GetPhysics();

	CGameObject* CreateGameObject(const std::string& _krObjectResource);
	CGameObject* GetGameObject(TGameObjectId _id);
	void DestroyGameObject(TGameObjectId _id);

	void AddView(TStrongGameViewPtr _pView, TGameObjectId _id = g_kINVALID_OBJECT_ID);
	void RemoveView(TStrongGameViewPtr _pView);

	virtual void VRegisterEventListeners();
	virtual void VRemoveEventListeners();

	// Event Listeners
	void DestroyObjectListener(TEventDataPtr _pEventData);
	void MoveObjectListener(TEventDataPtr _pEventData);
protected:
	virtual CObjectFactory* VCreateObjectFactory();
private:

	// Member Variables
public:
protected:
	float m_fElapsedTime;		// The amount of time elapsed since the game started.

	CRenderer* m_pRenderer;		// The renderer of the game, manages sprites and drawing to the screen.
	CPhysics* m_pPhysics;		// The physics engine, currently just registers objects and checks collisions.

	CObjectFactory* m_pObjectFactory;
	TGameObjectMap m_gameObjects;

	TGameViewList m_gameViews;	// The views of the game.
	EGameState m_eState;		// The current state or screen of the game.
private:
};

#endif