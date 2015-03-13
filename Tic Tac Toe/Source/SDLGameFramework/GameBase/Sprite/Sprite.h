// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: Sprite.h
// Desrciption	: CSprite declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once

#ifndef __SPRITE_H__
#define __SPRITE_H__

// Library Includes

// Local Includes
#include "../../Utilities/Rect.h"

//-----------------------------------------------------
// CSprite is a wrapper class for images
//
// The loading of images is defined in the game app
// by the LoadSprite() member function.
//-----------------------------------------------------

class CSprite {
	// Member Functions
public:
	CSprite();																// Default constructer.
	CSprite(SDL_Surface* _pLoadedSprite, bool _bIsVisible = true);	// Normal constructer.
	CSprite(CSprite& _rSprite);					// Copy constructer.

	~CSprite();			// Destroys the texture if there is one.

	CSprite& operator=(CSprite& _rSprite);

	// Accessors
	SDL_Texture* GetSprite() const;	// RETURNS the sprite.
	SDL_Texture* Release();		// RELEASES the sprite; m_hBitmap will be NULL after this call.

	void AddMask(const CRect& _krMask);

	CRect GetMask(int _iFrame = 0) const;
	const std::vector<CRect>& GetAllMasks() const;

	void SetVisible(bool _bIsVisible);
	bool IsVisible() const;

protected:
private:

	// Member Variables
public:
protected:
private:
	SDL_Texture* m_pSpriteSheet; 
	std::vector<CRect> m_masks;	// The masks of the sprite for animations.
	bool m_bIsVisible;			// True if the image should be drawn to the screen, false if not.
};



#endif