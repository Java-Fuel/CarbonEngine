#ifndef PLATFORMEVENTMANAGER_H
#define PLATFORMEVENTMANAGER_H

#include <vector>
#include <unordered_map>
#include "PlatformEventHandler.h"
#include "Utils/Defines.h"


CAPI enum PlatformEventType
{
    WINDOW_RESIZE
};

CAPI class PlatformEventManager
{
    /* Variables */
    public:
    
    protected:
        static PlatformEventManager* m_current;

    private:
        std::unordered_map<PlatformEventType, std::vector<IPlatformEventHandler*>> subscribers;

    /* Methods */
    public:
        void subscribe(PlatformEventType eventType, IPlatformEventHandler* handler);
        void unsubscribe(); // TODO: Need to implement
        void publishEvent(PlatformEventType eventType, PlatformEventArgs* args);
        
        static PlatformEventManager* current();

    protected:
        PlatformEventManager() = default;
    private:
        std::vector<IPlatformEventHandler*>* m_getSubscribers(PlatformEventType eventType);
};

// #include "PlatformEventManager_inl.h"

#endif
