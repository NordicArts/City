#ifndef NordicArts_City_Game_GameState_Editor_H
#define NordicArts_City_Game_GameState_Editor_H

#include <SFML/Graphics.hpp>

#include <GameState.hpp>
#include <Map/Map.hpp>
#include <Tile/Tile.hpp>

namespace NordicArts {
    enum class ActionState {
        NONE,
        PANNING,
        SELECTING
    };

    class GameStateEditor : public GameState {
    // Variables
    public:
    protected:
    private:
        sf::Vector2i    m_vPanningAnchor;
        sf::Vector2i    m_vSelectionStart;
        sf::Vector2i    m_vSelectionEnd;

        sf::View        m_oGameView;
        sf::View        m_oGUIView;

        ActionState     m_eActionState;

        Map             m_oMap;

        float           m_fZoomLevel;

        Tile            *m_pCurrentTile;

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
