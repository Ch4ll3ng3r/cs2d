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
    m_fPos.x = 0.f;
    m_fPos.y = 0.f;
    m_fVelocity = 1.0f;
    m_uiLastShotTime = 0;
    m_fBulletWidth = 10.f;
    m_fBulletHeight = 10.f;
}

CWeapon::~CWeapon ()
{
    m_pTexture = nullptr;
}

void CWeapon::Shoot (vector<CBullet*> *vpBullets, vector<sf::Sprite*> *vpSprites, float fDirection, string strShootersName)
{
    sf::Sprite *pSprite = nullptr;
    CBullet *pBullet = nullptr;
    float _fDirection;
    int BulletSpread = 0;
    for (unsigned int i = 0; i < m_NbBulletsPerShot; i++)
    {
        pSprite = new sf::Sprite;
        pSprite->setTexture (*m_pTexture);
        vpSprites->push_back (pSprite);
        BulletSpread = rand () % (m_uiBulletSpread * 2) - m_uiBulletSpread;;
        if (m_uiBulletSpread > 0)
            _fDirection = fDirection + static_cast<float> (BulletSpread);
        else
            _fDirection = fDirection;
        pBullet = new CBullet (pSprite, _fDirection, m_fVelocity, m_fPos, m_fBulletWidth, m_fBulletHeight, strShootersName, m_uiDamage, vpSprites->size - 1);
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
