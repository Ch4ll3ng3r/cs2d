#ifndef HIT_HPP_INCLUDED
#define HIT_HPP_INCLUDED

#include "CollisionBulletVsBlock.hpp"
#include <iostream>

class CHit : public CCollisionBulletVsBlock
{
    public:
        CHit (vector<sf::Sprite*> *p_vpSprites, vector<CBullet*> *p_vpBullets,
              sf::Sprite *p_pSprite, CBullet *p_pBullet, CPlayer *p_pVictim);
        ~CHit ();
        void Handle ();

    private:
        CPlayer *m_pVictim;
};

#endif // HIT_HPP_INCLUDED
