// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: RenderComponent.h
// Desrciption	: CRenderComponent declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once

#ifndef __RENDERCOMPONENT_H__
#define __RENDERCOMPONENT_H__

// Library Includes

// Local Includes
#include "ObjectComponent.h"

class CRenderComponent : public CObjectComponent {
	// Member Functions
public:
	CRenderComponent();
	~CRenderComponent();

	virtual bool VInitialize(TiXmlElement* _pXmlData);
	virtual void VPostInitialize();
	virtual void VUpdate(float _fDeltaTime);

	void Render();

	// Accessors
	CSprite* GetSprite() const;
protected:
private:

	// Member Variables
public:
protected:
private:
	CSprite* m_pSprite;		// A reference to the sprite to render, managed by the Renderer.

	int m_iLayer;			// The layer to render this object on.
};

TStrongObjectComponentPtr CreateRenderComponent();

#endif