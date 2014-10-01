#include <SFML/Graphics.hpp>

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>

#include <Map/Map.hpp>
#include <Tile/Tile.hpp>

namespace NordicArts {
    Map::Map() : m_iTileSize(8), m_iWidth(0), m_iHeight(0), m_iNumSelected(0) {
        m_iNumRegions[0] = 1;
    }
    Map::Map(const std::string &cFile, unsigned int iWidth, unsigned int iHeight, std::map<std::string, Tile> &oTiles) : m_iTileSize(8), m_iNumSelected(0) {
        load(cFile, iWidth, iHeight, oTiles);
    }

    void Map::load(const std::string &cFile, unsigned int iWidth, unsigned int iHeight, std::map<std::string, Tile> &oTiles) {
        std::ifstream fFile;
        fFile.open(cFile, (std::ios::in | std::ios::binary));

        this->m_iWidth  = iWidth;
        this->m_iHeight = iHeight;

        for (int iPos = 0; iPos < (this->m_iWidth * this->m_iHeight); ++iPos) {
            this->m_vResources.push_back(255);

            this->m_vSelected.push_back(0);

            TileType eTileType;
            fFile.read((char *)&eTileType, sizeof(int));
            switch (eTileType) {
                case TileType::FOREST: {
                    this->m_vTiles.push_back(oTiles.at("forest"));
                    break;
                }
                case TileType::WATER: {
                    this->m_vTiles.push_back(oTiles.at("water"));
                    break;
                }
                case TileType::RESIDENTIAL: {
                    this->m_vTiles.push_back(oTiles.at("residential"));
                    break;
                }
                case TileType::COMMERCIAL: {
                    this->m_vTiles.push_back(oTiles.at("commercial"));
                    break;
                }
                case TileType::INDUSTRIAL: {
                    this->m_vTiles.push_back(oTiles.at("industrial"));
                    break;
                }
                case TileType::ROAD: {
                    this->m_vTiles.push_back(oTiles.at("road"));
                    break;
                }
                case TileType::VOID:
                case TileType::GRASS:
                default: {
                    this->m_vTiles.push_back(oTiles.at("grass"));
                    break;
                }
            }

            Tile &oTile = this->m_vTiles.back();
            
            fFile.read((char *)&oTile.m_iTileVariant, sizeof(int));
            fFile.read((char *)&oTile.m_iRegions, (sizeof(int) * 1));
            fFile.read((char *)&oTile.m_dPopulation, sizeof(double));
            fFile.read((char *)&oTile.m_fStoredGoods, sizeof(float));
        }

        fFile.close();
    
        return;
    }

    void Map::save(const std::string &cFile) {
        std::ofstream fFile;
        fFile.open(cFile, (std::ios::out | std::ios::binary));

        for (auto oTile : this->m_vTiles) {
            fFile.write((char *)oTile.getTileType(), sizeof(int));
            fFile.write((char *)&oTile.m_iTileVariant, sizeof(int));
            fFile.write((char *)&oTile.m_iRegions, (sizeof(int) * 3));
            fFile.write((char *)&oTile.m_dPopulation, sizeof(double));
            fFile.write((char *)&oTile.m_fStoredGoods, sizeof(float));
        }

        fFile.close();
    
        return;
    }

    void Map::draw(sf::RenderWindow &oWindow, float fDT) {
        for (int y = 0; y < this->m_iHeight; ++y) {
            for (int x = 0; x < this->m_iWidth; ++x) {
                sf::Vector2f vPos;
                vPos.x = (((x - y) * this->m_iTileSize) + (this->m_iWidth * this->m_iHeight));
                vPos.y = (((x + y) * this->m_iTileSize) * 0.5);
                this->m_vTiles[((y * this->m_iWidth) + x)].getSprite().setPosition(vPos);

                if (this->m_vSelected[((y * this->m_iWidth) + x)]) {
                    this->m_vTiles[((y * this->m_iWidth) + x)].getSprite().setColor(sf::Color(0x7d, 0x7d, 0x7d));
                } else {
                    this->m_vTiles[((y * this->m_iWidth) + x)].getSprite().setColor(sf::Color(0xff, 0xff, 0xff));
                }

                this->m_vTiles[((y * this->m_iWidth) + x)].draw(oWindow, fDT);
            }
        }

        return;
    }

    void Map::updateDirection(TileType eTileType) {
        for (int y = 0; y < this->m_iHeight; ++y) {
            for (int x = 0; x < this->m_iWidth; ++x) {
                int iPos = (y * this->m_iWidth + x);
        
                if (this->m_vTiles[iPos].getTileType() != eTileType) {
                    continue;
                }

                bool bAdjacentTiles[3][3] = {
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
                };

                if ((x > 0) && (y > 0)) {
                    bAdjacentTiles[0][0] = ((this->m_vTiles[(y - 1) * this->m_iWidth + (x - 1)].getTileType()) == eTileType);
                }

                if (y > 0) {
                    bAdjacentTiles[0][1] = ((this->m_vTiles[(y -1) * this->m_iWidth + x].getTileType()) == eTileType);
                }

                if ((x < (this->m_iWidth - 1)) && (y > 0)) {
                    bAdjacentTiles[0][2] = ((this->m_vTiles[(y -1) * this->m_iWidth + (x + 1)].getTileType()) == eTileType);
                }

                if (x > 0) {
                    bAdjacentTiles[1][0] = ((this->m_vTiles[y * this->m_iWidth + (x - 1)].getTileType()) == eTileType);
                }

                if (x < (m_iWidth - 1)) {
                    bAdjacentTiles[1][2] = ((this->m_vTiles[y * this->m_iWidth + (x + 1)].getTileType()) == eTileType);
                }

                if ((x > 0) && (y < (this->m_iHeight - 1))) {
                    bAdjacentTiles[2][0] = ((this->m_vTiles[(y + 1) * this->m_iWidth + (x - 1)].getTileType()) == eTileType);
                }

                if (y < (this->m_iHeight - 1)) {
                    bAdjacentTiles[2][1] = ((this->m_vTiles[(y + 1) * this->m_iWidth + x].getTileType()) == eTileType);
                }

                if ((x < (this->m_iWidth - 1)) && (y < (this->m_iHeight - 1))) {
                    bAdjacentTiles[2][2] = ((this->m_vTiles[(y + 1) * this->m_iWidth + (x + 1)].getTileType()) == eTileType);
                }

                if (bAdjacentTiles[1][0] && bAdjacentTiles[1][2] && bAdjacentTiles[0][1] && bAdjacentTiles[2][1]) {
                    this->m_vTiles[iPos].m_iTileVariant = 2;
                } else if (bAdjacentTiles[1][0] && bAdjacentTiles[1][2] && bAdjacentTiles[0][1]) {
                    this->m_vTiles[iPos].m_iTileVariant = 7;
                } else if (bAdjacentTiles[1][0] && bAdjacentTiles[1][2] && bAdjacentTiles[2][1]) {
                    this->m_vTiles[iPos].m_iTileVariant = 8;
                } else if (bAdjacentTiles[0][1] && bAdjacentTiles[2][1] && bAdjacentTiles[1][0]) {
                    this->m_vTiles[iPos].m_iTileVariant = 9;
                } else if (bAdjacentTiles[0][1] && bAdjacentTiles[2][1] && bAdjacentTiles[1][2]) {
                    this->m_vTiles[iPos].m_iTileVariant = 10;
                } else if (bAdjacentTiles[1][0] && bAdjacentTiles[1][2]) {
                    this->m_vTiles[iPos].m_iTileVariant = 0;
                } else if (bAdjacentTiles[0][1] && bAdjacentTiles[2][1]) {
                    this->m_vTiles[iPos].m_iTileVariant = 1;
                } else if (bAdjacentTiles[2][1] && bAdjacentTiles[1][0]) {
                    this->m_vTiles[iPos].m_iTileVariant = 3;
                } else if (bAdjacentTiles[0][1] && bAdjacentTiles[0][1]) {
                    this->m_vTiles[iPos].m_iTileVariant = 4;
                } else if (bAdjacentTiles[1][0] && bAdjacentTiles[0][1]) {
                    this->m_vTiles[iPos].m_iTileVariant = 5;
                } else if (bAdjacentTiles[2][1] && bAdjacentTiles[1][2]) {
                    this->m_vTiles[iPos].m_iTileVariant = 6;
                } else if (bAdjacentTiles[1][0]) {
                    this->m_vTiles[iPos].m_iTileVariant = 0;
                } else if (bAdjacentTiles[1][2]) {
                    this->m_vTiles[iPos].m_iTileVariant = 0;
                } else if (bAdjacentTiles[0][1]) {
                    this->m_vTiles[iPos].m_iTileVariant = 1;
                } else if (bAdjacentTiles[2][1]) {
                    this->m_vTiles[iPos].m_iTileVariant = 1;
                }
            }
        }

        return;
    }

    void Map::depthFirstSearch(std::vector<TileType> &oList, sf::Vector2i vPos, int iLabel, int iRegionType = 0) {
        // Invalid positions
        if ((vPos.x < 0) || (vPos.x >= this->m_iWidth)) {
            return;
        }

        if ((vPos.y < 0) || (vPos.y >= this->m_iHeight)) {
            return;
        }

        if (this->m_vTiles[((vPos.y * this->m_iWidth) + vPos.x)].m_iRegions[iRegionType] != 0) {
            return;
        }

        // Found type
        bool bFound = false;
        for (auto oType : oList) {
            if (oType == this->m_vTiles[((vPos.y * this->m_iWidth) + vPos.x)].getTileType()) {
                bFound = true;

                break;
            }
        }
        if (!bFound) { 
            return;
        }

        this->m_vTiles[((vPos.y * this->m_iWidth) + vPos.x)].m_iRegions[iRegionType] = iLabel;
    
        depthFirstSearch(oList, (vPos + sf::Vector2i(-1, 0)), iLabel, iRegionType);
        depthFirstSearch(oList, (vPos + sf::Vector2i(0, 1)), iLabel, iRegionType);
        depthFirstSearch(oList, (vPos + sf::Vector2i(1, 0)), iLabel, iRegionType);
        depthFirstSearch(oList, (vPos + sf::Vector2i(0, -1)), iLabel, iRegionType);

        return;
    }

    void Map::findConnectedRegions(std::vector<TileType> oList, int iRegionType = 0) {
        int iRegions = 1;

        for (auto &oTile : this->m_vTiles) {
            oTile.m_iRegions[iRegionType] = 0;
        }

        for (int y = 0; y < this->m_iHeight; ++y) {
            for (int x = 0; x < this->m_iWidth; ++x) {
                bool bFound = false;
                for (auto oType : oList) {
                    if (oType == this->m_vTiles[((y * this->m_iWidth) + x)].getTileType()) {
                        bFound = true;

                        break;
                    }
                }

                if ((this->m_vTiles[((y * this->m_iWidth) + x)].m_iRegions[iRegionType] == 0) && bFound) {
                    depthFirstSearch(oList, sf::Vector2i(x, y), iRegions++, iRegionType);
                }
            }
        }

        this->m_iNumRegions[iRegionType] = iRegions;
    }

    void Map::clearSelected() {
        for (auto &oTile : this->m_vSelected) {
            oTile = 0;
        }

        this->m_iNumSelected = 0;
        
        return;
    }

    void Map::select(sf::Vector2i vStart, sf::Vector2i vEnd, std::vector<TileType> vList) {
        if (vEnd.y < vStart.y) {
            std::swap(vStart.y, vEnd.y);
        }
        if (vEnd.x < vStart.x) {
            std::swap(vStart.x, vEnd.x);
        }

        // End X
        if (vEnd.x >= this->m_iWidth) {
            vEnd.x = (this->m_iWidth - 1);
        } else if (vEnd.x < 0) {
            vEnd.x = 0;
        }

        // End Y
        if (vEnd.y >= this->m_iHeight) {
            vEnd.y = (this->m_iHeight - 1);
        } else if (vEnd.y < 0) {
            vEnd.y = 0;
        }

        // Start X
        if (vStart.x >= this->m_iWidth) {
            vStart.x = (this->m_iWidth - 1);
        } else if (vStart.x < 0) {
            vStart.x = 0;
        }

        // Start Y
        if (vStart.y >= this->m_iHeight) {
            vStart.y = (this->m_iHeight - 1);
        } else if (vStart.y < 0) {
            vStart.y = 0;
        }

        for (int y = vStart.y; y < vEnd.y; ++y) {
            for (int x = vStart.x; x < vEnd.x; ++x) {
                this->m_vSelected[((y * this->m_iWidth) + x)] = 1;
            
                ++this->m_iNumSelected;

                for (auto eType : vList) {
                    if (m_vTiles[((y * this->m_iWidth) + x)].getTileType() == eType) {
                        this->m_vSelected[((y * this->m_iWidth) + x)] = 2;

                        --this->m_iNumSelected;
                
                        break;
                    }
                }
            }
        }

        return;
    }

    unsigned int Map::getTileSize() const {
        return this->m_iTileSize;
    }
    void Map::setTileSize(unsigned int iSize) {
        this->m_iTileSize = iSize;
    }

    unsigned int Map::getNumSelected() const {
        return this->m_iNumSelected;
    }

    unsigned int Map::getWidth() const {
        return this->m_iWidth;
    }
    unsigned int Map::getHeight() const {
        return this->m_iHeight;
    }
};                
        
