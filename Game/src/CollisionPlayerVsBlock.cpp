#include "../include/CollisionPlayerVsBlock.hpp"

CCollisionPlayerVsBlock::CCollisionPlayerVsBlock (CPlayer *pPlayer)
: CEvent (COLLISION_PLAYER_VS_BLOCK)
{
    m_pPlayer = pPlayer;
}

CCollisionPlayerVsBlock::~CCollisionPlayerVsBlock ()
{
    m_pPlayer = nullptr;
}

void CCollisionPlayerVsBlock::Handle ()
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

void CCollisionPlayerVsBlock::Ignore ()
{

}
