// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: EventManager.h
// Desrciption	: CEventManager declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once

#ifndef __EVENTMANAGER_H__
#define __EVENTMANAGER_H__

// Library Includes
#include <typeindex>

// Local Includes
#include "EventData.h"
#include "../3rdParty/fastdelegate/FastDelegate.h"

using fastdelegate::MakeDelegate;

typedef shared_ptr<CIEventData> TEventDataPtr;
typedef fastdelegate::FastDelegate1<TEventDataPtr> TEventListener;
typedef std::map<std::type_index, std::list<TEventListener> > TEventListenerMap;

//=========================================================================
// CEventManager is a singleton class that handles the events of the game.
//
// The singleton instance is managed as a unique_ptr which is an auto 
// pointer that deallocates itself whenever it goes out of scope. This
// ensures that the event manager does not leak and the instance is always
// de-allocated upon program termination.
//
// Adding listeners allows the registered function/delegated to be called
// whenever an event of the event type is fired off.
//
// Events do not fire off immediately unless TriggerEvent() is used.
// Instead they put in a queue to be fired off on the next update tick.
//
// Immediately triggering events using TriggerEvent() is not recommended
// unless it's absolutely neccessary. 
//=========================================================================

class CEventManager {
	// Member Functions
public:
	~CEventManager();

	static std::unique_ptr<CEventManager>& GetInstance();	// A reference must be returned as you 
															// cannot copy unique_ptrs.
	template<typename EventType>
	void AddListener(const TEventListener& _krEventListener);	// Adds listener that is called whenever
																// an event of the event type is called.

	template<typename EventType>
	void RemoveListener(const TEventListener& _krEventListener);	// Removes a listener.

	void TriggerEvent(const TEventDataPtr& _pEvent);	// IMMEDIATELY fires off and event.
	void QueueEvent(const TEventDataPtr& _pEvent);		// Default firing off of an event by placing it
														// into the queue to be fired off next tick.
	
	void VFireOffEvents(); 	// Fires off all events in the current queue, this should happen every tick.
protected:
private:
	// Disable instancing.
	CEventManager();

	// Disable copying.
	CEventManager(const CEventManager& _krEventManager);
	CEventManager& operator=(const CEventManager& _krEventManager);

	// Member Variables
public:
protected:
private:
	static std::unique_ptr<CEventManager> s_pInstance;	// The singleton instance, stored as a unique ptr
														// to ensure its de-allocation.
 
	TEventListenerMap m_eventListeners;	// The registered delegates, to be called if an event of the
										// corresponding type is fired off.
	
	std::list<TEventDataPtr> m_eventQueue;	// The queue of events that are to be fired off next 
											// update tick.
};

template<typename EventType>
void CEventManager::AddListener(const TEventListener& _krEventListener)
{
	// Get the type_index of the EventType;
	std::type_index index(typeid(EventType));

	// Find the list of listeners at the type index.
	std::list<TEventListener>& listenerList = m_eventListeners[index];

	std::list<TEventListener>::iterator listIter;

	for(listIter = listenerList.begin(); listIter != listenerList.end(); ++listIter) {
		if(_krEventListener == (*listIter)) {
		// This listener is already registered.
			std::cerr << "WARNING: Attempting to register a listener twice." << std::endl;

			// Don't register the listener twice.
			return;
		}
	}

	// Register listener.
	listenerList.push_back(_krEventListener);
}

template<typename EventType>
void CEventManager::RemoveListener(const TEventListener& _krEventListener)
{
	// Get the type_index of the EventType;
	std::type_index index(typeid(EventType));

	// Find the list of listeners at the type index.
	TEventListenerMap::iterator findIter = m_eventListeners.find(index);

	if(findIter != m_eventListeners.end()) {
		std::list<TEventListener>::iterator listIter;

		for(listIter = findIter->second.begin(); listIter != findIter->second.end(); ++listIter) {
			if(_krEventListener == (*listIter)) {
			// Listener found.
				findIter->second.erase(listIter);
				return;
			}
		}
	}
}

#endif