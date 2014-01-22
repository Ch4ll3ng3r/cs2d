#include "../include/Game.hpp"

CGame::CGame ()
{

    m_pWindow = nullptr;
    m_CurGameStateType = MENU;
    m_LastGameStateType = MENU;
    m_pWindow = new sf::RenderWindow (sf::VideoMode::getDesktopMode (), "M41N G4M3", sf::Style::Fullscreen);
    m_DefaultView.setCenter (m_pWindow->getView ().getCenter ());
    m_DefaultView.setSize (m_pWindow->getView ().getSize ());
    LoadTextures ();
    LoadFonts ();
    InitGameStates ();
}

void CGame::Run ()
{
    while ((m_pWindow->isOpen ()) && (m_CurGameStateType != EXIT))
    {
        m_Clock.restart ();
        Update ();
        Render ();
        sf::sleep (sf::milliseconds (1));
    }
}

CGame::~CGame ()
{
    // close window, if opened
    if (m_pWindow->isOpen ())
        m_pWindow->close ();

    // sprites
    vector<sf::Sprite*>::iterator i;
    for (i = m_vpSprites.begin (); i < m_vpSprites.end (); i++)
    {
        *i = nullptr;
    }

    // texts
    vector<sf::Text*>::iterator j;
    for (j = m_vpTexts.begin (); j < m_vpTexts.end (); j++)
    {
        *j = nullptr;
    }

    m_pCurGameState = nullptr;
    SAFE_DELETE (m_pMultiplayer);
    SAFE_DELETE (m_pMenu);
    SAFE_DELETE (m_pPause);
    SAFE_DELETE (m_pWindow);
    //int h = 0;
    //cin >> h;
}

void CGame::LoadTextures ()
{
    pair<string, sf::Texture> texture;
    sf::Texture _texture;
    string strPath = "Graphics/block_ground.bmp";
    if (!_texture.loadFromFile (strPath))
        cout << "failed to load " << strPath << endl;
    texture = make_pair ("block_ground", _texture);
    m_Textures.insert (texture);
    strPath = "Graphics/block_obstacle.bmp";
    if (!_texture.loadFromFile (strPath))
        cout << "failed to load " << strPath << endl;
    texture = make_pair ("block_obstacle", _texture);
    m_Textures.insert (texture);
    strPath = "Graphics/block_spawn_t.bmp";
    if (!_texture.loadFromFile (strPath))
        cout << "failed to load " << strPath << endl;
    texture = make_pair ("block_spawn_t", _texture);
    m_Textures.insert (texture);
    strPath = "Graphics/block_spawn_ct.bmp";
    if (!_texture.loadFromFile (strPath))
        cout << "failed to load " << strPath << endl;
    texture = make_pair ("block_spawn_ct", _texture);
    m_Textures.insert (texture);
    strPath = "Graphics/block_bombspot_a.bmp";
    if (!_texture.loadFromFile (strPath))
        cout << "failed to load " << strPath << endl;
    texture = make_pair ("block_bombspot_a", _texture);
    m_Textures.insert (texture);
    strPath = "Graphics/block_bombspot_b.bmp";
    if (!_texture.loadFromFile (strPath))
        cout << "failed to load " << strPath << endl;
    texture = make_pair ("block_bombspot_b", _texture);
    m_Textures.insert (texture);
    strPath = "Graphics/block_error.bmp";
    if (!_texture.loadFromFile (strPath))
        cout << "failed to load " << strPath << endl;
    texture = make_pair ("block_error", _texture);
    m_Textures.insert (texture);
    strPath = "Graphics/Player.bmp";
    if (!_texture.loadFromFile (strPath))
        cout << "failed to load " << strPath << endl;
    texture = make_pair ("Player", _texture);
    m_Textures.insert (texture);
    strPath = "Graphics/MenuBackground.bmp";
    if (!_texture.loadFromFile (strPath))
        cout << "failed to load " << strPath << endl;
    texture = make_pair ("MenuBackground", _texture);
    m_Textures.insert (texture);
    strPath = "Graphics/Button.bmp";
    if (!_texture.loadFromFile (strPath))
        cout << "failed to load " << strPath << endl;
    texture = make_pair ("Button", _texture);
    m_Textures.insert (texture);
}

void CGame::Update ()
{
    m_pCurGameState->ProcessWindowEvents ();
    if (m_CurGameStateType != PAUSE)
    {
        m_pCurGameState->ProcessKeyboardEvents ();
        m_pCurGameState->ProcessMouseEvents ();
        if (m_CurGameStateType == MULTIPLAYER)
        {
            m_pMultiplayer->CheckCollisions ();
            m_pMultiplayer->ProcessGameEvents ();
            m_pMultiplayer->UpdateView ();
        }
        else
            m_pWindow->setView (sf::View (m_DefaultView));
    }
    UpdateGameState ();
}

void CGame::Render ()
{
    m_pWindow->clear ();

    // sprites
    vector<sf::Sprite*>::iterator i;
    for (i = m_vpSprites.begin (); i < m_vpSprites.end (); i++)
    {
        m_pWindow->draw (**i);
    }

    // texts
    vector<sf::Text*>::iterator j;
    for (j = m_vpTexts.begin (); j < m_vpTexts.end (); j++)
    {
        m_pWindow->draw (**j);
    }

    m_pWindow->display ();
}

void CGame::InitGameStates ()
{
    m_pCurGameState = nullptr;
    m_pMultiplayer = nullptr;
    m_pMenu = nullptr;
    m_pPause = nullptr;
    m_pMultiplayer = new CMultiplayer (&m_Textures, m_pWindow, &m_CurGameStateType);
    m_pMenu = new CMenu (&m_Textures, &m_Fonts, m_pWindow, &m_CurGameStateType);
    m_pPause = new CPause (m_pWindow, &m_CurGameStateType);
    m_pCurGameState = GetGameState (m_CurGameStateType);
    m_pCurGameState->Prepare (&m_vpSprites, &m_vpTexts);
}

void CGame::UpdateGameState ()
{
    // game state change
    if ((m_CurGameStateType != m_LastGameStateType) && (m_CurGameStateType != EXIT))
    {
        ClearSpriteList ();
        ClearTextList ();
        m_pCurGameState = GetGameState (m_CurGameStateType);
        m_pCurGameState->Prepare (&m_vpSprites, &m_vpTexts);
        if (m_CurGameStateType == PAUSE)
            m_pPause->SetGameStateTypeBeforePause (m_LastGameStateType);
    }
    m_LastGameStateType = m_CurGameStateType;
}

CGameState* CGame::GetGameState (EGameStateType GameStateType)
{
    switch (GameStateType)
    {
        case MULTIPLAYER:
        {
            return m_pMultiplayer;
        } break;

        case MENU:
        {
            return m_pMenu;
        } break;

        case PAUSE:
        {
            return m_pPause;
        } break;

        default:
        {
            return nullptr;
        }
    }
}

void CGame::ClearSpriteList ()
{
    vector<sf::Sprite*>::iterator i;
    for (i = m_vpSprites.begin (); i < m_vpSprites.end (); i++)
    {
        *i = nullptr;
    }
    m_vpSprites.clear ();
}

void CGame::ClearTextList ()
{
    vector<sf::Text*>::iterator i;
    for (i = m_vpTexts.begin (); i < m_vpTexts.end (); i++)
    {
        *i = nullptr;
    }
    m_vpTexts.clear ();
}

void CGame::LoadFonts ()
{
    pair<string, sf::Font> font;
    sf::Font _font;
    string strPath = "Fonts/arial.ttf";
    if (!_font.loadFromFile (strPath))
        cout << "failed to load " << strPath << endl;
    font = make_pair ("arial", _font);
    m_Fonts.insert (font);
    strPath = "Fonts/ariblk.ttf";
    if (!_font.loadFromFile (strPath))
        cout << "failed to load " << strPath << endl;
    font = make_pair ("ariblk", _font);
    m_Fonts.insert (font);
    strPath = "Fonts/impact.ttf";
    if (!_font.loadFromFile (strPath))
        cout << "failed to load " << strPath << endl;
    font = make_pair ("impact", _font);
    m_Fonts.insert (font);
}

void CGame::LoadSoundBuffers ()
{
    pair <string, sf::SoundBuffer> buffer;
    sf::SoundBuffer _buffer;
    string strPath = "Sounds/pl_step1.wav";
    if (!_buffer.loadFromFile (strPath))
        cout << "failed to load" << strPath << endl;
    buffer = make_pair ("step", _buffer);
    m_SoundBuffers.insert (buffer);
    strPath = "Sounds/ak47-1.wav";
    if (!_buffer.loadFromFile (strPath))
        cout << "failed to load" << strPath << endl;
    buffer = make_pair ("ak", _buffer);
    m_SoundBuffers.insert (buffer);
}