#ifndef NordicArts_City_Engine_GUI_Entry_H
#define NordicArts_City_Engine_GUI_Entry_H

#include <string>
#include <utility>
#include <vector>

#include <SFML/Graphics.hpp>

namespace NordicArts {
    class GUIEntry {
    // Variables
    public:
        sf::RectangleShape  m_oShape;

        std::string         m_cMessage;

        sf::Text            m_oText;

    protected:
    private:

    // Methods
    public:
        GUIEntry(const std::string &cMessage, sf::RectangleShape oShape, sf::Text oText);
        GUIEntry();

    protected:
    private:

    };
};

#endif
