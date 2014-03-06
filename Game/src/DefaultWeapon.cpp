#include "../include/DefaultWeapon.hpp"

CDefaultWeapon::CDefaultWeapon (sf::Texture *pTexture)
: CWeapon (pTexture)
{
    m_strBulletTextureName = "BulletDefault";
}
