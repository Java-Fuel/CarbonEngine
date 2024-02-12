#ifndef PLATFORMEVENTHANDLER_H
#define PLATFORMEVENTHANDLER_H

#include "Utils/Defines.h"

/*
 * This file contains all structs, classes, and interfaces required to 
 * implement a platform event handler. 
 */

struct PlatformEventArgs
{
    u32 first;
    u32 second;
};

class IPlatformEventHandler 
{
    /* Variables */
    
    /* Methods  */
    public:
        virtual void publish(PlatformEventArgs* args) {};

        
    private:
        virtual void m_exec(PlatformEventArgs* args) {};
};

template<typename T>
class PlatformEventHandler : public IPlatformEventHandler
{
    /* Variables */
    public:
        typedef void (T::*PlatformEventCallback)(PlatformEventArgs*);

    private:
        T* instance;
        PlatformEventCallback callback;

    /* Methods */
    public:
        PlatformEventHandler() = default;
        PlatformEventHandler(T* instance, PlatformEventCallback callback);
        void publish(PlatformEventArgs* args);

    private:
        void m_exec(PlatformEventArgs* args);
};

#include "PlatformEventHandler_inl.h"

#endif
