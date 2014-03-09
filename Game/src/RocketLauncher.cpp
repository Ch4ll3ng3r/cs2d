#include "../include/RocketLauncher.hpp"

CRocketLauncher::CRocketLauncher (sf::Texture *p_pTexture) :
CWeapon (p_pTexture)
{
    m_strBulletTextureName = "BulletRocketLauncher";
    m_uiShotDelay = 1000;
    m_uiNbBulletsPerShot = 1;
    m_uiDamage = 44;
    m_uiBulletSpread = 1;
    m_fSize = sf::Vector2f (60.f, 40.f);
    m_fVelocity = 7.f;
}
