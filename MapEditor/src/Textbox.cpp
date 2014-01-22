#include "../include/Textbox.hpp"

CTextbox::CTextbox (sf::Vector2i Pos, sf::Vector2u Size)
{
    m_Pos = Pos;
    m_Size = Size;
    m_Window.setPosition (m_Pos);
    m_Window.setSize (m_Size);
    m_Window.setTitle ("Textbox");
    m_Window.setActive (true);
    //m_Window.setVisible (true);
    m_bInputCancelled = false;

    // load font and prepare text
    if (!m_Font.loadFromFile ("Fonts/arial.ttf"))
        cout << "loading font failed" << endl;
    else
    {
        m_Text.setFont (m_Font);
        m_Text.setCharacterSize (12);
        m_Text.setColor (sf::Color::Black);
        m_Text.setString ("please insert text...");
    }
}

CTextbox::~CTextbox()
{

}

string CTextbox::GetUserInput ()
{
    while (m_Window.isOpen ())
    {
        ProcessWindowEvents ();
        m_Window.clear (sf::Color::White);
        m_Window.draw (m_Text);
        m_Window.display ();
    }
    if (m_bInputCancelled)
        return "Input cancelled";
    else
        return m_Text.getString ();
}

void CTextbox::ProcessWindowEvents ()
{
    sf::Event event;
    while (m_Window.pollEvent(event))
    {
        switch (event.type)
        {
            // window close
            case sf::Event::Closed:
            {
                m_Window.close ();
            } break;

            // keyboard pressed
            case sf::Event::KeyPressed:
            {
                switch (event.key.code)
                {
                    // input cancelled
                    case sf::Keyboard::Escape:
                    {
                        m_Window.close ();
                        m_bInputCancelled = true;
                    } break;

                    // input confirmed
                    case sf::Keyboard::Return:
                    {
                        m_Window.close ();
                        m_bInputCancelled = false;
                    } break;

                    // default
                    default:
                    {
                        // nothing
                    }
                }
            } break;

            // window lost focus
            /*case sf::Event::LostFocus:
            {
                m_bPause = true;
            } break;

            // window gained focus
            case sf::Event::GainedFocus:
            {
                m_bPause = false;
            } break;*/

            // default
            default:
            {
                // nothing
            }
        }
    }
}
