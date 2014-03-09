#include "../include/Shotgun.hpp"

CShotgun::CShotgun (sf::Texture *p_pTexture) :
CWeapon (p_pTexture)
{
    m_strBulletTextureName = "BulletShotgun";
    m_uiShotDelay = 2000;
    m_uiNbBulletsPerShot = 5;
    m_uiDamage = 20;
    m_uiBulletSpread = 10;
    m_fSize = sf::Vector2f (20.f, 20.f);
    m_fVelocity = 10.f;
    m_uiLastShotTime = 0;
}
