#ifndef PLATFORMEVENTMANAGER_H
#define PLATFORMEVENTMANAGER_H


#include <queue> // ToDo: Build own queue system and do not use STD::Queue
#include <unordered_map> // ToDo: May be worth building our own map for performance reasons
#include <vector>

enum EventType {
    WINDOW_RESIZE,
    MOUSE_RIGHT_CLICK,
    MOUSE_LEFT_CLICK
};

struct PlatformEventArgs {
    EventType id;
    void* args;
};

class PlatformEventManager {
private:
    /**
     * Holds events waiting to be handled
     */
    std::queue<PlatformEventArgs> event_queue;
    /**
     * Maintains list of subscribers to events
     */
    std::unordered_map<EventType, std::vector<void (*)(PlatformEventArgs*)>> subscribers;
    
public:
    /**
     * Subscribe to a particular event
     * @param id The event type to subscribe too
     * @param callback The function to call when event is triggered
     */
    void Subscribe(EventType id, void (*callback)(PlatformEventArgs*));

    /**
     * Process all events in the event queue
     */
    void ProcessEventQueue();

    /**
     * Notify all subscribers a particular event has occurred
     * @param id The ID of the event of which to notify subscribers
     */
    void TriggerEvent(EventType id);

    /**
     * Add an event to the event queue
     * @param id The event type to add to queue
     * @param args Additional data that is required to handle the event properly
     */
    void QueueEvent(EventType id, PlatformEventArgs* args);


};

#endif
