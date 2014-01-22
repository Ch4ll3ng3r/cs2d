#ifndef BLOCK_HPP_INCLUDED
#define BLOCK_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "BlockType.hpp"

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
        bool CheckCollision (sf::Vector2f fPos);
        bool IsStable ();
        sf::Vector2f GetPos ();

    private:
        sf::Sprite *m_pSprite;
        sf::Vector2f m_fPos;
        sf::Vector2i m_BlockPos;
        EBlockType m_Type;
        bool m_bIsStable;
};

#endif // BLOCK_HPP_INCLUDED
