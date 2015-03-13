// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: EventManager.cpp
// Desrciption	: CEventManager implementation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// PCH
#include "GameStd.h"

// Library Includes

// This Include
#include "EventData.h"

// Local Includes

//====================================================================
// EvtDataDestroyObject
//====================================================================

CEvtDataDestroyObject::CEvtDataDestroyObject()
	:m_objectId(g_kINVALID_OBJECT_ID)
{

}

CEvtDataDestroyObject::CEvtDataDestroyObject(TGameObjectId _objectId)
	:m_objectId(_objectId)
{
}

CEvtDataDestroyObject::~CEvtDataDestroyObject()
{

}

std::type_index CEvtDataDestroyObject::VGetTypeIndex()
{
	return typeid(*this);
}

TGameObjectId CEvtDataDestroyObject::GetObjectId() const 
{ 
	return m_objectId; 
}

//====================================================================
// EvtDataCollision
//====================================================================

CEvtDataCollision::CEvtDataCollision()
	:m_objectIdFirst(g_kINVALID_OBJECT_ID),
	m_objectIdSecond(g_kINVALID_OBJECT_ID)
{

}

CEvtDataCollision::CEvtDataCollision(TGameObjectId _objectIdFirst, TGameObjectId _objectIdSecond)
	:m_objectIdFirst(_objectIdFirst),
	m_objectIdSecond(_objectIdSecond)
{
}

CEvtDataCollision::~CEvtDataCollision()
{

}

std::type_index CEvtDataCollision::VGetTypeIndex()
{
	return typeid(*this);
}

TGameObjectId CEvtDataCollision::GetObjectIdFirst() const 
{ 
	return m_objectIdFirst; 
}

TGameObjectId CEvtDataCollision::GetObjectIdSecond() const 
{ 
	return m_objectIdSecond; 
}

//====================================================================
// EvtDataAnimFinish
//====================================================================

CEvtDataAnimFinish::CEvtDataAnimFinish()
	:m_objectId(g_kINVALID_OBJECT_ID),
	m_animation("Invalid")
{
}

CEvtDataAnimFinish::CEvtDataAnimFinish(TGameObjectId _objectId, const std::string _strAnimation)
	:m_objectId(_objectId),
	m_animation(_strAnimation)
{
}

CEvtDataAnimFinish::~CEvtDataAnimFinish()
{
}

std::type_index CEvtDataAnimFinish::VGetTypeIndex()
{
	return typeid(*this);
}

TGameObjectId CEvtDataAnimFinish::GetObjectId() const
{
	return m_objectId;
}

const std::string CEvtDataAnimFinish::GetAnimationName() const
{
	return m_animation;
}

//====================================================================
// EvtDataMoveObject
//====================================================================

CEvtDataMoveObject::CEvtDataMoveObject(TGameObjectId _id, bool _bIsXAxis, float _fAcceleration, float _fMaxVelocity)
	:m_objectId(_id),
	m_bIsXAxis(_bIsXAxis),
	m_fAcceleration(_fAcceleration),
	m_fMaxVelocity(_fMaxVelocity)
{

}

CEvtDataMoveObject::~CEvtDataMoveObject()
{

}

std::type_index CEvtDataMoveObject::VGetTypeIndex()
{
	return typeid(*this);
}

TGameObjectId CEvtDataMoveObject::GetObjectId() const
{
	return m_objectId;
}

float CEvtDataMoveObject::GetAcceleration() const
{
	return m_fAcceleration;
}

float CEvtDataMoveObject::GetMaxVelocity() const
{
	return m_fMaxVelocity;
}

bool CEvtDataMoveObject::GetIsXAxis() const
{
	return m_bIsXAxis;
}
