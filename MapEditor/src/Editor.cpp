#include "../include/Editor.hpp"

CEditor::CEditor()
{
    cout << "Initializing Map Editor..." << endl;
    LoadTextures ();
    LoadSprites ();
    m_pMap = nullptr;
    m_pMap = new CMap (&m_vpSprites);
    cout << "Starting Map Editor..." << endl;
    cout << "place blocks with left mouse button" << endl;
    cout << "choose white blocks with 1" << endl;
    cout << "choose blue blocks with 2" << endl;
    cout << "choose t spawn with 3" << endl;
    cout << "choose ct spawn with 4" << endl;
    cout << "choose bombspot a with 5" << endl;
    cout << "choose bombspot b with 6" << endl;
    m_pWindow = new sf::RenderWindow (sf::VideoMode::getDesktopMode (), "4w350m3 3d1t0r", sf::Style::Fullscreen);
    m_pWindow->setFramerateLimit (60);
    m_View.setCenter (static_cast<float> (m_pWindow->getSize ().x / 2), static_cast<float> (m_pWindow->getSize ().y / 2));
    m_View.setSize (static_cast<float> (m_pWindow->getSize ().x), static_cast<float> (m_pWindow->getSize ().y));
    m_CurrentBlockType = GROUND;
    m_strCurrentBlockTextureName = "block_ground";
    m_fScrollingVelocity = 10.f;
    m_LastKeyPressedTime = 0;
    m_bPause = false;
    //m_pTextbox = nullptr;
}

CEditor::~CEditor()
{
    cout << "Exit..." << endl;
    DestroySprites ();
    SAFE_DELETE (m_pMap);
    //SAFE_DELETE (m_pTextbox);
    SAFE_DELETE (m_pWindow);
}

void CEditor::Run ()
{
    while (m_pWindow->isOpen ())
    {
        ProcessKeyboardEvents ();
        ProcessWindowEvents ();
        if (!m_bPause)
        {
            ProcessMouseEvents ();
            m_pWindow->setView (m_View);
            RenderSprites ();
        }
    }
}

void CEditor::LoadTextures ()
{
    pair<string, sf::Texture> texture;
    sf::Texture _texture;
    _texture.loadFromFile ("Graphics/block_ground.bmp");
    texture = make_pair ("block_ground", _texture);
    m_Textures.insert (texture);
    _texture.loadFromFile ("Graphics/block_obstacle.bmp");
    texture = make_pair ("block_obstacle", _texture);
    m_Textures.insert (texture);
    _texture.loadFromFile ("Graphics/block_spawn_t.bmp");
    texture = make_pair ("block_spawn_t", _texture);
    m_Textures.insert (texture);
    _texture.loadFromFile ("Graphics/block_spawn_ct.bmp");
    texture = make_pair ("block_spawn_ct", _texture);
    m_Textures.insert (texture);
    _texture.loadFromFile ("Graphics/block_bombspot_a.bmp");
    texture = make_pair ("block_bombspot_a", _texture);
    m_Textures.insert (texture);
    _texture.loadFromFile ("Graphics/block_bombspot_b.bmp");
    texture = make_pair ("block_bombspot_b", _texture);
    m_Textures.insert (texture);
    _texture.loadFromFile ("Graphics/block_error.bmp");
    texture = make_pair ("block_error", _texture);
    m_Textures.insert (texture);
}

void CEditor::LoadSprites ()
{
    for (int i = 0; i < 10000; i++)
    {
        sf::Sprite *pSprite = nullptr;
        pSprite = new sf::Sprite (m_Textures.at ("block_ground"));
        m_vpSprites.push_back (pSprite);
        pSprite = nullptr;
    }
}

void CEditor::DestroySprites ()
{
    vector<sf::Sprite*>::iterator i;
    for (i = m_vpSprites.begin (); i < m_vpSprites.end (); i++)
    {
        if ((*i) != nullptr)
        {
            delete (*i);
            (*i) = nullptr;
        }
    }
}

void CEditor::ProcessKeyboardEvents ()
{
    if (m_bPause)
    {
        // save map
        if ((sf::Keyboard::isKeyPressed (sf::Keyboard::K)) && (m_Clock.getElapsedTime ().asMilliseconds () >= m_LastKeyPressedTime + 1000) && (m_pMap->IsValidated ()))
        {
            m_LastKeyPressedTime = m_Clock.getElapsedTime ().asMilliseconds ();
            cout << "Saving Map..." << endl;
            char cName[30];
            cout << "Map Name: ";
            cin.getline (cName, 29);
            m_pMap->SetName (cName);
            if (m_pMap->Save ())
                cout << "Map successfully saved" << endl;
            else
                cout << "Saving Map failed" << endl;
        }
        // load map
        else if ((sf::Keyboard::isKeyPressed (sf::Keyboard::L)) && (m_Clock.getElapsedTime ().asMilliseconds () >= m_LastKeyPressedTime + 1000))
        {
            m_LastKeyPressedTime = m_Clock.getElapsedTime ().asMilliseconds ();
            char cName[30];
            cout << "Map Name: ";
            cin.getline (cName, 29);
            cout << "Loading Map..." << endl;
            if (m_pMap->Load (cName))
            {
                m_pMap->UpdateBlockTextures (&m_Textures);
                cout << "Map successfully loaded" << endl;
            }
            else
                cout << "Loading Map failed" << endl;
        }
    }
    else
    {
        // view movement
        if ((sf::Keyboard::isKeyPressed (sf::Keyboard::W) && (m_View.getCenter ().y > m_View.getSize ().y / 2)))
        {
            m_View.move (0.f, -m_fScrollingVelocity);
        }
        else if ((sf::Keyboard::isKeyPressed (sf::Keyboard::S) && (m_View.getCenter ().y < 6000.f - m_View.getSize ().y / 2)))
        {
            m_View.move (0.f, m_fScrollingVelocity);
        }
        else if ((sf::Keyboard::isKeyPressed (sf::Keyboard::A) && (m_View.getCenter ().x > m_View.getSize ().x / 2)))
        {
            m_View.move (-m_fScrollingVelocity, 0.f);
        }
        else if ((sf::Keyboard::isKeyPressed (sf::Keyboard::D) && (m_View.getCenter ().x < 6000.f - m_View.getSize ().x / 2)))
        {
            m_View.move (m_fScrollingVelocity, 0.f);
        }
        else if ((sf::Keyboard::isKeyPressed (sf::Keyboard::Add)) && (m_fScrollingVelocity < 100.f))
        {
            m_fScrollingVelocity += 0.5f;
        }
        else if ((sf::Keyboard::isKeyPressed (sf::Keyboard::Subtract)) && (m_fScrollingVelocity > 1.f))
        {
            m_fScrollingVelocity -= 0.5f;
        }
        /*else if ((sf::Keyboard::isKeyPressed (sf::Keyboard::T)) && (m_Clock.getElapsedTime ().asMilliseconds () >= m_LastKeyPressedTime + 1000))
        {
            m_LastKeyPressedTime = m_Clock.getElapsedTime ().asMilliseconds ();
            cout << "Creating Textbox..." << endl;
            m_pTextbox = nullptr;
            m_pTextbox = new CTextbox (sf::Vector2i (500, 500), sf::Vector2u (300, 30));
            cout << m_pTextbox->GetUserInput () << endl;
            SAFE_DELETE (m_pTextbox);
        }*/
    }
}

void CEditor::ProcessMouseEvents ()
{
    if (sf::Mouse::isButtonPressed (sf::Mouse::Left))
    {
        sf::Vector2i MousePos = sf::Mouse::getPosition ();
        MousePos.x += m_View.getCenter ().x - m_View.getSize ().x / 2;
        MousePos.y += m_View.getCenter ().y - m_View.getSize ().y / 2;
        if ((MousePos.x >= 0.f) && (MousePos.x <= 6000.f) && (MousePos.y >= 0.f) && (MousePos.y <= 6000))
        m_pMap->GetBlock (MousePos.x / 60, MousePos.y / 60)->SetType (m_CurrentBlockType);
        m_pMap->GetBlock (MousePos.x / 60, MousePos.y / 60)->SetTexture (m_Textures.at (m_strCurrentBlockTextureName));
    }
}

void CEditor::ProcessWindowEvents ()
{
    sf::Event event;
    while (m_pWindow->pollEvent(event))
    {
        switch (event.type)
        {
            // window close
            case sf::Event::Closed:
            {
                m_pWindow->close ();
            } break;

            // keyboard pressed
            case sf::Event::KeyPressed:
            {
                switch (event.key.code)
                {
                    // close window
                    case sf::Keyboard::Escape:
                    {
                        m_pWindow->close ();
                    } break;

                    // choose ground block
                    case sf::Keyboard::Num1:
                    {
                        m_CurrentBlockType = GROUND;
                        m_strCurrentBlockTextureName = "block_ground";
                    } break;

                    // choose obstacle block
                    case sf::Keyboard::Num2:
                    {
                        m_CurrentBlockType = OBSTACLE;
                        m_strCurrentBlockTextureName = "block_obstacle";
                    } break;

                    // choose t spawn block
                    case sf::Keyboard::Num3:
                    {
                        m_CurrentBlockType = SPAWN_T;
                        m_strCurrentBlockTextureName = "block_spawn_t";
                    } break;

                    // choose ct spawn block
                    case sf::Keyboard::Num4:
                    {
                        m_CurrentBlockType = SPAWN_CT;
                        m_strCurrentBlockTextureName = "block_spawn_ct";
                    } break;

                    // choose bombspot a block
                    case sf::Keyboard::Num5:
                    {
                        m_CurrentBlockType = BOMBSPOT_A;
                        m_strCurrentBlockTextureName = "block_bombspot_a";
                    } break;

                    // choose bombspot b block
                    case sf::Keyboard::Num6:
                    {
                        m_CurrentBlockType = BOMBSPOT_B;
                        m_strCurrentBlockTextureName = "block_bombspot_b";
                    } break;

                    // default
                    default:
                    {
                        // nothing
                    }
                }
            } break;

            // window lost focus
            case sf::Event::LostFocus:
            {
                m_bPause = true;
            } break;

            // window gained focus
            case sf::Event::GainedFocus:
            {
                m_bPause = false;
            } break;

            // default
            default:
            {
                // nothing
            }
        }
    }
}

void CEditor::RenderSprites ()
{
    m_pWindow->clear ();
    vector<sf::Sprite*>::iterator i;
    for (i = m_vpSprites.begin (); i < m_vpSprites.end (); i++)
    {
        m_pWindow->draw (**i);
    }
    m_pWindow->display ();
}
