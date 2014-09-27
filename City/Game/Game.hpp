#ifndef NordicArts_City_Game_Game_H
#define NordicArts_City_Game_Game_H

#include <iostream>
#include <map>
#include <string>
#include <stack>

#include <SFML/Graphics.hpp>

#include <Texture/Manager.hpp>
#include <Tile/Tile.hpp>

// Errors
#ifndef printStuff
#define printStuff
#define printIt(variable) { std::cout << #variable << " " << variable << std::endl; }
#endif


namespace NordicArts {
    class GameState;

    class Game {
    // Variables
    public:
        std::stack<GameState *>     m_sStates;

        sf::RenderWindow            m_oWindow;
        sf::Sprite                  m_oBackground;

        TextureManager              m_oTextureManager;

        std::map<std::string, Tile> m_mTiles;

        const static int            m_iTileSize = 8;

    protected:
    private:

    // Methods
    public:
        void pushState(GameState *pState);
        void popState();
        void changeState(GameState *pState);
        void gameLoop();

        GameState *peekState();

        Game();
        ~Game();

    protected:
    private:
        void loadTextures();
        void loadTiles();
    
    };
};

#endif
