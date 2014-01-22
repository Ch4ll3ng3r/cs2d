#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include "Block.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <map>

using namespace std;

class CMap
{
    public:
        CMap (vector<sf::Sprite*> *vpSprites);
        ~CMap ();
        CBlock* GetBlock (int xPos, int yPos);
        bool Save ();
        bool Load (string strName);
        void SetName (string strName);
        void UpdateBlockTextures (map<string, sf::Texture> *rTextures);
        bool IsValidated ();
        sf::Vector2f GetTSpawnPos ();
        sf::Vector2f GetCTSpawnPos ();

    private:
        unsigned int m_Height;
        unsigned int m_Width;
        CBlock m_Blocks[100][100];
        CBlock *m_pTSpawn;
        CBlock *m_pCTSpawn;
        CBlock *m_pBombspotA;
        CBlock *m_pBombspotB;
        string m_strName;
        bool m_bValidated;
        sf::Vector2f m_fSpawnPos;
};

#endif // MAP_HPP_INCLUDED
