

#include "PlatformEventManager.h"

/* Static Implementations */

PlatformEventManager* PlatformEventManager::m_current = nullptr;

PlatformEventManager* PlatformEventManager::current()
{
    if(m_current == nullptr)
    {
        m_current = new PlatformEventManager();
    }

    return m_current;
}

/* Method Impl */
void PlatformEventManager::subscribe(PlatformEventType eventType, IPlatformEventHandler* handler)
{
    if (subscribers.find(eventType) == subscribers.end())
    {
        // Subscriber list not exist, create one!
        subscribers.emplace(eventType, std::vector<IPlatformEventHandler*>());
    }
    
    subscribers.at(eventType).push_back(handler);
}

void PlatformEventManager::publishEvent(PlatformEventType eventType, PlatformEventArgs* args)
{
    // TODO: Handle scenario where subscriber list doesn't exist
    if (!m_getSubscribers(eventType))
    {
        // TODO: Log message 
        return;
    }

    std::vector<IPlatformEventHandler*> eventSubs = subscribers.at(eventType);
    for (int i = 0; i < eventSubs.size(); ++i)
    {
        (*(eventSubs.at(i))).publish(args);
    }
}

std::vector<IPlatformEventHandler*>* PlatformEventManager::m_getSubscribers(PlatformEventType eventType)
{
    // If no subscribers exist, just returning null
    if (subscribers.find(eventType) == subscribers.end())
    {
        return nullptr;
    }  

    return &subscribers.at(eventType);
}
