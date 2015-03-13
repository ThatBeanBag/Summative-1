// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: AnimationComponent.cpp
// Desrciption	: CAnimationComponent implementation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// PCH
#include "GameStd.h"

// Library Includes

// This Include
#include "AnimationComponent.h"

// Local Includes
#include "RenderComponent.h"
#include "../Events/EventManager.h"

CAnimationComponent::CAnimationComponent()
	:m_iCurrentFrame(0),
	m_currentAnimation("Invalid"),
	m_iSpeed(0),
	m_fFrameTime(0.0f)
{

}

CAnimationComponent::~CAnimationComponent()
{
}

bool CAnimationComponent::VInitialize(TiXmlElement* _pXmlData)
{
	CRenderer* pRenderer = g_pApp->m_pGame->GetRenderer();

	if(!pRenderer) {
		std::cerr << "ERROR: Can't have a render component without a renderer" << std::endl;

		// Return failed to initialize.
		return false;
	}
	else {
		TiXmlElement* pMasks = _pXmlData->FirstChildElement("Animations");
		if(pMasks) {
			for(TiXmlElement* pNode = pMasks->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement()) {
				std::string strName;
				double dX = 0.0;
				double dY = 0.0;
				double dWidth = 0.0;
				double dHeight = 0.0;
				double dHCells = 0.0;
				double dVCells = 0.0;

				strName = pNode->Value();
				pNode->Attribute("X", &dX);
				pNode->Attribute("Y", &dY);
				pNode->Attribute("Width", &dWidth);
				pNode->Attribute("Height", &dHeight);
				pNode->Attribute("HorizontalCells", &dHCells);
				pNode->Attribute("VerticalCells", &dVCells);

				// Create the animation under temporary storage.
				CreateAnimationMasks(strName, 
									 static_cast<int>(dX), static_cast<int>(dY), 
									 static_cast<int>(dWidth), static_cast<int>(dHeight), 
									 static_cast<int>(dHCells), static_cast<int>(dVCells));
			}
		}
		else {
		// No animations found.
			std::cerr << "ERROR: 'Animations' wasn't found when initializing an animation component" << std::endl;
			return false;
		}
	}

	return true;
}

void CAnimationComponent::VPostInitialize()
{
	shared_ptr<CRenderComponent> pRenderComponent = m_pOwner->GetComponent<CRenderComponent>();

	if(!pRenderComponent) {
		std::cerr << "ERROR: Can't have a animation component with a render component" << std::endl;
		return;
	}
	else {
		// Retrieve the sprite from the render component.
		CSprite* pSprite = pRenderComponent->GetSprite();

		assert(pSprite);

		TAnimationMap::iterator iter;
		for(iter = m_animations.begin(); iter != m_animations.end(); ++iter) {
			// First check to see if these masks are already a part of the sprite.
			bool bIsAnimAlreadyThere = false;

			for(unsigned int i = 0; i < pSprite->GetAllMasks().size(); ++i) {
				if(pSprite->GetAllMasks()[i] == m_tempMasks[iter->second.m_iX]) {
				// We found a mask that's the same as the first mask.
					bIsAnimAlreadyThere = true;

					CPoint& startEndPoints = iter->second;

					// Check all subsequent masks.
					for(int j = startEndPoints.m_iX + 1; j <= startEndPoints.m_iY; ++j) {
						if(pSprite->GetAllMasks()[i + j - startEndPoints.m_iX] != m_tempMasks[j]) {
							// Theres a dis-alignment, we'll have to create the new animation at the back.
							bIsAnimAlreadyThere = false;
							break;
						}
					}

					if(bIsAnimAlreadyThere) {
					// Animations already in the sprite, just need to set the start and end points.
						startEndPoints.m_iY = startEndPoints.m_iY - startEndPoints.m_iX + i;
						startEndPoints.m_iX = i;
					}

					break;
				}
				else {
					// Continue searching.
				}
			}

			if(!bIsAnimAlreadyThere) {
			// Animation is not already in the sprite.
				int iStartIndex = pSprite->GetAllMasks().size();

				// Transfer masks to the sprite.
				for(int i = iter->second.m_iX; i <= iter->second.m_iY; ++i) {
					pSprite->AddMask(m_tempMasks[i]);
				}

				iter->second.m_iX = iStartIndex;
				iter->second.m_iY = pSprite->GetAllMasks().size() - 1;
			}
			else {
			// Animation already exists.

			}
		}
	}

	// All animation should now be in the sprite.
	// Clear the temporary masks, as they are no longer needed.
	m_tempMasks.clear();

	// We no longer need the memory allocated by the vector, as it was only temporary storage. 
	// De-allocate it.
	m_tempMasks.shrink_to_fit();
}

void CAnimationComponent::VUpdate(float _fDeltaTime)
{
	m_fFrameTime += _fDeltaTime;

	if(m_iSpeed <= 0) {
	// A speed of 0 or less than 0 doesn't change the frame at all.
		return;
	}

	int iFrameTimeMilliseconds = static_cast<int>(g_kiONE_SECOND * m_fFrameTime);

	if(iFrameTimeMilliseconds > g_kiONE_SECOND / m_iSpeed) {
	// The frame needs changing.
		// Reset the frame time.
		m_fFrameTime = 0.0f;

		// Move to the next frame.
		NextFrame();
	}

	return;
}

bool CAnimationComponent::PlayAnimation(std::string _strAnimation, int _iSpeed, bool _bIsLooping)
{
	m_currentAnimation = _strAnimation;
	m_iSpeed = _iSpeed;
	m_bIsLooping = _bIsLooping;

	// Set the frame back to 0, so that we can play the new animation from the start.
	m_iCurrentFrame = 0;

	return true;
}

void CAnimationComponent::NextFrame()
{
	// Increment frame.
	++m_iCurrentFrame;

	// Find the current animation.
	TAnimationMap::iterator findIter = m_animations.find(m_currentAnimation);

	if(findIter != m_animations.end()) {
	// Animation found.
		if(m_iCurrentFrame > findIter->second.m_iY - findIter->second.m_iX) {
		// Have we reached the end of the animation.
			if(m_bIsLooping) {
			// Are we looping?
				// Reset the first frame of the animation.
				m_iCurrentFrame = 0;
			}
			else {
			// We are not looping.
				// Lock the animation at the last frame.
				m_iCurrentFrame = findIter->second.m_iY - findIter->second.m_iX;

				// Set the speed to 0, so that the animation no longer plays.
				m_iSpeed = 0;

				// Trigger an animation finished event.
				// TO DO: Only make this happen once.
				shared_ptr<CEvtDataAnimFinish> pEvent(new CEvtDataAnimFinish(m_pOwner->GetId(), m_currentAnimation));
				CEventManager::GetInstance()->QueueEvent(pEvent);
			}
		}
	}
	else {
	// No animation found.
		// Set the frame back to 0.
		m_iCurrentFrame = 0;
	}
}

const std::string& CAnimationComponent::GetCurrentAnimation() const
{
	return m_currentAnimation;
}

int CAnimationComponent::GetCurrentMaskToRender() const
{
	// Find the current animation.
	TAnimationMap::const_iterator findIter = m_animations.find(m_currentAnimation);

	if(findIter != m_animations.end()) {
	// Animation found.
		return m_iCurrentFrame + findIter->second.m_iX;
	}
	else {
	// Couldn't find animation.
		std::cerr << "WARNING: Current animation not found when rendering, display first mask instead." << std::endl;
		return 0;
	}

	return 0;
}

int CAnimationComponent::GetAmountOfAnimations() const
{
	return m_animations.size();
}

void CAnimationComponent::CreateAnimationMasks(std::string _strAnimName, 
											   int _iStartX, int _iStartY, 
											   int _iCellWidth, int _iCellHeight, 
											   int _iCellsX, int _iCellsY)
{
	if(_iCellsX * _iCellsY > 0) {
	// Are there any cells/frames in this animation?
		CPoint startAndEndPoints(m_tempMasks.size(), m_tempMasks.size());

		CRect currentMask;

		for(int i = 0; i < _iCellsY; ++i) {
			for(int j = 0; j < _iCellsX; ++j) {
				currentMask = CRect(_iStartX + _iCellWidth * j, _iStartY + _iCellHeight * i, _iCellWidth, _iCellHeight);

				// Add the currentRect to the temporary masks.
				m_tempMasks.push_back(currentMask);
			}
		}

		startAndEndPoints.m_iY = m_tempMasks.size() - 1;

		// Add the indeces of the tempMasks to the animation map.
		m_animations[_strAnimName] = startAndEndPoints;

		if(m_currentAnimation == "Invalid") {
		// Is this the first animation?
			m_currentAnimation = _strAnimName; // The first animation is always the default.
		}
	} 
	else {
		std::cerr << "WARNING: Can't create an animation with no cells" << std::endl;
		return;
	}
}

TStrongObjectComponentPtr CreateAnimationComponent()
{
	return TStrongObjectComponentPtr(new CAnimationComponent);
}