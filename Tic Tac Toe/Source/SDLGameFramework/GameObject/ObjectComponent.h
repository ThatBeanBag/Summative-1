// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: ObjectComponent.h
// Desrciption	: CObjectComponent declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once

#ifndef __OBJECTCOMPONENT_H__
#define __OBJECTCOMPONENT_H__

// Library Includes

// Local Includes
#include "GameObject.h"

class CObjectComponent {
	// Member Functions
public:
	CObjectComponent();
	virtual ~CObjectComponent();

	virtual bool VInitialize(TiXmlElement* _pXmlData) = 0;
	virtual void VPostInitialize() = 0;
	virtual void VUpdate(float _fDeltaTime) = 0;

	void SetOwner(CGameObject* _pOwner);	// Should only be called by ObjectFactory.
protected:
private:

	// Member Variables
public:
protected:
	CGameObject* m_pOwner;	// A pointer to the owner of this object.
private:
};


#endif