#include "../include/Movement.hpp"

CMovement::CMovement (CPlayer *pPlayer, unsigned int uiElapsed)
: CEvent (MOVEMENT)
{
    m_pPlayer = pPlayer;
    m_uiElapsed = uiElapsed;
}

CMovement::~CMovement()
{
    m_pPlayer = nullptr;
}

void CMovement::Handle ()
{
    m_pPlayer->Move (m_uiElapsed);
}

void CMovement::Ignore ()
{

}
