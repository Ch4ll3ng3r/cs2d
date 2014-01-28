#ifndef COLLISION_HPP_INCLUDED
#define COLLISION_HPP_INCLUDED

#include "Event.hpp"
#include <iostream>

using namespace std;


class CCollision : public CEvent
{
    public:
        CCollision (CPlayer *pPlayer);
        ~CCollision ();
        void Handle ();
        void Ignore ();

    private:
        CPlayer *m_pPlayer;
};

#endif // COLLISION_HPP_INCLUDED
