#include <SFML/Graphics.hpp>

#include <GameState/Start.hpp>
#include <GameState/Editor.hpp>
#include <GameState.hpp>

namespace NordicArts {
    void GameStateStart::draw(const float fDT) {
        this->m_pGame->m_oWindow.setView(this->m_oView);
        this->m_pGame->m_oWindow.clear(sf::Color::Black);
        this->m_pGame->m_oWindow.draw(this->m_pGame->m_oBackground);

        for (auto oGUI : this->m_mGUISystem) {
            this->m_pGame->m_oWindow.draw(oGUI.second);
        }

        return;
    }

    void GameStateStart::update(const float fDT) {
    }

    void GameStateStart::handleInput() {
        sf::Event oEvent;

        sf::Vector2f vMousePos = this->m_pGame->m_oWindow.mapPixelToCoords(sf::Mouse::getPosition(this->m_pGame->m_oWindow), this->m_oView);

        while (this->m_pGame->m_oWindow.pollEvent(oEvent)) {
            switch (oEvent.type) {
                case sf::Event::Closed: {
                    m_pGame->m_oWindow.close();
            
                    break;
                }

                case sf::Event::Resized: {
                    this->m_oView.setSize(oEvent.size.width, oEvent.size.height);
                    this->m_pGame->m_oBackground.setPosition(this->m_pGame->m_oWindow.mapPixelToCoords(sf::Vector2i(0, 0)));

                    sf::Vector2f vPos = sf::Vector2f(oEvent.size.width, oEvent.size.height);
                    vPos *= 0.5f;
                    vPos = this->m_pGame->m_oWindow.mapPixelToCoords(sf::Vector2i(vPos), this->m_oView);
                    this->m_mGUISystem.at("menu").setPosition(vPos);

                    this->m_pGame->m_oBackground.setScale(
                        (float(oEvent.size.width) / float(this->m_pGame->m_oBackground.getTexture()->getSize().x)),
                        (float(oEvent.size.height) / float(this->m_pGame->m_oBackground.getTexture()->getSize().y))
                    );

                    break;
                }

                case sf::Event::MouseMoved: {
                    this->m_mGUISystem.at("menu").highlight(this->m_mGUISystem.at("menu").getEntry(vMousePos));

                    break;
                }

                case sf::Event::MouseButtonPressed: {
                    if (oEvent.mouseButton.button == sf::Mouse::Left) {
                        std::string cMessage = this->m_mGUISystem.at("menu").activate(vMousePos);
                        if (cMessage == "load_game") {
                            this->loadGame();
                        }
                    }
                    break;
                }

                case sf::Event::KeyPressed: {
                    if (oEvent.key.code == sf::Keyboard::Escape) {
                        this->m_pGame->m_oWindow.close();
                    } else if (oEvent.key.code == sf::Keyboard::Space) {
                        this->loadGame();
                    }
                
                    break;
                }

                default: break;
            }
        }

        return;
    }

    void GameStateStart::loadGame() {
        this->m_pGame->pushState(new GameStateEditor(this->m_pGame));
        
        return;
    }

    GameStateStart::GameStateStart(Game *pGame) {
        this->m_pGame = pGame;

        sf::Vector2f vPos = sf::Vector2f(this->m_pGame->m_oWindow.getSize());
        this->m_oView.setSize(vPos);

        vPos *= 0.5f;
        this->m_oView.setCenter(vPos);

        this->m_mGUISystem.emplace("menu", GUI(sf::Vector2f(192, 32), 4, false, m_pGame->m_mStyleSheets.at("button"), {
            std::make_pair("Load Game", "load_game")
        }));
        this->m_mGUISystem.at("menu").setPosition(vPos);
        this->m_mGUISystem.at("menu").setOrigin(96, ((32 * 1) / 2));
        this->m_mGUISystem.at("menu").show();
    }
};
