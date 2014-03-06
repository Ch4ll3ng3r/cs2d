#include "../include/BigFuckingGun.hpp"

CBigFuckingGun::CBigFuckingGun (sf::Texture )
{
    m_strBulletTextureName = "BulletBigFuckingGun";
    m_ShotDelay = 10000;
    m_NbBulletsPerShot = 1;
    m_Damage = 100;
    m_BulletSpread = 10;
    m_fPos.x = 0;
    m_fPos.y = 0;
    m_fVelocity = 0.1f;
    m_LastShotTime = 0;
    m_fBulletWidth = 300.f;
    m_fBulletHeight = 300.f;
}

void CBigFuckingGun::Init (sf::Texture *pTexture)
{
    m_pTexture = pTexture;

}
