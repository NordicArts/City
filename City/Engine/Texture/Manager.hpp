#ifndef NordicArts_City_Engine_Texture_Manager_H
#define NordicArts_City_Engine_Texture_Manager_H

#include <SFML/Graphics.hpp>

#include <string>
#include <map>

namespace NordicArts {
    class TextureManager {
    // Variables
    public:
        std::map<std::string, sf::Texture> m_mTextures;

    protected:
    private:

    // Methods
    public:
        void loadTexture(const std::string &cName, const std::string &cFile);

        sf::Texture &getRef(const std::string &cTexture);

        TextureManager();

    protected:
    private:

    };
};

#endif
