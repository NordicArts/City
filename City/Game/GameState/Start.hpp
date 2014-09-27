#ifndef NordicArts_City_Game_GameState_Start_H
#define NordicArts_City_Game_GameState_Start_H

#include <SFML/Graphics.hpp>

#include <GameState.hpp>

namespace NordicArts {
    class GameStateStart : public GameState {
    // Variables
    public:
    protected:
    private:
        sf::View m_oView;

    // Methods
    public:
        virtual void draw(const float fDT);
        virtual void update(const float fDT);
        virtual void handleInput();

        GameStateStart(Game *pGame);

    protected:
    private:
        void loadGame();
    
    };
};

#endif
