#include <vector>
#include <utility>
#include <string>

#include <GUI/Style.hpp>
#include <GUI/Entry.hpp>
#include <GUI/GUI.hpp>

namespace NordicArts {
    GUI::GUI(sf::Vector2f vDimensions, int iPadding, bool bHorizontal, GUIStyle &oStyle, std::vector<std::pair<std::string, std::string>> vEntries) : m_bVisible(false), m_bHorizontal(bHorizontal), m_oStyle(oStyle), m_vDimensions(vDimensions), m_iPadding(iPadding) {
        sf::RectangleShape oShape;
        oShape.setSize(vDimensions);
        oShape.setFillColor(oStyle.getBodyColor());
        oShape.setOutlineThickness(oStyle.getBorderSize());
        oShape.setOutlineColor(oStyle.getBorderColor());

        for (auto oEntry : vEntries) {
            sf::Text oText;
            oText.setString(oEntry.first);
            oText.setFont(*oStyle.getFont());
            oText.setColor(oStyle.getTextColor());
            oText.setCharacterSize(vDimensions.y - oStyle.getBorderSize() - iPadding);

            this->m_vEntries.push_back(GUIEntry(oEntry.second, oShape, oText));
        }
    }

    sf::Vector2f GUI::getSize() {
        return (sf::Vector2f(this->m_vDimensions.x, (this->m_vDimensions.y * m_vEntries.size())));
    }

    int GUI::getEntry(const sf::Vector2f vMousePos) {
        if (m_vEntries.size() == 0) {
            return -1;
        }

        if (!this->m_bVisible) {
            return -1;
        }

        for (int i = 0; i < this->m_vEntries.size(); ++i) {
            sf::Vector2f vPoint = vMousePos;
            vPoint += this->m_vEntries[i].getShape().getOrigin();
            vPoint -= this->m_vEntries[i].getShape().getPosition();

            if ((vPoint.x < 0) || (vPoint.x > (this->m_vEntries[i].getShape().getScale().x * this->m_vDimensions.x))) {
                continue;
            }
            if ((vPoint.y < 0) || (vPoint.y > (this->m_vEntries[i].getShape().getScale().y * this->m_vDimensions.y))) {
                continue;
            }
        }


        return -1;
    }

    void GUI::setEntryText(int iEntry, std::string cText) {
        if ((iEntry >= m_vEntries.size()) || (iEntry < 0)) {
            return;
        }

        m_vEntries[iEntry].getText().setString(cText);
        
        return;
    }

    void GUI::setDimensions(sf::Vector2f vDimensions) {
        this->m_vDimensions = vDimensions;

        for (auto &oEntry : m_vEntries) {
            oEntry.getShape().setSize(vDimensions);
            oEntry.getText().setCharacterSize(m_vDimensions.y - m_oStyle.getBorderSize() - m_iPadding);
        }

        return;
    }

    void GUI::draw(sf::RenderTarget &oTarget, sf::RenderStates oStates) const {
        if (m_bVisible) {
            return;
        }

        for (auto oEntry : this->m_vEntries) {
            oTarget.draw(oEntry.getShape());
            oTarget.draw(oEntry.getText());
        }

        return;
    }

    void GUI::show() {
        sf::Vector2f vOffset(0.0f, 0.0f);

        this->m_bVisible = true;

        for (auto &oEntry : this->m_vEntries) {
            sf::Vector2f vOrigin = this->getOrigin();
            vOrigin -= vOffset;
            oEntry.getShape().setOrigin(vOrigin);
            oEntry.getText().setOrigin(vOrigin);

            oEntry.getShape().setPosition(this->getPosition());
            oEntry.getText().setPosition(this->getPosition());

            if (this->m_bHorizontal) {
                vOffset.x += this->m_vDimensions.x;
            } else {
                vOffset.y += this->m_vDimensions.y;
            }
        }

        return;
    }

    void GUI::hide() {
        this->m_bVisible = false;

        return;
    }

    void GUI::highlight(const int iEntry) {
        for (int i = 0; i < m_vEntries.size(); ++i) {
            if (i == iEntry) {
                m_vEntries[i].getShape().setFillColor(m_oStyle.getBodyHighlightColor());
                m_vEntries[i].getShape().setOutlineColor(m_oStyle.getBorderHighlightColor());
                m_vEntries[i].getText().setColor(m_oStyle.getTextHighlightColor());
            } else {
                m_vEntries[i].getShape().setFillColor(m_oStyle.getBodyColor());
                m_vEntries[i].getShape().setOutlineColor(m_oStyle.getBorderColor());
                m_vEntries[i].getText().setColor(m_oStyle.getTextColor());
            }
        }

        return;
    }

    std::string GUI::activate(const int iEntry) {
        if (iEntry == -1) {
            return "null";
        }

        return m_vEntries[iEntry].m_cMessage;
    }

    std::string GUI::activate(sf::Vector2f vMousePos) {
        int iEntry = this->getEntry(vMousePos);
        return this->activate(iEntry);
    }
};
