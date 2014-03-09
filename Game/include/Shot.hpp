#ifndef SHOT_HPP_INCLUDED
#define SHOT_HPP_INCLUDED

#include "Event.hpp"


class CShot : public CEvent
{
    public:
        CShot (CPlayer *p_pPlayer, unsigned int p_uiNow, vector<sf::Sprite*> *p_vpSprites, vector<CBullet*> *p_vpBullets);
        ~CShot ();
        void Handle ();
        void Ignore ();

    private:
        CPlayer *m_pPlayer;
        unsigned int m_uiNow;
        vector<sf::Sprite*> *m_vpSprites;
        vector<CBullet*> *m_vpBullets;
};

#endif // SHOT_HPP_INCLUDED
