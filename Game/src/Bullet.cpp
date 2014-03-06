#include "../include/Bullet.hpp"

CBullet::CBullet (sf::Sprite *pSprite, float fDirection, float fVelocity, sf::Vector2<float> fPos, sf::Vector2f fSize,
                  string strShootersName, unsigned int uiDamage, unsigned int uiSpriteId)
{
    m_pSprite = nullptr;
    m_pSprite = pSprite;
    m_uiSpriteId = uiSpriteId;
    m_fDirection = fDirection;
    m_fVelocity = fVelocity;
    m_fPos = fPos;
    m_fSize = fSize
    m_pSprite->setOrigin (0, m_fSize.y);
    m_pSprite->setRotation (m_fDirection);
    m_pSprite->setPosition (m_fPos);
    m_uiDamage = uiDamage;
    m_strShootersName = strShootersName;
}

CBullet::~CBullet ()
{
    m_pSprite = nullptr;
}

void CBullet::Fly (unsigned int elapsed)
{
    if (m_fDirection == 0.f)
        m_fPos.x += m_fVelocity * static_cast<float> (elapsed);
    else
        m_fPos.x -= m_fVelocity * static_cast<float> (elapsed);
    m_pSprite->setPosition (m_fPos);
}

sf::Vector2f CBullet::GetPos ()
{
    return m_fPos;
}

sf::Vector2f CBullet::GetSize ()
{
    return m_fSize;
}

bool CBullet::CheckCollision (sf::Vector2<float> fSpot)
{
    return false;
}

unsigned int CBullet::GetDamage ()
{
    return m_uiDamage;
}

string CBullet::GetShootersName ()
{
    return m_strShootersName;
}

unsigned int CBullet::GetSpriteId ()
{
    return m_uiSpriteId;
}
