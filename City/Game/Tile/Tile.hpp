#ifndef NordicArts_City_Engine_Tile_Tile_H
#define NordicArts_City_Engine_Tile_Tile_H

#include <SFML/Graphics.hpp>

#include <vector>

#include <Animation/Handler.hpp>

namespace NordicArts {
    enum class TileType {
        VOID,
        GRASS,
        FOREST,
        WATER,
        RESIDENTIAL,
        COMMERCIAL,
        INDUSTRIAL,
        ROAD
    };

    std::string tileTypeToString(TileType eType);

    class Tile {
    // Variables
    public:
        AnimationHandler    m_oAnimationHandler;

        sf::Sprite          m_oSprite;
        
        TileType            m_eTileType;

        int                 m_iTileVariant;

        unsigned int        m_iRegions[1];
        unsigned int        m_iCost;
        unsigned int        m_iMaxPopPerLevel;
        unsigned int        m_iMaxLevels;
        
        double              m_dPopulation;

        float               m_fProduction;
        float               m_fStoredGoods;

    protected:
    private:

    // Methods
    public:
        Tile();
        Tile(const unsigned int iTileSize, const unsigned int iHeight, sf::Texture &oTexture, const std::vector<Animation> &vAnimations, const TileType eTileType, const unsigned int iCost, const unsigned int iMaxPopPerLevel, const unsigned int iMaxLevels);

        void draw(sf::RenderWindow &oWindow, float fDT);
        void update();

        std::string getCost() const;

    protected:
    private:

    };
};

#endif
