
CarbonLogger* CarbonLogger::m_instance = 0;

CarbonLogger* CarbonLogger::current()
{
    if (m_instance == nullptr)
    {
        m_instance = new CarbonLogger();
    }

    return m_instance;
}