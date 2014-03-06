#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#define M_PI 3.141592
#define DEG_TO_RAD(x) M_PI / 180 * x

#include <cmath>
#include "Weapon.hpp"

class CPlayer
{
    public:
        CPlayer (sf::Sprite *pSprite, sf::Vector2f fPos, sf::Vector2f fViewSize/*, CWeapon *pWeapon*/);
        ~CPlayer();
        void DecreaseVelocity (unsigned int uiElapsed);
        void IncreaseVelocity (unsigned int uiElapsed);
        void Rotate (float fCoefficient, unsigned int uiElapsed);
        void SetMovementDirection (float fDeviation);
        void SetViewDirection (float fDirection);
        void SetPos (sf::Vector2f fPos);
        sf::View& GetView ();
        sf::Vector2f GetPos ();
        void Move (unsigned int uiElapsed);
        void UpdateSpriteAndView ();
        void ResetMove ();
        void ResetRotation ();
        float GetCurVelocity ();
        float GetViewDirection ();
        bool CheckCollision (sf::Vector2f fSpot);
        bool RequestsMovement ();

    private:
        sf::Vector2f m_fPos;
        sf::Vector2f m_fOldPos;
        sf::Sprite *m_pSprite;
        sf::View m_View;
        //CWeapon *m_pWeapon;
        float m_fViewDirection;
        float m_fOldViewDirection;
        float m_fMovementDirection;
        float m_fMaxVelocity;
        float m_fCurVelocity;
        float m_fRotationVelocity;
        float m_fVelocityDecrease;
        float m_fVelocityIncrease;
        bool m_bRequestsMovement;
};

#endif // PLAYER_HPP_INCLUDED
