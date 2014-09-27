#include <stack>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <Game.hpp>
#include <GameState.hpp>
#include <Texture/Manager.hpp>

namespace NordicArts {
    void Game::loadTiles() {
        Animation oAnim(0, 0, 1.0f);
        Animation oWater(0, 3, 0.5f);
        
        this->m_mTiles["grass"]         = Tile(this->m_iTileSize, 1, m_oTextureManager.getRef("grass"), { oAnim }, TileType::GRASS, 50, 0, 1);
        this->m_mTiles["forest"]        = Tile(this->m_iTileSize, 1, m_oTextureManager.getRef("forest"), { oAnim }, TileType::FOREST, 100, 0, 1);
        this->m_mTiles["water"]         = Tile(this->m_iTileSize, 1, m_oTextureManager.getRef("water"), { oWater, oWater, oWater, oWater }, TileType::WATER, 0, 0, 1);
        this->m_mTiles["residential"]   = Tile(this->m_iTileSize, 1, m_oTextureManager.getRef("residential"), { oAnim, oAnim, oAnim, oAnim, oAnim, oAnim }, TileType::RESIDENTIAL, 300, 50, 6);
        this->m_mTiles["commercial"]    = Tile(this->m_iTileSize, 1, m_oTextureManager.getRef("commercial"), { oAnim, oAnim, oAnim, oAnim }, TileType::COMMERCIAL, 300, 50, 4);
        this->m_mTiles["industrial"]    = Tile(this->m_iTileSize, 1, m_oTextureManager.getRef("industrial"), { oAnim, oAnim, oAnim, oAnim }, TileType::INDUSTRIAL, 300, 50, 4);
        this->m_mTiles["road"]          = Tile(this->m_iTileSize, 1, m_oTextureManager.getRef("road"), { oAnim, oAnim, oAnim, oAnim, oAnim, oAnim, oAnim, oAnim, oAnim, oAnim, oAnim }, TileType::ROAD, 100, 0, 1);

        return;
    }

    void Game::loadTextures() {
        m_oTextureManager.loadTexture("grass", "GameFiles/media/grass.png");
        m_oTextureManager.loadTexture("forest", "GameFiles/media/forest.png");
        m_oTextureManager.loadTexture("water", "GameFiles/media/water.png");
        m_oTextureManager.loadTexture("residential", "GameFiles/media/residential.png");
        m_oTextureManager.loadTexture("commercial", "GameFiles/media/commercial.png");
        m_oTextureManager.loadTexture("industrial", "GameFiles/media/industrial.png");
        m_oTextureManager.loadTexture("road", "GameFiles/media/road.png");
        m_oTextureManager.loadTexture("background", "GameFiles/media/background.png");
    }

    void Game::pushState(GameState *pState) {
        this->m_sStates.push(pState);

        return;
    }

    void Game::popState() {
        delete this->m_sStates.top();

        this->m_sStates.pop();
        
        return;
    }

    void Game::changeState(GameState *pState) {
        if (!this->m_sStates.empty()) {
            popState();
        }

        pushState(pState);

        return;
    }

    GameState *Game::peekState() {
        if (this->m_sStates.empty()) {
            return nullptr;
        }

        return this->m_sStates.top();
    }

    void Game::gameLoop() {
        sf::Clock oClock;

        while (this->m_oWindow.isOpen()) {
            sf::Time oTime = oClock.restart();

            float fDT = oTime.asSeconds();

            if (peekState() == nullptr) {
                continue;
            }

            peekState()->handleInput();
            peekState()->update(fDT);

            this->m_oWindow.clear(sf::Color::Black);

            peekState()->draw(fDT);

            this->m_oWindow.display();
        }
    }

    Game::Game() {
        this->loadTextures();
        this->loadTiles();

        this->m_oWindow.create(sf::VideoMode(800, 600), "City");
        this->m_oWindow.setFramerateLimit(60);

        this->m_oBackground.setTexture(this->m_oTextureManager.getRef("background"));
    }

    Game::~Game() {
        while (!this->m_sStates.empty()) {
            popState();
        }
    }
};
