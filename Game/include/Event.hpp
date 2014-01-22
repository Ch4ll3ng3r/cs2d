#ifndef EVENT_HPP_INCLUDED
#define EVENT_HPP_INCLUDED

#include "EventType.hpp"
#include "Player.hpp"

class CEvent
{
    public:
        CEvent (EEventType Type);
        virtual ~CEvent();
        EEventType GetType ();
        virtual void Handle () = 0;
        virtual void Ignore () = 0;

    protected:
        EEventType m_Type;
};

#endif // EVENT_HPP_INCLUDED
