#include "../include/Block.hpp"

CBlock::CBlock ()
{
    m_pSprite = nullptr;
    m_fPos.x = 0.f;
    m_fPos.y = 0.f;
    m_BlockPos.x = 0;
    m_BlockPos.y = 0;
    m_iSize.x = 60;
    m_iSize.y = 60;
    m_Type = GROUND;
    m_bIsStable = false;
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
    if (m_Type == OBSTACLE)
        m_bIsStable = true;
    else
        m_bIsStable = false;
}

EBlockType CBlock::GetType ()
{
    return m_Type;
}

void CBlock::SetTexture (sf::Texture &rTexture)
{
    m_pSprite->setTexture (rTexture);
}

bool CBlock::CheckCollision (sf::Sprite *p_pSprite, sf::Vector2f p_fPos)
{
    bool bCollided = false;
    int iNbSteps = 0;
    float fDirection = p_pSprite->getRotation ();
    if (p_pSprite->getOrigin () != sf::Vector2f (0.f, 0.f))
    {
        fDirection -= 90.f;
        p_fPos.x += p_pSprite->getOrigin ().x * cos (DEG_TO_RAD(fDirection));
        p_fPos.y += p_pSprite->getOrigin ().y * sin (DEG_TO_RAD(fDirection));
        fDirection += 90.f;
        p_fPos.x +=  p_pSprite->getOrigin ().x * cos (DEG_TO_RAD(fDirection));
        p_fPos.y += p_pSprite->getOrigin ().y * sin (DEG_TO_RAD(fDirection));
    }

    for (int i = 0; i < 4; i++)
    {
        fDirection += 90.f;
        if (i % 2 == 1)
            iNbSteps = p_pSprite->getTextureRect ().height;
        else
            iNbSteps = p_pSprite->getTextureRect ().width;
        for (int j = 0; j < iNbSteps; j++)
        {
            p_fPos.x += 1.f * cos (DEG_TO_RAD(fDirection));
            p_fPos.y += 1.f * sin (DEG_TO_RAD(fDirection));
            if ((p_fPos.x >= m_fPos.x - static_cast<float> (m_iSize.x) / 2) && (p_fPos.x <= m_fPos.x + static_cast<float> (m_iSize.x) / 2) &&
                (p_fPos.y >= m_fPos.y - static_cast<float> (m_iSize.y) / 2) && (p_fPos.y <= m_fPos.y + static_cast<float> (m_iSize.y) / 2))
                bCollided = true;
        }
    }
    return bCollided;
}

bool CBlock::IsStable ()
{
    return m_bIsStable;
}

sf::Vector2f CBlock::GetPos ()
{
    return m_fPos;
}
