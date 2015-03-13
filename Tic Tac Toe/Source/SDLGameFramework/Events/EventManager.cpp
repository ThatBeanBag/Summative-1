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
#include "EventManager.h"

// Local Includes

std::unique_ptr<CEventManager> CEventManager::s_pInstance = 0;

CEventManager::~CEventManager()
{
	// No de-allocation required, unique_ptr will de-allocate itself autmatically.
}

std::unique_ptr<CEventManager>& CEventManager::GetInstance()
{
	if(!s_pInstance)  {
		// Create the instance.
		s_pInstance = std::unique_ptr<CEventManager>(new CEventManager());
	}

	return s_pInstance;
}

void CEventManager::TriggerEvent(const TEventDataPtr& _pEvent)
{
	if(!_pEvent) {
		std::cerr << "ERROR: Invalid event to trigger." << std::endl;
		return;
	}
	else {
		// Continue.
	}

	// Get the type_index of the event;
	std::type_index index(typeid(*_pEvent));

	// Find the list of listeners at the type index.
	TEventListenerMap::iterator findIter = m_eventListeners.find(index);

	if(findIter != m_eventListeners.end()) {
	// Found the listeners of the _pEvent type.
		std::list<TEventListener>::iterator iter;
		
		// Iterate through all listeners of the type of the _pEvent.
		for(iter = findIter->second.begin(); iter != findIter->second.end(); ++iter) {
			TEventListener listener = *iter;

			// Call the listener.
			listener(_pEvent);
		}
	}
}

void CEventManager::QueueEvent(const TEventDataPtr& _pEvent)
{
	if(!_pEvent) {
		std::cerr << "ERROR: Invalid event to queue." << std::endl;
		return;
	}
	else {
		// Continue.
	}

	// Get the type_index of the event;
	std::type_index index = _pEvent->VGetTypeIndex();

	// Find the list of listeners at the type index.
	TEventListenerMap::iterator findIter = m_eventListeners.find(index);

	if(findIter != m_eventListeners.end()) {
	// Are there any listeners listening to this event type?
		// Push event into queue.
		m_eventQueue.push_back(_pEvent);
	}

}

void CEventManager::VFireOffEvents()
{
	while(!m_eventQueue.empty()) {
	// Are we done firing off all events in the queue?
		TEventDataPtr pEvent = m_eventQueue.front();

		// Pop the event from the queue.
		m_eventQueue.pop_front();

			// Get the type_index of the event;
		std::type_index index(typeid(*pEvent));

		// Find the list of listeners at the type index.
		TEventListenerMap::iterator findIter = m_eventListeners.find(index);

		if(findIter != m_eventListeners.end()) {
		// Found the listeners of the _pEvent type.
			std::list<TEventListener>::iterator iter;
		
			// Iterate through all listeners of the type of the _pEvent.
			for(iter = findIter->second.begin(); iter != findIter->second.end(); ++iter) {
				TEventListener listener = *iter;

				// Call the listener.
				listener(pEvent);
			}
		}
	}
}

CEventManager::CEventManager()
{
}

CEventManager::CEventManager(const CEventManager& _krEventManager)
{
}

CEventManager& CEventManager::operator=(const CEventManager& _krEventManager)
{
	return *this;
}

