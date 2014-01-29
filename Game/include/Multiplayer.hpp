#ifndef MULTIPLAYER_HPP_INCLUDED
#define MULTIPLAYER_HPP_INCLUDED

#include "GameState.hpp"
#include "Collision.hpp"
#include "Movement.hpp"
#include "Shot.hpp"

class CMultiplayer : public CGameState
{
    public:
        CMultiplayer (map<string, sf::Texture> *pTextures, sf::RenderWindow *pWindow, EGameStateType *pCurGameStateType);
        ~CMultiplayer ();
        void ProcessWindowEvents ();
        void ProcessKeyboardEvents (unsigned int uiElapsed);
        void ProcessMouseEvents (unsigned int uiElapsed);
        void ProcessGameEvents ();
        void CheckCollisions (unsigned int uiElapsed);
        void UpdateView ();
        void Prepare (vector<sf::Sprite*> *vpSprites, vector<sf::Text*> *vpTexts);

    private:
        CMap* m_pMap;
        CPlayer* m_pPlayer;
        vector<CEvent*> m_vpPendingEvents;
};

#endif // MULTIPLAYER_HPP_INCLUDED
