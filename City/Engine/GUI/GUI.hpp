#ifndef NordicArts_City_Engine_GUI_GUI_H
#define NordicArts_City_Engine_GUI_GUI_H

#include <vector>
#include <string>
#include <utility>

#include <GUI/Style.hpp>
#include <GUI/Entry.hpp>

namespace NordicArts {
    class GUI : public sf::Transformable, public sf::Drawable {
    // Variables
    public:
        bool                    m_bVisible;
        
        std::vector<GUIEntry>   m_vEntries;

    protected:
    private:
        bool                    m_bHorizontal;

        GUIStyle                m_oStyle;

        int                     m_iPadding;

        sf::Vector2f            m_vDimensions;

    // Methods
    public:
        GUI(sf::Vector2f vDimensions, int iPadding, bool bHorizontal, GUIStyle &oStyle, std::vector<std::pair<std::string, std::string>> vEntries);

        sf::Vector2f getSize();

        int getEntry(const sf::Vector2f vMousePos);

        void setEntryText(int iEntry, std::string cText);
        void setDimensions(sf::Vector2f vDimensions);
        void show();
        void hide();
        void highlight(const int iEntry);

        virtual void draw(sf::RenderTarget &oTarget, sf::RenderStates oStates) const;

        std::string activate(const int iEntry);
        std::string activate(const sf::Vector2f vMousePos);

    protected:
    private:

    };
};

#endif
