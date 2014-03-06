#include "../include/RocketLauncher.hpp"

CRocketLauncher::CRocketLauncher ()
{
    m_strBulletTextureName = "BulletRocketLauncher";
}

void CRocketLauncher::Init (sf::Texture *pTexture)
{
    m_pTexture = pTexture;
    m_ShotDelay = 1000;
    m_NbBulletsPerShot = 1;
    m_Damage = 44;
    m_BulletSpread = 1;
    m_fPos.x = 0;
    m_fPos.y = 0;
    m_fVelocity = 0.7f;
    m_LastShotTime = 0;
    m_fBulletWidth = 60.f;
    m_fBulletHeight = 40.f;
}
