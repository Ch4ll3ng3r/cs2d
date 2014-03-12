#include "../include/BigFuckingGun.hpp"

CBigFuckingGun::CBigFuckingGun (sf::Texture *p_pTexture) :
CWeapon (p_pTexture)
{
    m_strBulletTextureName = "BulletBigFuckingGun";
    m_uiShotDelay = 10000;
    m_uiNbBulletsPerShot = 1;
    m_uiDamage = 100;
    m_uiBulletSpread = 10;
    m_fSize = sf::Vector2f (300.f, 300.f);
    m_fVelocity = 0.1f;
    m_uiLastShotTime = 0;
}
