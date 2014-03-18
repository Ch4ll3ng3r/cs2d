#ifndef COLLISIONPLAYERVSBLOCK_HPP_INCLUDED
#define COLLISIONPLAYERVSBLOCK_HPP_INCLUDED

#include "Event.hpp"

class CCollisionPlayerVsBlock : public CEvent
{
    public:
        CCollisionPlayerVsBlock (CPlayer *pPlayer);
        ~CCollisionPlayerVsBlock ();
        void Handle ();
        void Ignore ();

    private:
        CPlayer *m_pPlayer;
};

#endif // COLLISIONPLAYERVSBLOCK_HPP_INCLUDED
