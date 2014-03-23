#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "Weapon.hpp"

class CPlayer
{
    public:
        CPlayer (sf::Sprite *pSprite, sf::Vector2f fPos, sf::Vector2f fViewSize, CWeapon *p_pWeapon);
        ~CPlayer();
        void DecreaseVelocity (unsigned int uiElapsed);
        void IncreaseVelocity (unsigned int uiElapsed);
        void Rotate (float fCoefficient, unsigned int uiElapsed);
        void SetMovementDirection (float fDeviation);
        void SetViewDirection (float fDirection);
        void SetPos (sf::Vector2f fPos);;
        void Move ();
        void UpdateSpriteAndView ();
        void ResetMove ();
        void ResetRotation ();
        void Shoot (unsigned int p_uiNow, vector<sf::Sprite*> *p_vpSprites, vector<CBullet*> *p_vpBullets);
        void TakeDamage (unsigned int p_uiDamage);
        float GetCurVelocity ();
        float GetViewDirection ();
        bool CheckCollision (sf::FloatRect p_fRect);
        bool RequestsMovement ();
        bool IsAlive ();
        string GetName ();
        sf::View& GetView ();
        sf::Vector2f GetPos ();
        sf::Sprite* GetSprite ();

    private:
        sf::Vector2f m_fPos;
        sf::Vector2f m_fOldPos;
        sf::Vector2f m_fSize;
        sf::Sprite *m_pSprite;
        sf::View m_View;
        CWeapon *m_pWeapon;
        float m_fViewDirection;
        float m_fOldViewDirection;
        float m_fMovementDirection;
        float m_fMaxVelocity;
        float m_fCurVelocity;
        float m_fRotationVelocity;
        float m_fVelocityDecrease;
        float m_fVelocityIncrease;
        unsigned int m_uiArmor;
        bool m_bRequestsMovement;
        string m_strName;
};

#endif // PLAYER_HPP_INCLUDED
