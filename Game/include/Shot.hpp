#ifndef SHOT_HPP_INCLUDED
#define SHOT_HPP_INCLUDED

#include "Event.hpp"


class CShot : public CEvent
{
    public:
        CShot ();
        ~CShot ();
        void Handle ();
        void Ignore ();

    private:
};

#endif // SHOT_HPP_INCLUDED
