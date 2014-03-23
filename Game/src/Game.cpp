#include "../include/Game.hpp"

CGame::CGame ()
{
    m_pWindow = nullptr;
    m_pLogfile = nullptr;
    m_CurGameStateType = MENU;
    m_LastGameStateType = MENU;
    m_pWindow = new sf::RenderWindow (sf::VideoMode::getDesktopMode (), "M41N G4M3", sf::Style::Fullscreen);
    m_DefaultView.setCenter (m_pWindow->getView ().getCenter ());
    m_DefaultView.setSize (m_pWindow->getView ().getSize ());
    m_pLogfile = new CLogfile ("log");
    cout << "starting game ..." << endl;
    m_pLogfile->Write ("starting game ...");
    LoadTextures ();
    m_pLogfile->Write ("textures loaded");
    LoadFonts ();
    m_pLogfile->Write ("fonts loaded");
    //LoadSoundBuffers ();
    //m_pLogfile->Write ("soundbuffers loaded");
    // disabled, because it produces a SIGSEGV (known SFML bug)
    InitGameStates ();

    // Init Time
    m_uiElapsedTime = 0;
    m_uiLastUpdateTime = 0;
    m_uiMaxFramesPerSecond = 120;
    m_uiTickRate = 128;
    m_uiLastPacketSendTime = 0;
    m_uiNow = 0;
}

void CGame::Run ()
{
    while ((m_pWindow->isOpen ()) && (m_CurGameStateType != EXIT))
    {
        m_uiNow = m_Clock.getElapsedTime ().asMilliseconds ();
        ReceivePackets ();
        if (m_uiNow - m_uiLastUpdateTime > 1000 / m_uiMaxFramesPerSecond)
        {
            m_uiElapsedTime = m_uiNow - m_uiLastUpdateTime;
            Update ();
            Render ();
            m_uiLastUpdateTime = m_uiNow;
        }
        if (m_uiNow - m_uiLastPacketSendTime > 1000 / m_uiTickRate)
        {
            SendPackets();
            m_uiLastPacketSendTime = m_uiNow;
        }
        sf::sleep (sf::milliseconds (1));
    }
}

CGame::~CGame ()
{
    cout << "exiting game ..." << endl;
    m_pLogfile->Write ("exiting game ...");

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
    SAFE_DELETE (m_pLogfile);
    //int h = 0;
    //cin >> h;
}

void CGame::LoadTextures ()
{
    LoadTexture ("Graphics/block_ground_02.bmp", "block_ground");
    LoadTexture ("Graphics/block_obstacle_01.bmp", "block_obstacle");
    LoadTexture ("Graphics/block_spawn_t.bmp", "block_spawn_t");
    LoadTexture ("Graphics/block_spawn_ct.bmp", "block_spawn_ct");
    LoadTexture ("Graphics/block_bombspot_a.bmp", "block_bombspot_a");
    LoadTexture ("Graphics/block_bombspot_b.bmp", "block_bombspot_b");
    LoadTexture ("Graphics/block_error.bmp", "block_error");
    LoadTexture ("Graphics/Player.bmp", "Player");
    LoadTexture ("Graphics/MenuBackground.bmp", "MenuBackground");
    LoadTexture ("Graphics/Button.bmp", "Button");
    LoadTexture ("Graphics/BulletBigFuckingGun.bmp", "BulletBigFuckingGun");
    LoadTexture ("Graphics/BulletShotgun.bmp", "BulletShotgun");
    LoadTexture ("Graphics/BulletRocketLauncher.bmp", "BulletRocketLauncher");
}

void CGame::Update ()
{
    m_pCurGameState->ProcessWindowEvents ();
    if (m_CurGameStateType != PAUSE)
    {
        m_pCurGameState->ProcessKeyboardEvents (m_uiElapsedTime);
        m_pCurGameState->ProcessMouseEvents (m_uiElapsedTime, m_uiNow);
        if (m_CurGameStateType == MULTIPLAYER)
        {
            m_pMultiplayer->UpdateBullets (m_uiElapsedTime);
            m_pMultiplayer->CheckCollisions ();
            m_pMultiplayer->ProcessGameEvents ();
            ClearSpriteList ();
            m_pMultiplayer->FillSpriteList (&m_vpSprites);
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
    m_pMultiplayer = new CMultiplayer (&m_Textures, m_pWindow, &m_CurGameStateType, m_pLogfile);
    m_pMenu = new CMenu (&m_Textures, &m_Fonts, m_pWindow, &m_CurGameStateType, m_pLogfile);
    m_pPause = new CPause (m_pWindow, &m_CurGameStateType, m_pLogfile);
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
    LoadFont ("Fonts/arial.ttf", "arial");
    LoadFont ("Fonts/ariblk.ttf", "ariblk");
    LoadFont ("Fonts/impact.ttf", "impact");
}

void CGame::LoadSoundBuffers ()
{
    LoadSoundBuffer ("Sounds/pl_step1.wav", "step");
    LoadSoundBuffer ("Sounds/ak47-1.wav", "ak");
    LoadSoundBuffer ("Sounds/m3-1.wav", "shotgun");
}

void CGame::ReceivePackets ()
{
    if (m_pMultiplayer->ConnectionEstablished ())
        m_pMultiplayer->ReceivePackets (m_uiNow);
}

void CGame::SendPackets ()
{
    if (m_pMultiplayer->ConnectionEstablished ())
        m_pMultiplayer->SendPackets (m_uiNow);
}

void CGame::LoadTexture (string p_strPath, string p_strDescription)
{
    pair<string, sf::Texture> texture;
    sf::Texture _texture;
    if (!_texture.loadFromFile (p_strPath))
    {
        m_pLogfile->Write ("failed to load" + p_strPath);
        cout << "failed to load " << p_strPath << endl;
    }
    else
    {
        texture = make_pair (p_strDescription, _texture);
        m_Textures.insert (texture);
    }
}

void CGame::LoadSoundBuffer (string p_strPath, string p_strDescription)
{
    pair<string, sf::SoundBuffer> buffer;
    sf::SoundBuffer _buffer;
    if (!_buffer.loadFromFile (p_strPath))
    {
        m_pLogfile->Write ("failed to load" + p_strPath);
        cout << "failed to load " << p_strPath << endl;
    }
    else
    {
        buffer = make_pair (p_strDescription, _buffer);
        m_SoundBuffers.insert (buffer);
    }
}

void CGame::LoadFont (string p_strPath, string p_strDescription)
{
    pair<string, sf::Font> font;
    sf::Font _font;
    if (!_font.loadFromFile (p_strPath))
    {
        m_pLogfile->Write ("failed to load" + p_strPath);
        cout << "failed to load " << p_strPath << endl;
    }
    else
    {
        font = make_pair (p_strDescription, _font);
        m_Fonts.insert (font);
    }
}
