#ifndef COLLISIONBULLETVSBLOCK_HPP_INCLUDED
#define COLLISIONBULLETVSBLOCK_HPP_INCLUDED

#include "Event.hpp"
#include <vector>
#include "Bullet.hpp"
#include "SafeDelete.hpp"

class CCollisionBulletVsBlock : public CEvent
{
    public:
        CCollisionBulletVsBlock (vector<sf::Sprite*> *p_vpSprites, vector<CBullet*> *p_vpBullets,
                                 sf::Sprite *p_pSprite, CBullet *p_pBullet);
        ~CCollisionBulletVsBlock ();
        void Handle ();
        void Ignore ();

    private:
        vector<sf::Sprite*> *m_vpSprites;
        vector<CBullet*> *m_vpBullets;
        sf::Sprite *m_pSprite;
        CBullet *m_pBullet;
};

#endif // COLLISIONBULLETVSBLOCK_HPP_INCLUDED
