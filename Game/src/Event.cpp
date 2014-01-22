#include "../include/Event.hpp"

CEvent::CEvent (EEventType Type)
{
    m_Type = Type;
}

CEvent::~CEvent()
{
    // nothing
}

EEventType CEvent::GetType ()
{
    return m_Type;
}
