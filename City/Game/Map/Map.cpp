#include <SFML/Graphics.hpp>

#include <string>
#include <map>
#include <vector>
#include <fstream>

#include <Map/Map.hpp>
#include <Tile/Tile.hpp>

namespace NordicArts {
    Map::Map() : m_iTileSize(8), m_iWidth(0), m_iHeight(0) {
        m_iNumRegions[0] = 1;
    }
    Map::Map(const std::string &cFile, unsigned int iWidth, unsigned int iHeight, std::map<std::string, Tile> &oTiles) : m_iTileSize(8) {
        load(cFile, iWidth, iHeight, oTiles);
    }

    void Map::load(const std::string &cFile, unsigned int iWidth, unsigned int iHeight, std::map<std::string, Tile> &oTiles) {
        std::ifstream fFile;
        fFile.open(cFile, (std::ios::in | std::ios::binary));

        this->m_iWidth  = iWidth;
        this->m_iHeight = iHeight;

        for (int iPos = 0; iPos < (this->m_iWidth * this->m_iHeight); ++iPos) {
            this->m_vResources.push_back(255);

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
        fFile.open(cFile, (std::ios:out | std::ios::binary));

        for (auto oTile : this->m_vTiles) {
            fFile.write((char *)&oTile.m_iTileType, sizeof(int));
            fFile.write((char *)&oTile.m_iTileVariant, sizeof(int));
            fFile.write((char *)&oTile.m_iRegions, (sizeof(int) * 3));
            fFile.write((char *)&oTile.m_dPopulation, sizeof(double));
            fFile.write((char *)&oTile.m_fStoredGoods, sizeof(float));
        }

        fFile.close();
    
        return;
    }

    void Map::draw(sf::RenderWinod &oWindow, float fDT) {
        for (int y = 0; y < this->m_iHeight; ++y) {
            for (int x = 0; x < this->m_iWidth; ++x) {
                sf::Vector2f vPos;
                vPos.x = (((x - y) * this->m_iTileSize) + (this->m_iWidth * this->m_iHeight));
                vPos.y = (((x + y) * this->m_iTileSize) * 0.5);
                this->m_vTiles[(y * this->m_iWidth + x)].m_oSprite.setPosition(vPos);
            }
        }

        return;
    }

    void Map::updateDirection(TileType eTileType) {
        for (int y = 0; y < this->m_iHeight; ++y) {
            for (int x = 0; x < this->m_iWidth; ++x) {
                int iPos = (y * this->m_iWidth + x);
        
                if (this->m_vTiles[iPos].m_eTileType != eTileType) {
                    continue;
                }

                bool bAdjacentTiles[3][3] = {
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
                };

                if ((x > 0) && (y > 0)) {
                    bAdjacentTiles[0][0] = ((this->m_vTiles[(y - 1) * this->m_iWidth + (x - 1)].m_eTileType) == eTileType);
                }

                if (y > 0) {
                    bAdjacentTiles[0][1] = ((this->m_vTiles[(y -1) * this->m_iWidth + x].m_eTileType) == eTileType);
                }

                if ((x < (this->m_iWidth - 1)) && (y > 0)) {
                    bAdjacentTiles[0][2] = ((this->m_vTiles[(y -1) * this->m_iWidth + (x + 1)].m_eTileType) == eTileType);
                }

                if (x > 0) {
                    bAdjacentTiles[1][0] = ((this->m_vTiles[y * this->m_iWidth + (x - 1)].m_eTileType) == eTileType);
                }

                if (x < (m_iWidth - 1)) {
                    bAdjacentTiles[1][2] = ((this->m_vTiles[y * this->m_iWidth + (x + 1)].m_eTileType) == eTileType);
                }

                if ((x > 0) && (y < (this->m_iHeight - 1))) {
                    bAdjacentTiles[2][0] = ((this->m_vTiles[(y + 1) * this->m_iWidth + (x - 1)].m_eTileType) == eTileType);
                }

                if (y < (this->m_iHeight - 1)) {
                    bAdjacentTiles[2][1] = ((this->m_vTiles[(y + 1) * this->m_iWidth + x].m_eTileType) == eTileType);
                }

                if ((x < (this->m_iWidth - 1)) && (y < (this->m_iHeight - 1))) {
                    bAdjacentTiles[2][2] = ((this->m_vTiles[(y + 1) * this->m_iWidth + (x + 1)].m_eTileType) == eTileType);
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

    void Map::depthFirstSearch(std::vector<TileType> &oList) {
        
};
