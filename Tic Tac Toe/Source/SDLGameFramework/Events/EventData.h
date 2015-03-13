// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: EventData.h
// Desrciption	: CIEventData declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once

#ifndef __EVENTDATA_H__
#define __EVENTDATA_H__

// Library Includes

// Local Includes
#include "../GameObject/GameObject.h"

//=========================================================================
// CIEventData is an interface that defines nothing, but must be derived
// from in order to create event data that is passed to listeners when an 
// event fires off.
//=========================================================================

class CIEventData {
	// Member Functions
public:
	virtual std::type_index VGetTypeIndex() = 0;
protected:
private:

	// Member Variables
public:
protected:
private:
};

//=========================================================================
// CIEvtDataDestroyObject
//=========================================================================

class CEvtDataDestroyObject : public CIEventData {
	// Member Functions
public:
	CEvtDataDestroyObject();
	CEvtDataDestroyObject(TGameObjectId _objectId);

	~CEvtDataDestroyObject();

	virtual std::type_index VGetTypeIndex();
	TGameObjectId GetObjectId() const;

protected:
private:

	// Member Variables
public:
protected:
private:
	TGameObjectId m_objectId;
};

//=========================================================================
// CIEvtDataCollision
//=========================================================================

class CEvtDataCollision : public CIEventData {
	// Member Functions
public:
	CEvtDataCollision();
	CEvtDataCollision(TGameObjectId _objectIdFirst, TGameObjectId _objectIdSecond);

	~CEvtDataCollision();

	virtual std::type_index VGetTypeIndex();

	TGameObjectId GetObjectIdFirst() const;
	TGameObjectId GetObjectIdSecond() const;
protected:
private:

	// Member Variables
public:
protected:
private:
	TGameObjectId m_objectIdFirst;	// The id of the first object involved in the collision.
	TGameObjectId m_objectIdSecond;	// The id of the second object involved in the collision.
};

//=========================================================================
// CIEvtDataAnimFinish
//=========================================================================

class CEvtDataAnimFinish : public CIEventData {
	// Member Functions
public:
	CEvtDataAnimFinish();
	CEvtDataAnimFinish(TGameObjectId _objectId, const std::string _strAnimation);

	~CEvtDataAnimFinish();

	virtual std::type_index VGetTypeIndex();

	// Accessors.
	TGameObjectId GetObjectId() const;
	const std::string GetAnimationName() const;
protected:
private:

	// Member Variables
public:
protected:
private:
	TGameObjectId m_objectId;	// The id of a object that finished an animation.
	std::string m_animation;	// The name of the animation that finished.
};

//=========================================================================
// CIEvtDataMoveObject
//=========================================================================

class CEvtDataMoveObject : public CIEventData {
	// Member Functions
public:
	// The normal construction of CEvtDataMoveObject, the _bIsXAxis defines which axis the 
	// velocity/acceleration is applied to. If _fAcceleration is 0 the velocity of the object,
	// is set the _fMaxVelocity.
	CEvtDataMoveObject(TGameObjectId _id, bool _bIsXAxis, float _fAcceleration, float _fMaxVelocity = g_kfINFINITY);

	~CEvtDataMoveObject();

	virtual std::type_index VGetTypeIndex();

	// Accessors.
	TGameObjectId GetObjectId() const;
	float GetAcceleration() const;
	float GetMaxVelocity() const;
	bool GetIsXAxis() const;
protected:
private:
		// Member Variables
public:
protected:
private:
	TGameObjectId m_objectId;	// The id of a object that finished an animation.
	float m_fAcceleration;		// The acceleration to apply, if this is 0 the velocity of the object will
								// be set to the max velocity.
	float m_fMaxVelocity;
	bool m_bIsXAxis;			// If true the velocity/acceleration is applied on the X, otherwise it's
								// applied on the Y axis.
};

#endif