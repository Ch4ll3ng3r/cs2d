#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "Pause.hpp"
#include "Menu.hpp"
#include "Multiplayer.hpp"

class CGame
{
    public:
        CGame ();
        ~CGame ();
        void Run ();

    private:
        void LoadTextures ();
        void LoadFonts ();
        void LoadSoundBuffers ();
        void Render ();
        void Update ();
        void SendPackets ();
        void ReceivePackets ();
        void InitGameStates ();
        void UpdateGameState ();
        void ClearSpriteList ();
        void ClearTextList ();
        CGameState* GetGameState (EGameStateType GameStateType);
        sf::Clock m_Clock;
        sf::RenderWindow *m_pWindow;
        map<string, sf::Texture> m_Textures;
        map<string, sf::Font> m_Fonts;
        map<string, sf::SoundBuffer> m_SoundBuffers;
        vector<sf::Sprite*> m_vpSprites;
        vector<sf::Text*> m_vpTexts;
        vector<sf::Sound*> m_vpSounds;
        CGameState* m_pCurGameState;
        CPause* m_pPause;
        CMultiplayer* m_pMultiplayer;
        CMenu* m_pMenu;
        EGameStateType m_CurGameStateType;
        EGameStateType m_LastGameStateType;
        sf::View m_DefaultView;
        unsigned int m_uiNow;
        unsigned int m_uiMaxFramesPerSecond;
        unsigned int m_uiElapsedTime;
        unsigned int m_uiLastUpdateTime;
        unsigned int m_uiTickRate;
        unsigned int m_uiLastPacketSendTime;
};

#endif // GAME_HPP_INCLUDED
