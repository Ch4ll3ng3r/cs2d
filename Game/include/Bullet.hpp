#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class CBullet
{
    public:
        CBullet (sf::Sprite *pSprite, float fDirection, float fVelocity, sf::Vector2<float> fPos, sf::Vector2f fSize,
                 string strShootersName, unsigned int uiDamage, unsigned int uiSpriteId);
        ~CBullet ();
        void Fly (unsigned int uiElapsed);
        sf::Vector2f GetPos ();
        sf::Vector2f GetSize ();
        string GetShootersName ();
        bool CheckCollision (sf::Vector2f fSpot);
        unsigned int GetDamage ();
        unsigned int GetSpriteId ();

    private:
        float m_fVelocity;
        float m_fDirection;
        sf::Vector2f m_fPos;
        sf::Vector2f m_fSize;
        sf::Sprite *m_pSprite;
        unsigned int m_uiDamage;
        unsigned int m_uiSpriteId;
        string m_strShootersName;
};

#endif
