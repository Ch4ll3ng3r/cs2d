#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "Bullet.hpp"
#include <stdlib.h>

class CWeapon
{
    public:
        CWeapon (sf::Texture *pTexture);
        virtual ~CWeapon ();
        void Shoot (std::vector<CBullet*> *vpBullets, std::vector<sf::Sprite*> *vpSprites, float fDirection, std::string strShootersName);
        void SetPos (sf::Vector2f fPos);
        string GetBulletTextureName ();
        bool IsShotAvailable (unsigned int uiNow);

    protected:
        unsigned int m_uiShotDelay;
        unsigned int m_uiNbBulletsPerShot;
        unsigned int m_uiDamage;
        unsigned int m_uiBulletSpread;
        sf::Texture *m_pTexture;
        sf::Vector2f m_fPos;
        float m_fVelocity;
        string m_strBulletTextureName;
        unsigned int m_uiLastShotTime;
        float m_fBulletWidth;
        float m_fBulletHeight;
};

#endif
