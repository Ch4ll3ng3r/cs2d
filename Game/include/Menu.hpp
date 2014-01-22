#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include "GameState.hpp"
#include "Button.hpp"


class CMenu : public CGameState
{
    public:
        CMenu (map<string, sf::Texture> *pTextures, map<string, sf::Font> *pFonts,
               sf::RenderWindow *pWindow, EGameStateType *pCurGameStateType);
        ~CMenu ();
        void ProcessWindowEvents ();
        void ProcessKeyboardEvents ();
        void ProcessMouseEvents ();
        void Prepare (vector<sf::Sprite*> *vpSprites, vector<sf::Text*> *vpTexts);

    private:
        CButton *m_pButtonPlay;
        CButton *m_pButtonExit;
};

#endif // MENU_HPP_INCLUDED
