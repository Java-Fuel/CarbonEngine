
template<typename T>
PlatformEventHandler<T>::PlatformEventHandler(T* instance, PlatformEventCallback callback)
{
    this->instance = instance;
    this->callback = callback;
}

template<typename T>
void PlatformEventHandler<T>::publish(PlatformEventArgs* args)
{
    // TODO: Implement Me!
    OutputDebugStringA("Publishing Event!\n");
}

template<typename T>
void PlatformEventHandler<T>::m_exec(PlatformEventArgs* args)
{
    // TODO: Implement Me!
    OutputDebugStringA("Executing event in instance function pointer!\n");
}
