#include "../include/Movement.hpp"

CMovement::CMovement (CPlayer *pPlayer)
: CEvent (MOVEMENT)
{
    m_pPlayer = pPlayer;
}

CMovement::~CMovement()
{
    m_pPlayer = nullptr;
}

void CMovement::Handle ()
{
    m_pPlayer->UpdateSpriteAndView ();
}

void CMovement::Ignore ()
{

}
