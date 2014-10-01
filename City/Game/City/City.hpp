#ifndef NordicArts_City_Game_City_H
#define NordicArts_City_Game_City_H

#include <vector>
#include <map>
#include <numeric>
#include <iostream>
#include <fstream>
#include <sstream>

#include <Map/Map.hpp>

namespace NordicArts {
    class City {
    // Variables    
    public:
        Map                 m_oMap;

        double              m_dPopulation;
        double              m_dEmployable;
        double              m_dResidentialTax;
        double              m_dCommercialTax;
        double              m_dIndustrialTax;
        double              m_dEarnings;
        double              m_dFunds;

        int                 m_iDay;

    protected:
    private:
        float               m_fCurrentTime;
        float               m_fTimePerDay;
        float               m_fPropCanWork;

        double              m_dPopulationPool;
        double              m_dEmploymentPool;
        double              m_dBirthRate;
        double              m_dDeathRate;

        std::vector<int>    m_iShuffledTiles;

    // Methods
    public:
        City();
        City(std::string cCityName, int iTileSize, std::map<std::string, Tile> &mTiles);

        void load(std::string cCityName, std::map<std::string, Tile> &mTiles);
        void save(std::string cCityName);
        void update(float fDT);
        void bulldoze(const Tile &oTile);
        void shuffleTiles();
        void tileChanged();

        double getHomeless() const;
        double getUnemployed() const;

    protected:
    private:
        double distributePool(double &dPool, Tile &oTile, double dRate);

    };
};

#endif
