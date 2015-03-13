// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: AnimationComponent.h
// Desrciption	: CAnimationComponent declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once

#ifndef __ANIMATIONCOMPONENT_H__
#define __ANIMATIONCOMPONENT_H__

// Library Includes

// Local Includes
#include "ObjectComponent.h"

//==========================================================
// CAnimationComponent manages animations of objects.
//
// An object that has a CAnimationComponent requires the
// object to have render component for obvious reasons.
// 
// The render component must be defined before an animation
// component in an xml definition of an object.
//
// The render component still handles the actual rendering
// and drawing to screen aspect, this is purely for
// drawing different masks to the screen.
//==========================================================

// Animations are stored in a map with a string being the key and a CPoint being the value.
// The CPoint represents a starting index and a terminating index of the vector of masks,
// in the CSprite. 
typedef std::map<std::string, CPoint> TAnimationMap;

class CAnimationComponent : public CObjectComponent {
	// Member Functions
public:
	CAnimationComponent();
	~CAnimationComponent();

	virtual bool VInitialize(TiXmlElement* _pXmlData);
	virtual void VPostInitialize();
	virtual void VUpdate(float _fDeltaTime);

	// Play an animation at a speed in frames per sec and loop it forever if required.
	bool PlayAnimation(std::string _strAnimation, int _iSpeed, bool _bIsLooping);

	// Moves to the next frame, if we have gone beyond the current animation and are a looping the
	// next frame will become the first frame of that animation. However, if we are not looping
	// the next frame stays at the last and an on animation event is queued.
	void NextFrame();

	// Accessors
	const std::string& GetCurrentAnimation() const;
	int GetCurrentMaskToRender() const;
	int GetAmountOfAnimations() const;
protected:
private:
	// Create an animation with _iCellsX X _iCellsY, where all the masks on the sprite are side by side all with the 
	// same size. The masks are stored into the m_tempMasks vector, which are then emptied and put into the sprite.
	void CreateAnimationMasks(std::string _strAnimName, int _iStartX, int _iStartY, int _iCellWidth, int _iCellHeight, int _iCellsX, int _iCellsY);

	// Member Variables
public:
protected:
private:
	TAnimationMap m_animations;		// The indexes of the masks in the sprite this object uses.

	int m_iCurrentFrame;			// The current frame of the current animation to draw.
	std::string m_currentAnimation;	// The current animation.
	int m_iSpeed;					// The speed in frames per sec of the animation.
	float m_fFrameTime;				// The time since last frame.
	bool m_bIsLooping;				// True if the current animation should loop, false if it should stop on the last frame.

	// Becuase we can only access the sprite after all components are initialized, we must store
	// the defined masks first in a temporary storage to be transfered onto the CSprite in the
	// post initialization phase. This could be more effeciently acheived, but for now
	// this will suffice.
	std::vector<CRect> m_tempMasks;	
};

TStrongObjectComponentPtr CreateAnimationComponent();

#endif