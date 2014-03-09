#include "../include/Weapon.hpp"

CWeapon::CWeapon (sf::Texture *pTexture)
{
    m_strBulletTextureName = "";
    m_pTexture = nullptr;
    m_pTexture = pTexture;
    m_uiShotDelay = 1000;
    m_uiNbBulletsPerShot = 1;
    m_uiDamage = 88;
    m_uiBulletSpread = 0;
    m_fPos = sf::Vector2f (0.f, 0.f);
    m_fSize = sf::Vector2f (10.f, 10.f);
    m_fVelocity = 1.0f;
    m_uiLastShotTime = 0;
}

CWeapon::~CWeapon ()
{
    m_pTexture = nullptr;
}

void CWeapon::Shoot (vector<CBullet*> *vpBullets, vector<sf::Sprite*> *vpSprites, float fDirection, string strShootersName)
{
    sf::Sprite *pSprite = nullptr;
    CBullet *pBullet = nullptr;
    float _fDirection = 0.f;
    int uiBulletSpread = 0;
    for (unsigned int i = 0; i < m_uiNbBulletsPerShot; i++)
    {
        pSprite = new sf::Sprite;
        pSprite->setTexture (*m_pTexture);
        vpSprites->push_back (pSprite);
        uiBulletSpread = rand () % (m_uiBulletSpread * 2) - m_uiBulletSpread;;
        _fDirection = fDirection + static_cast<float> (uiBulletSpread);
        pBullet = new CBullet (pSprite, _fDirection, m_fVelocity, m_fPos, m_fSize, strShootersName, m_uiDamage, vpSprites->size () - 1);
        vpBullets->push_back (pBullet);
    }
}

void CWeapon::SetPos (sf::Vector2f fPos)
{
    m_fPos = fPos;
}

string CWeapon::GetBulletTextureName ()
{
    return m_strBulletTextureName;
}

bool CWeapon::IsShotAvailable (unsigned int uiNow)
{
    if (m_uiLastShotTime + m_uiShotDelay <= uiNow)
    {
        m_uiLastShotTime = uiNow;
        return true;
    }
    return false;
}
