#include <string>
#include <utility>
#include <vector>

#include <GUI/Style.hpp>

namespace NordicArts {
    GUIStyle::GUIStyle(sf::Font *pFont, float fBorderSize, sf::Color oBodyColor, sf::Color oBorderColor, sf::Color oTextColor, sf::Color oBodyHighlightColor, sf::Color oBorderHighlightColor, sf::Color oTextHighlightColor) : m_oBodyColor(oBodyColor), m_oBorderColor(oBorderColor), m_oTextColor(oTextColor), m_oBodyHighlightColor(oBodyHighlightColor), m_oBorderHighlightColor(oBorderHighlightColor), m_oTextHighlightColor(oTextHighlightColor), m_pFont(pFont), m_fBorderSize(fBorderSize) {
    }

    GUIStyle::GUIStyle() {
    }
};
