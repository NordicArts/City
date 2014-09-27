#ifndef NordicArts_City_Game_Map_H
#define NordicArts_City_Game_Map_H

#include <SFML/Graphics.hpp>

#include <string>
#include <map>
#include <vector>

#include <Tile/Tile.hpp>

namespace NordicArts {
    class Map {
    // Variables   
    public:
        unsigned int        m_iWidth;
        unsigned int        m_iHeight;
        unsigned int        m_iTileSize;
        unsigned int        m_iNumSelected;
        unsigned int        m_iNumRegions[1];

        std::vector<int>    m_vResources;
        std::vector<Tile>   m_vTiles;

    protected:
    private:

    // Methods
    public:
        Map();
        Map(cosnt std::string &cFile, unsigned int iWidth, unsigned int iHeight, std::map<std::string, Tile> &mTiles);

        void load(const std::string &cFile, unsigned int iWidth, unsigned int iHeight, std::map<std::string, Tile> &mTiles);
        void save(const std::string &cFile);
        void draw(sf::RenderWindow &oWindow, float fDT);
        void findConnectedRegions(std::vector<TileType> vWhileList, int iType);
        void updateDirection(TileType eTileType);

    protected:
    private:
        void depthFirstSearch(std::vector<TileType> &oWhiteList, sf::Vector2i vPos, int iLabel, int iType);

    };
};

#endif
