#include "../include/Player.hpp"

CPlayer::CPlayer ()
{
    m_fPos.x = 0.f;
    m_fPos.y = 0.f;
    m_fDirection = 0.f;
}

void CPlayer::SetPos (sf::Vector2<float> fPos)
{
    m_fPos = fPos;
}

void CPlayer::SetDirection (float fDirection)
{
    m_fDirection = fDirection;
}

sf::Vector2<float> CPlayer::GetPos ()
{
    return m_fPos;
}

float CPlayer::GetDirection ()
{
    return m_fDirection;
}
