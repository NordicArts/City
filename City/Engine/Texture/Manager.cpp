#include <SFML/Graphics.hpp>

#include <map>
#include <string>

#include <Texture/Manager.hpp>

namespace NordicArts {
    TextureManager::TextureManager() {}

    void TextureManager::loadTexture(const std::string &cName, const std::string &cFile) {
        sf::Texture oTexture;

        oTexture.loadFromFile(cFile);

        this->m_mTextures[cName] = oTexture;

        return;
    }

    sf::Texture &TextureManager::getRef(const std::string &oTexture) {
        return this->m_mTextures.at(oTexture);
    }
};
