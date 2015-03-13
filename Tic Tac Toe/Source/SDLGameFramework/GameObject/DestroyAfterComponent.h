// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: DestroyAfterComponent.h
// Desrciption	: CDestroyAfterComponent declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once

#ifndef __DESTROYAFTERCOMPONENT_H__
#define __DESTROYAFTERCOMPONENT_H__

// Library Includes

// Local Includes
#include "ObjectComponent.h"

//========================================================
// CDestroyAfterComponent is a component that will destroy
// the owner object after a specified amount of time has
// surpassed.
//
// This is useful for objects with small life-spans that
// are only to display something visual to the user.
//========================================================

class CDestroyAfterComponent : public CObjectComponent {
	// Member Functions
public:
	CDestroyAfterComponent();
	~CDestroyAfterComponent();

	virtual bool VInitialize(TiXmlElement* _pXmlData);
	virtual void VPostInitialize();
	virtual void VUpdate(float _fDeltaTime);

	// Accessors
protected:
private:

	// Member Variables
public:
protected:
private:
	float m_fElapsedTime;	// The life time of this component and it's owner.
	float m_fWaitTime;		// The amonut of time to wait before destroying the object.
};

TStrongObjectComponentPtr CreateDestroyAfterComponent();

#endif