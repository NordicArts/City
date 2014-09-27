#ifndef NordicArts_City_Game_GameState_Editor_H
#define NordicArts_City_Game_GameState_Editor_H

#include <SFML/Graphics.hpp>

#include <GameState.hpp>
#include <Map/Map.hpp>

namespace NordicArts {
    enum class ActionState {
        NONE,
        PANNING
    };

    class GameStateEditor : public GameState {
    // Variables
    public:
    protected:
    private:
        sf::Vector2i    m_vPanningAnchor;

        sf::View        m_oGameView;
        sf::View        m_oGUIView;

        ActionState     m_eActionState;

        Map             m_oMap;

        float           m_fZoomLevel;

    // Methods
    public:
        virtual void draw(const float fDT);
        virtual void update(const float fDT);
        virtual void handleInput();

        GameStateEditor(Game *pGame);

    protected:
    private:

    };
};

#endif
