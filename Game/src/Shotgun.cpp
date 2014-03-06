#include "../include/Shotgun.hpp"

CShotgun::CShotgun ()
{
    m_strBulletTextureName = "BulletShotgun";
}

void CShotgun::Init (sf::Texture *pTexture)
{
    m_pTexture = pTexture;
    m_ShotDelay = 2000;
    m_NbBulletsPerShot = 5;
    m_Damage = 20;
    m_BulletSpread = 10;
    m_fPos.x = 0;
    m_fPos.y = 0;
    m_fVelocity = 1.0f;
    m_LastShotTime = 0;
    m_fBulletHeight = 20.f;
    m_fBulletWidth = 20.f;
}
