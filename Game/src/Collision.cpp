#include "../include/Collision.hpp"

CCollision::CCollision (CPlayer *pPlayer)
: CEvent (COLLISION)
{
    m_pPlayer = pPlayer;
}

CCollision::~CCollision()
{
    m_pPlayer = nullptr;
}

void CCollision::Handle ()
{
    if (m_pPlayer->GetCurVelocity () > 0.f)
    {
        m_pPlayer->ResetMove ();
        while (m_pPlayer->GetCurVelocity () > 0.f)
        {
            m_pPlayer->DecreaseVelocity (200);
        }
    }
    m_pPlayer->ResetRotation ();
}

void CCollision::Ignore ()
{

}
