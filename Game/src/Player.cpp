#include "../include/Player.hpp"

CPlayer::CPlayer (sf::Sprite *pSprite, sf::Vector2f fPos, sf::Vector2f fViewSize, CWeapon *p_pWeapon)
{
    m_fPos.x = fPos.x;
    m_fPos.y = fPos.y;
    m_fOldPos.x = 0.f;
    m_fOldPos.y = 0.f;
    m_fViewDirection = 0.f;
    m_fOldViewDirection = 0.f;
    m_fMovementDirection = 0.f;
    m_fMaxVelocity = 0.2f;
    m_fCurVelocity = 0.f;
    m_fVelocityIncrease = 0.02f;
    m_fVelocityDecrease = m_fVelocityIncrease / 2;
    m_fRotationVelocity = 0.01f;
    m_bRequestsMovement = false;
    m_pSprite = nullptr;
    m_pSprite = pSprite;
    m_pWeapon = nullptr;
    m_pWeapon = p_pWeapon;
    m_strName = "Horst";
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

void CPlayer::Rotate (float fCoefficient, unsigned int uiElapsed)
{
    m_fOldViewDirection = m_fViewDirection;
    m_bRequestsMovement = true;
    m_fViewDirection += m_fRotationVelocity * fCoefficient * static_cast<float> (uiElapsed);
    if (m_fViewDirection >= 360.f)
        m_fViewDirection -= 0.f;
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

void CPlayer::DecreaseVelocity (unsigned int uiElapsed)
{
    if (m_fCurVelocity > 0.f)
    {
        m_fCurVelocity -= m_fVelocityDecrease * static_cast<float> (uiElapsed);
        if (m_fCurVelocity < 0.f)
            m_fCurVelocity = 0.f;
        else if (m_fCurVelocity > 0.f)
            m_bRequestsMovement = true;
    }

}

void CPlayer::IncreaseVelocity (unsigned int uiElapsed)
{
    if (m_fCurVelocity < m_fMaxVelocity * static_cast<float> (uiElapsed))
    {
        m_fCurVelocity += m_fVelocityIncrease * static_cast<float> (uiElapsed);
        if (m_fCurVelocity > m_fMaxVelocity * static_cast<float> (uiElapsed))
            m_fCurVelocity = m_fMaxVelocity * static_cast<float> (uiElapsed);
    }

}

void CPlayer::Move ()
{
    m_fOldPos = m_fPos;
    m_bRequestsMovement = false;
    m_fPos.x += m_fCurVelocity * cos (DEG_TO_RAD(m_fMovementDirection));
    m_fPos.y += m_fCurVelocity * sin (DEG_TO_RAD(m_fMovementDirection));
}

void CPlayer::UpdateSpriteAndView ()
{
    m_View.setCenter (m_fPos);
    m_pSprite->setRotation (m_fViewDirection);
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
    m_pSprite->setRotation (m_fViewDirection);
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

bool CPlayer::RequestsMovement ()
{
    return m_bRequestsMovement;
}

float CPlayer::GetViewDirection ()
{
    return m_fViewDirection;
}

void CPlayer::SetPos (sf::Vector2f fPos)
{
    m_fPos = fPos;
    m_pSprite->setPosition (m_fPos);
}

void CPlayer::SetViewDirection (float fDirection)
{
    m_fViewDirection = fDirection;
    m_pSprite->setRotation (m_fViewDirection);
}

void CPlayer::Shoot (unsigned int p_uiNow, vector<sf::Sprite*> *p_vpSprites, vector<CBullet*> *p_vpBullets)
{
    if (m_pWeapon->IsShotAvailable (p_uiNow))
    {
        m_pWeapon->SetPos (m_fPos);
        m_pWeapon->Shoot (p_vpBullets, p_vpSprites, m_fViewDirection, m_strName);
    }
}
