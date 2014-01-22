#ifndef EDITOR_HPP_INCLUDED
#define EDITOR_HPP_INCLUDED

#include "Map.hpp"
#include "SafeDelete.hpp"
#include "Textbox.hpp"

class CEditor
{
    public:
        CEditor();
        ~CEditor();
        void Run ();

    private:
        void LoadTextures ();
        void LoadSprites ();
        void DestroySprites ();
        void ProcessWindowEvents ();
        void ProcessKeyboardEvents ();
        void ProcessMouseEvents ();
        void RenderSprites ();
        unsigned int m_MapHeight;
        unsigned int m_MapWidth;
        sf::Clock m_Clock;
        sf::RenderWindow *m_pWindow;
        //CTextbox *m_pTextbox;
        map<string, sf::Texture> m_Textures;
        vector<sf::Sprite*> m_vpSprites;
        CMap *m_pMap;
        EBlockType m_CurrentBlockType;
        string m_strCurrentBlockTextureName;
        sf::View m_View;
        float m_fScrollingVelocity;
        int m_LastKeyPressedTime;
        bool m_bPause;
};

#endif // EDITOR_HPP_INCLUDED
