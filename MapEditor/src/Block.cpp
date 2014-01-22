#include "../include/Block.hpp"

CBlock::CBlock ()
{
    m_pSprite = nullptr;
    m_fPos.x = 0.f;
    m_fPos.y = 0.f;
    m_BlockPos.x = 0;
    m_BlockPos.y = 0;
    m_Type = GROUND;
}

CBlock::~CBlock ()
{
    if (m_pSprite != nullptr)
        m_pSprite = nullptr;
}

void CBlock::SetSprite (sf::Sprite *pSprite)
{
    m_pSprite = pSprite;
    m_pSprite->setPosition (m_fPos);
    m_pSprite->setOrigin (30.f, 30.f);
}

void CBlock::SetPos (sf::Vector2i Pos)
{
    m_BlockPos = Pos;
    m_fPos.x = static_cast<float> (Pos.x * 60 + 30);
    m_fPos.y = static_cast<float> (Pos.y * 60 + 30);
    m_pSprite->setPosition (m_fPos);
}

void CBlock::SetType (EBlockType Type)
{
    m_Type = Type;
}

EBlockType CBlock::GetType ()
{
    return m_Type;
}

void CBlock::SetTexture (sf::Texture &rTexture)
{
    m_pSprite->setTexture (rTexture);
}

sf::Vector2f CBlock::GetPos ()
{
    return m_fPos;
}
