#ifndef BLOCK_HPP_INCLUDED
#define BLOCK_HPP_INCLUDED

#define M_PI 3.141592
#define DEG_TO_RAD(x) M_PI / 180 * x

#include <SFML/Graphics.hpp>
#include "BlockType.hpp"
#include <cmath>

class CBlock
{
    public:
        CBlock();
        ~CBlock();
        void SetPos (sf::Vector2i Pos);
        void SetType (EBlockType Type);
        void SetSprite (sf::Sprite *pSprite);
        void SetTexture (sf::Texture &rTexture);
        EBlockType GetType ();
        bool CheckCollision (sf::Sprite *p_pSprite, sf::Vector2f p_fPos);
        bool IsStable ();
        sf::Vector2f GetPos ();

    private:
        sf::Sprite *m_pSprite;
        sf::Vector2f m_fPos;
        sf::Vector2i m_BlockPos;
        sf::Vector2i m_iSize;
        EBlockType m_Type;
        bool m_bIsStable;
};

#endif // BLOCK_HPP_INCLUDED
