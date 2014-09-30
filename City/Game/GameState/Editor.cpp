#include <SFML/Graphics.hpp>

#include <GameState.hpp>
#include <GameState/Editor.hpp>

namespace NordicArts {
    void GameStateEditor::draw(const float fDT) {
        this->m_pGame->m_oWindow.clear(sf::Color::Black);
        this->m_pGame->m_oWindow.draw(this->m_pGame->m_oBackground);

        return;
    }

    void GameStateEditor::update(const float fDT) {
        return;
    }

    void GameStateEditor::handleInput() {
        sf::Event oEvent;

        while (this->m_pGame->m_oWindow.pollEvent(oEvent)) {
            switch (oEvent.type) {
                case sf::Event::Closed: {
                    this->m_pGame->m_oWindow.close();
                
                    break;
                }

                case sf::Event::Resized: {
                    m_oGameView.setSize(oEvent.size.width, oEvent.size.height);
                    m_oGUIView.setSize(oEvent.size.width, oEvent.size.height);

                    this->m_pGame->m_oBackground.setPosition(this->m_pGame->m_oWindow.mapPixelToCoords(sf::Vector2i(0, 0), this->m_oGUIView));
                    this->m_pGame->m_oBackground.setScale(
                        (float(oEvent.size.width) / float(this->m_pGame->m_oBackground.getTexture()->getSize().x)),
                        (float(oEvent.size.height) / float(this->m_pGame->m_oBackground.getTexture()->getSize().y))
                    );

                    break;
                }

                case sf::Event::MouseMoved: {
                    if (this->m_eActionState == ActionState::PANNING) {
                        sf::Vector2f vPos = sf::Vector2f(sf::Mouse::getPosition(this->m_pGame->m_oWindow) - this->m_vPanningAnchor);

                        m_oGameView.move(-1.0f * vPos * this->m_fZoomLevel);
                    
                        m_vPanningAnchor = sf::Mouse::getPosition(this->m_pGame->m_oWindow);
                    }
                    break;
                }
    
                case sf::Event::MouseButtonPressed: {
                    if (oEvent.mouseButton.button == sf::Mouse::Middle) {
                        if (this->m_eActionState != ActionState::PANNING) {
                            this->m_eActionState = ActionState::PANNING;
                            
                            this->m_vPanningAnchor = sf::Mouse::getPosition(this->m_pGame->m_oWindow);
                        }
                    }
                    break;
                }

                case sf::Event::MouseButtonReleased: {
                    if (oEvent.mouseButton.button == sf::Mouse::Middle) {
                        this->m_eActionState = ActionState::NONE;
                    }
                    break;
                }

                case sf::Event::MouseWheelMoved: {
                    if (oEvent.mouseWheel.delta < 0) {
                        m_oGameView.zoom(2.0f);

                        m_fZoomLevel *= 2.0f;
                    } else {
                        m_oGameView.zoom(0.5f);
        
                        m_fZoomLevel *= 0.5f;
                    }
                    break;
                }
                        
                default: break;
            }
        }

        return;
    }

    GameStateEditor::GameStateEditor(Game *pGame) {
        this->m_pGame = pGame;

        sf::Vector2f vPos = sf::Vector2f(this->m_pGame->m_oWindow.getSize());
        this->m_oGUIView.setSize(vPos);
        this->m_oGameView.setSize(vPos);

        vPos *= 0.5f;
        this->m_oGUIView.setCenter(vPos);
        this->m_oGameView.setCenter(vPos);

        m_oMap = Map("GameFiles/cityMap.dat", 64, 64, m_pGame->m_mTiles);

        this->m_fZoomLevel = 1.0f;

        sf::Vector2f vCenter(this->m_oMap.m_iWidth, (this->m_oMap.m_iHeight * 0.5));
        vCenter *= float(this->m_oMap.m_iTileSize);
        m_oGameView.setCenter(vCenter);

        this->m_eActionState = ActionState::NONE;
    }
};
