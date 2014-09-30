#ifndef NordicArts_City_Engine_GUI_Style_H
#define NordicArts_City_Engine_GUI_Style_H

#include <vector>
#include <string>
#include <utility>

#include <SFML/Graphics.hpp>

namespace NordicArts {
    class GUIStyle {
    // Variables
    public:
        sf::Color   m_oBodyColor;
        sf::Color   m_oBodyHighlightColor;
        sf::Color   m_oBorderColor;
        sf::Color   m_oBorderHighlightColor;
        sf::Color   m_oTextColor;
        sf::Color   m_oTextHighlightColor;  
        
        sf::Font    *m_pFont;

        float       m_fBorderSize;

    protected:
    private:

    // Methods
    public:
        GUIStyle(sf::Font *pFont, float fBorderSize, sf::Color oBodyColor, sf::Color oBorderColor, sf::Color oTextColor, sf::Color oBodyHighlightColor, sf::Color oBorderHighlightColor, sf::Color oTextHighlightColor);
        GUIStyle();

    protected:
    private:

    };
};

#endif
