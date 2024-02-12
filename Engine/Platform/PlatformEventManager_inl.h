

PlatformEventManager* PlatformEventManager::m_current = nullptr;

PlatformEventManager& PlatformEventManager::current()
{
    if(m_current == nullptr)
    {
        m_current = new PlatformEventManager();
    }

    return *m_current;
}
