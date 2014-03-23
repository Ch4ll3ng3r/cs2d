#include "../include/Hit.hpp"

CHit::CHit (vector<sf::Sprite*> *p_vpSprites, vector<CBullet*> *p_vpBullets,
            sf::Sprite *p_pSprite, CBullet *p_pBullet, CPlayer *p_pVictim)
: CCollisionBulletVsBlock (p_vpSprites, p_vpBullets, p_pSprite, p_pBullet)
{
    m_Type = HIT;
    m_pVictim = nullptr;
    m_pVictim = p_pVictim;
}

CHit::~CHit ()
{
    m_pVictim = nullptr;
}

void CHit::Handle ()
{
    m_pVictim->TakeDamage (m_pBullet->GetDamage ());
    cout << m_pVictim->GetName () << " took " << m_pBullet->GetDamage () << " Damage from " << m_pBullet->GetShootersName () << endl;
    CCollisionBulletVsBlock::Handle ();
}
