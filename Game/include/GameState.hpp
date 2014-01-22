#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED

#include <SFML/Audio.hpp>
#include "Player.hpp"
#include "Map.hpp"
#include "SafeDelete.hpp"
#include "GameStateType.hpp"

class CGameState
{
    public:
        CGameState (sf::RenderWindow *pWindow, EGameStateType *pCurGameStateType);
        virtual ~CGameState();
        virtual void ProcessWindowEvents () = 0;
        virtual void ProcessKeyboardEvents () = 0;
        virtual void ProcessMouseEvents () = 0;
        virtual void Prepare (vector<sf::Sprite*> *vpSprites, vector<sf::Text*> *vpTexts) = 0;

    protected:
        void FillSpriteList (vector<sf::Sprite*> *vpSprites);
        void FillTextList (vector<sf::Text*> *vpTexts);
        vector<sf::Sprite*> m_vpSprites;
        vector<sf::Text*> m_vpTexts;
        sf::RenderWindow *m_pWindow;
        EGameStateType *m_pCurGameStateType;
};

#endif // GAMESTATE_HPP_INCLUDED