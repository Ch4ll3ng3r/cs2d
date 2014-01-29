#ifndef MOVEMENT_HPP_INCLUDED
#define MOVEMENT_HPP_INCLUDED

#include "Event.hpp"


class CMovement : public CEvent
{
    public:
        CMovement (CPlayer *pPlayer, unsigned int uiElapsed);
        ~CMovement ();
        void Handle ();
        void Ignore ();

    private:
        CPlayer *m_pPlayer;
        unsigned int m_uiElapsed;
};

#endif // MOVEMENT_HPP_INCLUDED
