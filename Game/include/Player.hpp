#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#define M_PI 3.141592
#define DEG_TO_RAD(x) M_PI / 180 * x

#include <SFML/Graphics.hpp>
#include <cmath>

class CPlayer
{
    public:
        CPlayer (sf::Sprite *pSprite, sf::Vector2f fPos, sf::Vector2f fViewSize);
        ~CPlayer();
        void DecreaseVelocity ();
        void IncreaseVelocity ();
        void Rotate (float fCoefficient);
        void SetMovementDirection (float fDeviation);
        sf::View& GetView ();
        sf::Vector2f GetPos ();
        void Move ();
        float GetCurVelocity ();
        void ResetMove ();
        void ResetRotation ();
        bool CheckCollision (sf::Vector2f fSpot);

    private:
        sf::Vector2f m_fPos;
        sf::Vector2f m_fOldPos;
        sf::Sprite *m_pSprite;
        sf::View m_View;
        float m_fViewDirection;
        float m_fOldViewDirection;
        float m_fMovementDirection;
        float m_fMaxVelocity;
        float m_fCurVelocity;
        float m_fRotationVelocity;
        float m_fVelocityDecrease;
        float m_fVelocityIncrease;
};

#endif // PLAYER_HPP_INCLUDED
