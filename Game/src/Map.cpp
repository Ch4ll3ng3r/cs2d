#include "../include/Map.hpp"

CMap::CMap (vector<sf::Sprite*> *vpSprites)
{
    m_Width = 100;
    m_Height = 100;
    m_strName = "";
    m_pTSpawn = nullptr;
    m_pCTSpawn = nullptr;

    // Init Blocks
    int counter = 0;
    for (unsigned int i = 0; i < m_Width; i++)
    {
        for (unsigned int j = 0; j < m_Height; j++)
        {
            m_Blocks[i][j].SetSprite (vpSprites->at (counter));
            m_Blocks[i][j].SetPos (sf::Vector2i (i, j));
            counter++;
        }
    }
}

CMap::~CMap()
{
    m_pBombspotA = nullptr;
    m_pBombspotB = nullptr;
    m_pCTSpawn = nullptr;
    m_pTSpawn = nullptr;
}

CBlock* CMap::GetBlock (int xPos, int yPos)
{
    return &m_Blocks[xPos][yPos];
}

bool CMap::Save ()
{
    string strPath = "Maps/" + m_strName + ".plg";
    // Preparing Map Name
    for (int i = m_strName.length (); i < 29; i++)
    {
        m_strName.append ("0");
    }

    // Preparing Block Types
    EBlockType BlockTypes[100][100];
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            BlockTypes[i][j] = m_Blocks[i][j].GetType ();
        }
    }

    // Open File
    ofstream Output (strPath, ios::binary);
    if (Output.good ())
    {
        // Saving Map Name
        for (int i = 0; i < 29; i++)
        {
            Output.write (&m_strName.at (i), sizeof (char));
        }

        // Saving Block Types
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                Output.write ((char*) &BlockTypes[i][j], sizeof (EBlockType));
            }
        }

        // Closing File
        Output.close ();

        // Clear Map Name
        int StringEnd = static_cast<int> (m_strName.find ("0", 0));
        if (StringEnd != string::npos)
        {
            for (int i = StringEnd; i < 29; i++)
            {
                m_strName.pop_back ();
            }
        }
        return true;
    }
    return false;
}

bool CMap::Load (string strName)
{
    // Preparing Map Name
    for (int i = m_strName.length (); i < 29; i++)
    {
        m_strName.append ("0");
    }

    // Open File
    ifstream Input ("Maps/" + strName + ".plg", ios::binary);
    if (Input.good ())
    {
        // Read Map Name
        for (int i = 0; i < 29; i++)
        {
            Input.read (&m_strName.at (i), sizeof (char));
        }

        // Read Block Types
        EBlockType BlockTypes[100][100];
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                Input.read ((char*) &BlockTypes[i][j], sizeof (EBlockType));
            }
        }

        // Close File
        Input.close ();

        // Clear Map Name
        int StringEnd = static_cast<int> (m_strName.find ("0", 0));
        if (StringEnd != string::npos)
        {
            for (int i = StringEnd; i < 29; i++)
            {
                m_strName.pop_back ();
            }
        }

        // Update Block's Types
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                m_Blocks[i][j].SetType (BlockTypes[i][j]);
            }
        }
        return true;
    }
    return false;
}

void CMap::SetName (string strName)
{
    m_strName = strName;
}

void CMap::UpdateBlockTextures (map<string, sf::Texture> *rTextures)
{
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            switch (m_Blocks[i][j].GetType ())
            {
                case GROUND:
                {
                    m_Blocks[i][j].SetTexture (rTextures->at ("block_ground"));
                } break;

                case OBSTACLE:
                {
                    m_Blocks[i][j].SetTexture (rTextures->at ("block_obstacle"));
                } break;

                case SPAWN_T:
                {
                    m_Blocks[i][j].SetTexture (rTextures->at ("block_spawn_t"));
                    m_pTSpawn = &m_Blocks[i][j];
                } break;

                case SPAWN_CT:
                {
                    m_Blocks[i][j].SetTexture (rTextures->at ("block_spawn_ct"));
                    m_pCTSpawn = &m_Blocks[i][j];
                } break;

                case BOMBSPOT_A:
                {
                    m_Blocks[i][j].SetTexture (rTextures->at ("block_bombspot_a"));
                    m_pBombspotA = &m_Blocks[i][j];
                } break;

                case BOMBSPOT_B:
                {
                    m_Blocks[i][j].SetTexture (rTextures->at ("block_bombspot_b"));
                    m_pBombspotB = &m_Blocks[i][j];
                } break;

                default:
                {
                    m_Blocks[i][j].SetTexture (rTextures->at ("block_error"));
                }
            }
        }
    }
}

bool CMap::IsValidated ()
{
    int NbSpawnsT = 0;
    int NbSpawnsCT = 0;
    int NbBombspotsA = 0;
    int NbBombspotsB = 0;
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            if (m_Blocks[i][j].GetType () == SPAWN_T)
                NbSpawnsT++;
            else if (m_Blocks[i][j].GetType () == SPAWN_CT)
                NbSpawnsCT++;
            else if (m_Blocks[i][j].GetType () == BOMBSPOT_A)
                NbBombspotsA++;
            else if (m_Blocks[i][j].GetType () == BOMBSPOT_B)
                NbBombspotsB++;
        }
    }
    if (NbSpawnsT != 1)
    {
        cout << "one t spawn block" << endl;
        return false;
    }
    else if (NbSpawnsCT != 1)
    {
        cout << "one ct spawn block" << endl;
        return false;
    }
    else if (NbBombspotsA != 1)
    {
        cout << "one bombspot a block" << endl;
        return false;
    }
    else if (NbBombspotsB != 1)
    {
        cout << "one bombspot b block" << endl;
        return false;
    }
    return true;
}

sf::Vector2f CMap::GetTSpawnPos ()
{
    if (m_pTSpawn != nullptr)
        return m_pTSpawn->GetPos ();
    else
        return sf::Vector2f (0.f, 0.f);
}

sf::Vector2f CMap::GetCTSpawnPos ()
{
    if (m_pCTSpawn != nullptr)
        return m_pCTSpawn->GetPos ();
    else
        return sf::Vector2f (0.f, 0.f);
}
