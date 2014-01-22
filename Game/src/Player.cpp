#include "../include/Player.hpp"

CPlayer::CPlayer (sf::Sprite *pSprite, sf::Vector2f fPos, sf::Vector2f fViewSize)
{
    m_fPos.x = fPos.x;
    m_fPos.y = fPos.y;
    m_fOldPos.x = 0.f;
    m_fOldPos.y = 0.f;
    m_fViewDirection = 0.f;
    m_fOldViewDirection = 0.f;
    m_fMovementDirection = 0.f;
    m_fMaxVelocity = 0.8f;
    m_fCurVelocity = 0.f;
    m_fVelocityIncrease = 0.10f;
    m_fVelocityDecrease = 0.01f;
    m_fRotationVelocity = 0.05f;
    m_pSprite = nullptr;
    m_pSprite = pSprite;
    m_View.setCenter (m_fPos);
    m_View.setSize (fViewSize);
    m_pSprite->setOrigin (30.f, 30.f);
    m_pSprite->setPosition (m_View.getCenter ());
    m_pSprite->setRotation (m_fViewDirection);
}

CPlayer::~CPlayer()
{
    m_pSprite = nullptr;
}


sf::View& CPlayer::GetView ()
{
    return m_View;
}

void CPlayer::Rotate (float fCoefficient)
{
    m_fOldViewDirection = m_fViewDirection;
    m_fViewDirection += m_fRotationVelocity * fCoefficient;
    if (m_fViewDirection >= 360.f)
        m_fViewDirection -= 0.f;
    m_pSprite->setRotation (m_fViewDirection);
}

sf::Vector2f CPlayer::GetPos ()
{
    return m_fPos;
}

void CPlayer::SetMovementDirection (float fDeviation)
{
    m_fMovementDirection = m_fViewDirection + fDeviation;
    if (m_fMovementDirection >= 360.f)
        m_fMovementDirection -= 0.f;
}

void CPlayer::DecreaseVelocity ()
{
    if (m_fCurVelocity > 0.f)
    {
        m_fCurVelocity -= m_fVelocityDecrease;
        if (m_fCurVelocity < 0.f)
            m_fCurVelocity = 0.f;
    }

}

void CPlayer::IncreaseVelocity ()
{
    if (m_fCurVelocity < m_fMaxVelocity)
    {
        m_fCurVelocity += m_fVelocityIncrease;
        if (m_fCurVelocity > m_fMaxVelocity)
            m_fCurVelocity = m_fMaxVelocity;
    }

}

void CPlayer::Move ()
{
    m_fOldPos = m_fPos;
    m_View.move (m_fCurVelocity * cos (DEG_TO_RAD(m_fMovementDirection)), m_fCurVelocity * sin (DEG_TO_RAD(m_fMovementDirection)));
    m_fPos.x = m_View.getCenter ().x;
    m_fPos.y = m_View.getCenter ().y;
    m_pSprite->setPosition (m_fPos);
}

float CPlayer::GetCurVelocity ()
{
    return m_fCurVelocity;
}

void CPlayer::ResetMove ()
{
    m_fPos = m_fOldPos;
    m_View.setCenter (m_fPos);
    m_pSprite->setPosition (m_fPos);
}

void CPlayer::ResetRotation ()
{
    m_fViewDirection = m_fOldViewDirection;
}

bool CPlayer::CheckCollision (sf::Vector2f fSpot)
{
    // preparing collision check
    sf::Vector2f fPos = m_fPos;
    float fDirection = m_fViewDirection;
    fDirection -= 90.f;
    fPos.x += 30.f * cos (DEG_TO_RAD(fDirection));
    fPos.y += 30.f * sin (DEG_TO_RAD(fDirection));
    fDirection += 90.f;
    fPos.x += 30.f * cos (DEG_TO_RAD(fDirection));
    fPos.y += 30.f * sin (DEG_TO_RAD(fDirection));

    // check collision
    for (int i = 0; i < 4; i++)
    {
        fDirection += 90.f;
        for (int j = 0; j < 60; j++)
        {
            fPos.x += 1.f * cos (DEG_TO_RAD(fDirection));
            fPos.y += 1.f * sin (DEG_TO_RAD(fDirection));
            if (fPos == fSpot)
                return true;
        }
    }
    return false;
}
