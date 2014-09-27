#ifndef NordicArts_City_Game_GameState_H
#define NordicArts_City_Game_GameState_H

#include "./Game.hpp"

namespace NordicArts {
    class GameState {
    // Variables
    public:
    protected:
    private:

    // Methods
    public:
        Game *m_pGame;

        virtual void draw(const float fDT) = 0;
        virtual void update(const float fDT) = 0;
        virtual void handleInput() = 0;
    
        virtual ~GameState() {
            m_pGame = nullptr;
        }

    protected:
    private:

    };
};

#endif
