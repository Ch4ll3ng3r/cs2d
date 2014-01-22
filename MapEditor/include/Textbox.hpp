#ifndef TEXTBOX_HPP_INCLUDED
#define TEXTBOX_HPP_INCLUDED

#include "Map.hpp"

class CTextbox
{
    public:
        CTextbox (sf::Vector2i Pos, sf::Vector2u Size);
        ~CTextbox();
        string GetUserInput ();

    private:
        void ProcessWindowEvents ();
        sf::Vector2i m_Pos;
        sf::Vector2u m_Size;
        sf::RenderWindow m_Window;
        sf::Font m_Font;
        sf::Text m_Text;
        bool m_bInputCancelled;
};

#endif // TEXTBOX_HPP_INCLUDED
