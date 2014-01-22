#include "../include/Button.hpp"

CButton::CButton (sf::Vector2f fPos, sf::Vector2i iSize, sf::Sprite *pSprite,
                  sf::Text *pText, string strCaption)
{
    m_pSprite = nullptr;
    m_pText = nullptr;
    m_fPos = fPos;
    m_iSize = iSize;
    m_pSprite = pSprite;
    m_pText = pText;
    m_strCaption = strCaption;
    m_pText->setString (m_strCaption);
    m_pText->setColor (sf::Color::Black);
    m_pText->setCharacterSize (m_iSize.y);
    m_pText->setPosition (m_fPos);
    m_pSprite->setTextureRect (sf::IntRect (sf::Vector2i (0, 0), m_iSize));
    m_pSprite->setPosition (m_fPos);
}

CButton::~CButton()
{
    m_pSprite = nullptr;
    m_pText = nullptr;
}

bool CButton::CheckCollision (sf::Vector2f fSpot)
{
    return ((fSpot.x >= m_fPos.x) &&
            (fSpot.x <= m_fPos.x + static_cast<float> (m_iSize.x)) &&
            (fSpot.y >= m_fPos.y) &&
            (fSpot.y <= m_fPos.y + static_cast<float> (m_iSize.y)));
}

void CButton::SetCaption (string strCaption)
{
    m_strCaption = strCaption;
    m_pText->setString (m_strCaption);
}
