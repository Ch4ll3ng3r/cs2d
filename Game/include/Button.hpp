#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class CButton
{
    public:
        CButton (sf::Vector2f fPos, sf::Vector2i iSize, sf::Sprite *pSprite,
                 sf::Text *pText, string strCaption);
        ~CButton ();
        bool CheckCollision (sf::Vector2f fSpot);
        void SetCaption (string strCaption);

    private:
        sf::Vector2f m_fPos;
        sf::Vector2i m_iSize;
        sf::Sprite *m_pSprite;
        sf::Text *m_pText;
        string m_strCaption;
};

#endif // BUTTON_HPP_INCLUDED
