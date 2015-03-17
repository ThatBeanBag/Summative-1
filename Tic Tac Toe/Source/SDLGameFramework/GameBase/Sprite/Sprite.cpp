// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: Sprite.cpp
// Desrciption	: CSprite implementation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// PCH
#include "GameStd.h"

// Library Includes

// This Include
#include "Sprite.h"

// Local Includes

CSprite::CSprite()
	:m_pSpriteSheet(NULL),
	m_bIsVisible(false)
{

}

CSprite::CSprite(SDL_Surface* _pLoadedSprite, const std::string& _krstrResource, bool _bIsVisible)
	:m_strResource(_krstrResource),
	m_bIsVisible(_bIsVisible)
{
	if(_pLoadedSprite) {
		m_pSpriteSheet = SDL_CreateTextureFromSurface(g_pApp->GetRenderer(), _pLoadedSprite);

		AddMask(CRect(0,0, _pLoadedSprite->w, _pLoadedSprite->h));
	}
	else {
		AddMask(CRect(0,0,0,0));
	}
}

CSprite::CSprite(CSprite& _rSprite)
{
	m_pSpriteSheet = _rSprite.Release();
	m_masks = _rSprite.GetAllMasks();
	m_strResource = _rSprite.GetResource();
	m_bIsVisible = _rSprite.IsVisible();
}

CSprite::~CSprite()
{
	if(m_pSpriteSheet) {
		// Delete the bitmap.
		SDL_DestroyTexture(m_pSpriteSheet);
		m_pSpriteSheet = NULL;
	}
}

CSprite& CSprite::operator=(CSprite& _rSprite)
{
	m_pSpriteSheet = _rSprite.Release();
	m_masks = _rSprite.GetAllMasks();
	m_strResource = _rSprite.GetResource();
	m_bIsVisible = _rSprite.IsVisible();

	return *this;
}

SDL_Texture* CSprite::GetSprite() const
{
	return m_pSpriteSheet;
}

SDL_Texture* CSprite::Release()
{
	SDL_Texture* pTexture = m_pSpriteSheet;
	m_pSpriteSheet = NULL;

	return pTexture;
}

void CSprite::AddMask(const CRect& _krMask)
{
	m_masks.push_back(_krMask);
}

CRect CSprite::GetMask(int _iFrame) const
{
	if(_iFrame >= 0 && static_cast<unsigned int>(_iFrame) < m_masks.size()) {
		// Retrieve the mask at _iFrame.
		return m_masks[_iFrame];
	}
	else {
	// Out of bounds.
		// Return a blank CRect.
		return CRect();
	}
}

const std::vector<CRect>& CSprite::GetAllMasks() const
{
	return m_masks;
}

const std::string& CSprite::GetResource() const
{
	return m_strResource;
}

void CSprite::SetVisible(bool _bIsVisible)
{
	m_bIsVisible = _bIsVisible;
}

bool CSprite::IsVisible() const
{
	return m_bIsVisible;
}


