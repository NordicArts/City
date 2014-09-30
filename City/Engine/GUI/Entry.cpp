#include <string>
#include <vector>
#include <utility>

#include <GUI/Entry.hpp>

namespace NordicArts {
    GUIEntry::GUIEntry(const std::string &cMessage, sf::RectangleShape oShape, sf::Text oText) : m_cMessage(cMessage), m_oShape(oShape), m_oText(oText) {
    }

    GUIEntry::GUIEntry() {
    }
};
