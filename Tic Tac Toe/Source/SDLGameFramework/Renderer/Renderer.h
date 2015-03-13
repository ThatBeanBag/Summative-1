// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: Renderer.h
// Desrciption	: CRenderer declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once

#ifndef __RENDERER_H__
#define __RENDERER_H__

// Library Includes

// Local Includes
#include "../GameObject/GameObject.h"

typedef std::map<std::string, CSprite*> TResourceToSpriteMap;
typedef std::map<int, std::list<TGameObjectId> > TLayerObjectIdMap;

class CRenderer {
	// Member Functions
public:
	CRenderer();
	~CRenderer();

	void RenderGameObjects();

	void RegisterObject(CGameObject* _pObject, int _iLayer);
	void DeregisterObject(TGameObjectId _id);
	CSprite* GetSprite(const std::string& _krstrFile);	// Retrieves the sprite of the given file, creates if not already created.
protected:
private:

	// Member Variables
public:
protected:
private:
	TLayerObjectIdMap m_registeredObjects;

	TResourceToSpriteMap m_sprites;
};

#endif