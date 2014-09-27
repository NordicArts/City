#include <SFML/Graphics.hpp>

#include <Animation/Handler.hpp>
#include <Tile/Tile.hpp>

namespace NordicArts {
    Tile::Tile() {}

    Tile::Tile(const unsigned int iTileSize, const unsigned int iHeight, sf::Texture &oTexture, const std::vector<Animation> &vAnimations, const TileType eTileType, const unsigned int iCost, const unsigned int iMaxPopPerLevel, const unsigned int iMaxLevels) : m_eTileType(eTileType), m_iTileVariant(0), m_iCost(iCost), m_dPopulation(0), m_iMaxPopPerLevel(iMaxPopPerLevel), m_iMaxLevels(iMaxLevels), m_fStoredGoods(0), m_fProduction(0) {
        this->m_iRegions[0] = 0;

        this->m_oSprite.setOrigin(sf::Vector2f(0.0f, (iTileSize * (iHeight - 1))));
        this->m_oSprite.setTexture(oTexture);

        this->m_oAnimationHandler.m_oFrameSize = sf::IntRect(0, 0, (iTileSize * 2), (iTileSize * iHeight));
        for (auto oAnimation : vAnimations) {
            this->m_oAnimationHandler.addAnimation(oAnimation);
        }
        this->m_oAnimationHandler.update(0.0f);
    }

    void Tile::draw(sf::RenderWindow &oWindow, float fDT) {
        this->m_oAnimationHandler.changeAnimation(this->m_iTileVariant);
        this->m_oAnimationHandler.update(fDT);

        this->m_oSprite.setTextureRect(this->m_oAnimationHandler.m_oBounds);

        oWindow.draw(this->m_oSprite);

        return;
    }

    void Tile::update() {
        if (
            (
                (this->m_eTileType == TileType::RESIDENTIAL) ||
                (this->m_eTileType == TileType::COMMERCIAL) ||
                (this->m_eTileType == TileType::INDUSTRIAL)
            ) && (
                (this->m_dPopulation == (this->m_iMaxPopPerLevel * (this->m_iTileVariant + 1))) &&
                (this->m_iTileVariant < this->m_iMaxLevels)
            )
        ) {
            if ((rand() % int(1e4)) < (1e2  / (this->m_iTileVariant + 1))) {
                ++this->m_iTileVariant;
            }
        }

        return;
    }
    
    std::string tileTypeToString(TileType eType) {
        switch (eType) {
            case TileType::GRASS:       return "Void";
            case TileType::FOREST:      return "Forest";
            case TileType::WATER:       return "Water";
            case TileType::RESIDENTIAL: return "Residential Zone";
            case TileType::COMMERCIAL:  return "Commercial Zone";
            case TileType::INDUSTRIAL:  return "Industrial Zone";
            case TileType::VOID:
            default: {
                return "Void";
            }
        }
    }
};
