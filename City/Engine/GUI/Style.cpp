#include <string>
#include <utility>
#include <vector>

#include <GUI/Style.hpp>

namespace NordicArts {
    GUIStyle::GUIStyle(sf::Font *pFont, float fBorderSize, sf::Color oBodyColor, sf::Color oBorderColor, sf::Color oTextColor, sf::Color oBodyHighlightColor, sf::Color oBorderHighlightColor, sf::Color oTextHighlightColor) : m_oBodyColor(oBodyColor), m_oBorderColor(oBorderColor), m_oTextColor(oTextColor), m_oBodyHighlightColor(oBodyHighlightColor), m_oBorderHighlightColor(oBorderHighlightColor), m_oTextHighlightColor(oTextHighlightColor), m_pFont(pFont), m_fBorderSize(fBorderSize) {
    }

    GUIStyle::GUIStyle() {
    }

    sf::Font *GUIStyle::getFont() const {
        return m_pFont;
    }

    sf::Color GUIStyle::getBodyColor() const {
        return m_oBodyColor;
    }
    void GUIStyle::setBodyColor(sf::Color oColor) {
        m_oBodyColor = oColor;
    }

    sf::Color GUIStyle::getBodyHighlightColor() const {
        return m_oBodyHighlightColor;
    }
    void GUIStyle::setBodyHighlightColor(sf::Color oColor) {
        m_oBodyHighlightColor = oColor;
    }
    
    sf::Color GUIStyle::getBorderColor() const {
        return m_oBorderColor;
    }
    void GUIStyle::setBorderColor(sf::Color oColor) {
        m_oBorderColor = oColor;
    }

    sf::Color GUIStyle::getBorderHighlightColor() const {
        return m_oBorderHighlightColor;
    }
    void GUIStyle::setBorderHighlightColor(sf::Color oColor) {
        m_oBorderHighlightColor = oColor;
    }

    sf::Color GUIStyle::getTextColor() const {
        return m_oTextColor;
    }
    void GUIStyle::setTextColor(sf::Color oColor) {
        m_oTextColor = oColor;
    }

    sf::Color GUIStyle::getTextHighlightColor() const {
        return m_oTextHighlightColor;
    }
    void GUIStyle::setTextHighlightColor(sf::Color oColor) {
        m_oTextHighlightColor = oColor;
    }

    float GUIStyle::getBorderSize() const {
        return m_fBorderSize;
    }
    void GUIStyle::setBorderSize(float fSize) {
        m_fBorderSize = fSize;
    }
};
