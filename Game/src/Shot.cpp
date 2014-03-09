#include "../include/Shot.hpp"

CShot::CShot (CPlayer *p_pPlayer, unsigned int p_uiNow, vector<sf::Sprite*> *p_vpSprites, vector<CBullet*> *p_vpBullets)
: CEvent (SHOT)
{
    m_pPlayer = nullptr;
    m_vpSprites = nullptr;
    m_vpBullets = nullptr;
    m_pPlayer = p_pPlayer;
    m_vpSprites = p_vpSprites;
    m_vpBullets = p_vpBullets;
    m_uiNow = p_uiNow;
    p_pPlayer = nullptr;
    p_vpBullets = nullptr;
}

CShot::~CShot ()
{
    m_pPlayer = nullptr;
    m_vpSprites = nullptr;
}

void CShot::Handle ()
{
    m_pPlayer->Shoot (m_uiNow, m_vpSprites, m_vpBullets);
}

void CShot::Ignore ()
{

}
