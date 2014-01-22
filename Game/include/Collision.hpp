#ifndef COLLISION_HPP_INCLUDED
#define COLLISION_HPP_INCLUDED

#include "Event.hpp"


class CCollision : public CEvent
{
    public:
        CCollision ();
        ~CCollision ();
        void Handle ();
        void Ignore ();

    private:
};

#endif // COLLISION_HPP_INCLUDED
