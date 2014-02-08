#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <SFML/Network.hpp>

class CPlayer
{
    public:
        CPlayer();
        sf::Vector2<float> GetPos ();
        float GetDirection ();
        void SetPos (sf::Vector2<float> fPos);
        void SetDirection (float fDirection);

    private:
        sf::Vector2<float> m_fPos;
        float m_fDirection;
};

#endif // PLAYER_HPP_INCLUDED
