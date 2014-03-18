#include "../include/CollisionBulletVsBlock.hpp"

CCollisionBulletVsBlock::CCollisionBulletVsBlock (vector<sf::Sprite*> *p_vpSprites, vector<CBullet*> *p_vpBullets,
                                                  sf::Sprite *p_pSprite, CBullet *p_pBullet)
: CEvent (COLLISION_BULLET_VS_BLOCK)
{
    m_vpBullets = nullptr;
    m_vpSprites = nullptr;
    m_pBullet = nullptr;
    m_pSprite = nullptr;
    m_vpBullets = p_vpBullets;
    m_vpSprites = p_vpSprites;
    m_pBullet = p_pBullet;
    m_pSprite = p_pSprite;
}

CCollisionBulletVsBlock::~CCollisionBulletVsBlock ()
{
    m_vpBullets = nullptr;
    m_vpSprites = nullptr;
    m_pBullet = nullptr;
    m_pSprite = nullptr;
}

void CCollisionBulletVsBlock::Handle ()
{
    // sprite
    vector<sf::Sprite*>::iterator i;
    for (i = m_vpSprites->begin (); i < m_vpSprites->end (); i++)
    {
        if ((*i) == m_pSprite)
        {
            SAFE_DELETE (*i);
            m_vpSprites->erase (i);
        }
    }

    // bullet
    vector<CBullet*>::iterator j;
    for (j = m_vpBullets->begin (); j < m_vpBullets->end (); j++)
    {
        if ((*j) == m_pBullet)
        {
            SAFE_DELETE (*j);
            m_vpBullets->erase (j);
        }
    }
}

void CCollisionBulletVsBlock::Ignore ()
{

}
