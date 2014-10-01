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
    protected:
    private:
        sf::Color   m_oBodyColor;
        sf::Color   m_oBodyHighlightColor;
        sf::Color   m_oBorderColor;
        sf::Color   m_oBorderHighlightColor;
        sf::Color   m_oTextColor;
        sf::Color   m_oTextHighlightColor;  
        
        sf::Font    *m_pFont;

        float       m_fBorderSize;

    // Methods
    public:
        GUIStyle(sf::Font *pFont, float fBorderSize, sf::Color oBodyColor, sf::Color oBorderColor, sf::Color oTextColor, sf::Color oBodyHighlightColor, sf::Color oBorderHighlightColor, sf::Color oTextHighlightColor);
        GUIStyle();

        sf::Font *getFont() const;
        
        sf::Color getBodyColor() const;
        void setBodyColor(sf::Color oColor);

        sf::Color getBodyHighlightColor() const;
        void setBodyHighlightColor(sf::Color oColor);

        sf::Color getBorderColor() const;
        void setBorderColor(sf::Color oColor);

        sf::Color getBorderHighlightColor() const;
        void setBorderHighlightColor(sf::Color oColor);

        sf::Color getTextColor() const;
        void setTextColor(sf::Color oColor);

        sf::Color getTextHighlightColor() const;
        void setTextHighlightColor(sf::Color oColor);

        float getBorderSize() const;
        void setBorderSize(float fSize);

    protected:
    private:

    };
};

#endif
