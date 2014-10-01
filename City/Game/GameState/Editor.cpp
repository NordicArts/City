#include <SFML/Graphics.hpp>

#include <GameState.hpp>
#include <GameState/Editor.hpp>
#include <Map/Map.hpp>

namespace NordicArts {
    void GameStateEditor::draw(const float fDT) {
        this->m_pGame->m_oWindow.clear(sf::Color::Black);

        this->m_pGame->m_oWindow.setView(this->m_oGUIView);
        this->m_pGame->m_oWindow.draw(this->m_pGame->m_oBackground);

        this->m_pGame->m_oWindow.setView(this->m_oGameView);
        this->m_oCity.m_oMap.draw(this->m_pGame->m_oWindow, fDT);

        this->m_pGame->m_oWindow.setView(this->m_oGUIView);
        for (auto oGUI : this->m_mGUISystem) {
            this->m_pGame->m_oWindow.draw(oGUI.second);
        }

        return;
    }

    void GameStateEditor::update(const float fDT) {
        this->m_oCity.update(fDT);

        this->m_mGUISystem.at("infoBar").setEntryText(0, ("Day" + std::to_string(this->m_oCity.m_iDay)));
        this->m_mGUISystem.at("infoBar").setEntryText(1, ("$" + std::to_string(this->m_oCity.m_dFunds)));
        this->m_mGUISystem.at("infoBar").setEntryText(2, (std::to_string(this->m_oCity.m_dPopulation) + "(" + std::to_string(this->m_oCity.getHomeless()) + ")"));
        this->m_mGUISystem.at("infoBar").setEntryText(3, (std::to_string(this->m_oCity.m_dEmployable) + "(" + std::to_string(this->m_oCity.getUnemployed()) + ")"));
        this->m_mGUISystem.at("infoBar").setEntryText(4, tileTypeToString(m_pCurrentTile->m_eTileType));

        return;
    }

    void GameStateEditor::handleInput() {
        sf::Event oEvent;

        sf::Vector2f vGUIPos    = this->m_pGame->m_oWindow.mapPixelToCoords(sf::Mouse::getPosition(this->m_pGame->m_oWindow), this->m_oGUIView);
        sf::Vector2f vGamePos   = this->m_pGame->m_oWindow.mapPixelToCoords(sf::Mouse::getPosition(this->m_pGame->m_oWindow), this->m_oGameView);

        while (this->m_pGame->m_oWindow.pollEvent(oEvent)) {
            switch (oEvent.type) {
                case sf::Event::Closed: {
                    this->m_pGame->m_oWindow.close();
                
                    break;
                }

                case sf::Event::Resized: {
                    m_oGameView.setSize(oEvent.size.width, oEvent.size.height);
                    m_oGameView.zoom(m_fZoomLevel);

                    m_oGUIView.setSize(oEvent.size.width, oEvent.size.height);

                    this->m_mGUISystem.at("infoBar").setDimensions(sf::Vector2f((oEvent.size.width / this->m_mGUISystem.at("infobar").m_vEntries.size()), 16));
                    this->m_mGUISystem.at("infoBar").setPosition(this->m_pGame->m_oWindow.mapPixelToCoords(sf::Vector2i(0, (oEvent.size.height - 16)), this->m_oGUIView));
                    this->m_mGUISystem.at("infoBar").show();

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
                    } else if (this->m_eActionState == ActionState::SELECTING) {
                        sf::Vector2f vPos = this->m_pGame->m_oWindow.mapPixelToCoords(sf::Mouse::getPosition(this->m_pGame->m_oWindow), this->m_oGameView);
                        m_vSelectionEnd.x = ((vPos.x / this->m_oMap.m_iTileSize) + (vPos.x / (2 * this->m_oMap.m_iTileSize)) - (this->m_oMap.m_iWidth * 0.5) - 0.5);
                        m_vSelectionEnd.y = ((vPos.y / this->m_oMap.m_iTileSize) - (vPos.x / (2 * this->m_oMap.m_iTileSize)) - (this->m_oMap.m_iWidth * 0.5) + 0.5);

                        this->m_oMap.clearSelected();
                        
                        if (this->m_pCurrentTile->m_eTileType == TileType::GRASS) {
                            this->m_oMap.select(m_vSelectionStart, m_vSelectionEnd, { 
                                this->m_pCurrentTile->m_eTileType, 
                                TileType::WATER 
                            });
                        } else {
                            this->m_oMap.select(m_vSelectionStart, m_vSelectionEnd, {
                                this->m_pCurrentTile->m_eTileType,
                                TileType::FOREST,
                                TileType::WATER,
                                TileType::ROAD,
                                TileType::RESIDENTIAL,
                                TileType::COMMERCIAL,
                                TileType::INDUSTRIAL
                            });
                        }

                        this->m_mGUISystem.at("selectionCostText").setEntryText(0, "$" + std::to_string(this->m_pCurrentTile->m_iCost * this->m_oCity.m_oMap.m_iNumSelected));
                        if (this->m_oCity.m_dFunds <= (this->m_oCity.m_oMap.m_iNumSelected * this->m_pCurrentTile->m_iCost)) {
                            this->m_mGUISystem.at("selectionCostText").highlight(0);
                        } else {
                            this->m_mGUISystem.at("selectionCostText").highlight(-1);
                        }
                        this->m_mGUISystem.at("selectionCostText").setPosition(vGUIPos + sf::Vector2f(16, -16));
                        this->m_mGUISystem.at("selectionCostText").show();
                    }

                    this->m_mGUISystem.at("rightClickMenu").highlight(this->m_mGUISystem.at("rightClickMenu").getEntry(vGUIPos));

                    break;
                }
    
                case sf::Event::MouseButtonPressed: {
                    if (oEvent.mouseButton.button == sf::Mouse::Middle) {
                        this->m_mGUISystem.at("rightClickMenu").hide();
                        this->m_mGUISystem.at("selectionCostText").hide();

                        if (this->m_eActionState != ActionState::PANNING) {
                            this->m_eActionState = ActionState::PANNING;
                            
                            this->m_vPanningAnchor = sf::Mouse::getPosition(this->m_pGame->m_oWindow);
                        }
                    } else if (oEvent.mouseButton.button == sf::Mouse::Left) {
                        if (this->m_mGUISystem.at("rightClickMenu").m_bVisible == true) {
                            std::string cMessage = this->m_mGUISystem.at("rightClickMenu").activate(vGUIPos);
                            if ((cMessage != "flatten") && (cMessage != "null")) {
                                this->m_pCurrentTile = &this->m_pGame->m_mTiles.at(cMessage);
                            }

                            this->m_mGUISystem.at("rightClickMenu").hide();
                        } else {
                            if (this->m_eActionState != ActionState::SELECTING) {
                                this->m_eActionState = ActionState::SELECTING;
    
                                sf::Vector2f vPos = this->m_pGame->m_oWindow.mapPixelToCoords(sf::Mouse::getPosition(this->m_pGame->m_oWindow), this->m_oGameView);
                                m_vSelectionStart.x = ((vPos.x / this->m_oMap.m_iTileSize) + (vPos.x / (2 * this->m_oMap.m_iTileSize)) - (this->m_oMap.m_iWidth * 0.5) - 0.5);
                                m_vSelectionStart.y = ((vPos.y / this->m_oMap.m_iTileSize) - (vPos.x / (2 * this->m_oMap.m_iTileSize)) - (this->m_oMap.m_iWidth * 0.5) + 0.5);
                            }
                        }
                    } else if (oEvent.mouseButton.button == sf::Mouse::Right) {
                        if (this->m_eActionState == ActionState::SELECTING) {
                            this->m_eActionState = ActionState::NONE;

                            this->m_mGUISystem.at("selectionCostText").hide();

                            this->m_oCity.m_oMap.clearSelected();
                        } else {
                            sf::Vector2f vPos = vGUIPos;

                            if (vPos.x > (this->m_pGame->m_oWindow.getSize().x - this->m_mGUISystem.at("rightClickMenu").getSize().x)) {
                                vPos -= sf::Vector2f(this->m_mGUISystem.at("rightClickMenu").getSize().x, 0);
                            }

                            if (vPos.y > (this->m_pGame->m_oWindow.getSize().y - this->m_mGUISystem.at("rightClickMenu").getSize().y)) {
                                vPos -= sf::Vector2f(0, this->m_mGUISystem.at("rightClickMenu").getSize().y);
                            }

                            this->m_mGUISystem.at("rightClickMenu").setPosition(vPos);
                            this->m_mGUISystem.at("rightClickMenu").show();
                        }
                    }
                    break;
                }

                case sf::Event::MouseButtonReleased: {
                    if (oEvent.mouseButton.button == sf::Mouse::Middle) {
                        this->m_eActionState = ActionState::NONE;
                    } else if (oEvent.mouseButton.button == sf::Mouse::Left) {
                        if (this->m_eActionState == ActionState::SELECTING) {
                            if (this->m_pCurrentTile != nullptr) {
                                unsigned int iCost = (this->m_pCurrentTile->m_iCost * this->m_oCity.m_oMap.m_iNumSelected);
                                if (this->m_oCity.m_dFunds >= iCost) {
                                    this->m_oCity.bulldoze(*this->m_pCurrentTile);
                                    this->m_oCity.m_dFunds -= (this->m_pCurrentTile->m_iCost * this->m_oCity.m_oMap.m_iNumSelected);
                                    this->m_oCity.tileChanged();
                                }
                            }

                            this->m_mGUISystem.at("selectionCostText").hide();

                            this->m_eActionState = ActionState::NONE;

                            this->m_oMap.clearSelected();
                        }
                    }
                    break;
                }

                case sf::Event::MouseWheelMoved: 
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

        this->m_oCity = City("city", this->m_pGame->m_iTileSize, this->m_pGame->m_mTiles);
        this->m_oCity.shuffleTiles();

        this->m_mGUISystem.emplace("rightClickMenu", GUI(sf::Vector2f(196, 16), 2, false, this->m_pGame->m_mStyleSheets.at("button"),  {
            std::make_pair("Flatten $"              + this->m_pGame->m_mTiles["grass"].getCost(), "grass"),
            std::make_pair("Forest $"               + this->m_pGame->m_mTiles["forest"].getCost(), "forest"),
            std::make_pair("Residential Zone $"     + this->m_pGame->m_mTiles["residential"].getCost(), "residential"),
            std::make_pair("Commerical Zone $"      + this->m_pGame->m_mTiles["commercial"].getCost(), "commercial"),
            std::make_pair("Industrial Zone $"      + this->m_pGame->m_mTiles["industial"].getCost(), "industrial"),
            std::make_pair("Road $"                 + this->m_pGame->m_mTiles["road"].getCost(), "road")
        }));

        this->m_mGUISystem.emplace("selectionCostText", GUI(sf::Vector2f(196, 16), 0, false, this->m_pGame->m_mStyleSheets.at("text"), {
            std::make_pair("", "")
        }));

        this->m_mGUISystem.emplace("infoBar", GUI(sf::Vector2f((this->m_pGame->m_oWindow.getSize().x / 5), 16), 2, true, this->m_pGame->m_mStyleSheets.at("button"), {
            std::make_pair("time", "time"),
            std::make_pair("funds", "funds"),
            std::make_pair("population", "population"),
            std::make_pair("employment", "employment"),
            std::make_pair("current tile", "tile")
        }));
        this->m_mGUISystem.at("infoBar").setPosition(sf::Vector2f(0, (this->m_pGame->m_oWindow.getSize().y - 16)));
        this->m_mGUISystem.at("infoBar").show();

        this->m_fZoomLevel = 1.0f;

        sf::Vector2f vCenter(this->m_oMap.m_iWidth, (this->m_oMap.m_iHeight * 0.5));
        vCenter *= float(this->m_oMap.m_iTileSize);
        m_oGameView.setCenter(vCenter);

        this->m_vSelectionStart = sf::Vector2i(0, 0);
        this->m_vSelectionEnd   = sf::Vector2i(0, 0);

        this->m_pCurrentTile    = &this->m_pGame->m_mTiles.at("grass");

        this->m_eActionState = ActionState::NONE;
    }
};
