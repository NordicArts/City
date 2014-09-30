#include <City/City.hpp>

namespace NordicArts {
    City::City() : m_dBirthRate(0.00055), m_dDeathRate(0.00023), m_fPropCanWork(0.50), m_dPopulationPool(0), m_dEmploymentPool(0), m_dResidentialTax(0.05), m_dCommercialTax(0.05), m_dIndustrialTax(0.05), m_dEarnings(0), m_dFunds(0), m_fCurrentTime(0.0), m_fTimePerDay(1.0), m_iDay(0) {
        m_dPopulation   = m_dPopulationPool;
        m_dEmployable   = m_dEmploymentPool;
    }

    City::City(std::string cCityName, int iTileSize, std::map<std::string, Tile> &mTiles) : City() {
        this->m_oMap.m_iTileSize = iTileSize;
        
        load(cCityName, mTiles);
    }

    double City::getHomeless() const {
        return this->m_dPopulationPool;
    }

    double City::getUnemployed() const {
        return this->m_dEmploymentPool;
    }

    double City::distributePool(double &dPool, Tile &oTile, double dRate = 0.0) {
        const static int iMoveRate = 4;

        unsigned int iMaxPop = (oTile.m_iMaxPopPerLevel * (oTile.m_iTileVariant + 1));
        
        if (dPool > 0) {
            int iMoving = (iMaxPop - oTile.m_dPopulation);
            if (iMoving > iMoveRate) {
                iMoving = iMoveRate;
            }

            if ((dPool - iMoveRate) < 0) {
                iMoving = dPool;
            }

            dPool -= iMoving;
        
            oTile.m_dPopulation += iMoving;
        }

        oTile.m_dPopulation += (oTile.m_dPopulation * dRate);
        if (oTile.m_dPopulation > iMaxPop) {
            dPool += (oTile.m_dPopulation - iMaxPop);
            
            oTile.m_dPopulation = iMaxPop;
        }

        return oTile.m_dPopulation;
    }

    void City::bulldoze(const Tile &oTile) {
        for (int iPos = 0; iPos < (this->m_oMap.m_iWidth * this->m_oMap.m_iHeight); ++iPos) {
            if (this->m_oMap.m_vSelected[iPos] == 1) {
                if (this->m_oMap.m_vTiles[iPos].m_eTileType == TileType::RESIDENTIAL) {
                    this->m_dPopulationPool += this->m_oMap.m_vTiles[iPos].m_dPopulation;
                } else if (this->m_oMap.m_vTiles[iPos].m_eTileType == TileType::COMMERCIAL) {
                    this->m_dEmploymentPool += this->m_oMap.m_vTiles[iPos].m_dPopulation;
                } else if (this->m_oMap.m_vTiles[iPos].m_eTileType == TileType::INDUSTRIAL) {
                    this->m_dEmploymentPool += this->m_oMap.m_vTiles[iPos].m_dPopulation;
                }

                this->m_oMap.m_vTiles[iPos] = oTile;
            }
        }

        return;
    }

    void City::shuffleTiles() {
        while (this->m_iShuffledTiles.size() < this->m_oMap.m_vTiles.size()) {
            this->m_iShuffledTiles.push_back(0);
        }

        std::iota(m_iShuffledTiles.begin(), m_iShuffledTiles.end(), 1);
        std::random_shuffle(m_iShuffledTiles.begin(), m_iShuffledTiles.end());
    
        return;
    }

    void City::tileChanged() {
        this->m_oMap.updateDirection(TileType::ROAD);
        this->m_oMap.findConnectedRegions({
            TileType::ROAD,
            TileType::RESIDENTIAL,
            TileType::COMMERCIAL,
            TileType::INDUSTRIAL
        }, 0);

        return;
    }

    void City::load(std::string cCityName, std::map<std::string, Tile> &mTiles) {
        int iHeight = 0;
        int iWidth = 0;

        std::string cFile = "GameFiles/" + cCityName;
        cFile + "_cfg.dat";

        std::ifstream fFile(cFile.c_str(), std::ios::in);
        
        std::string cLine;
        while (std::getline(fFile, cLine)) {
            std::istringstream cStream(cLine);
            std::string cKey;
            if (std::getline(cStream, cKey, '=')) {
                std::string cValue;
                if (std::getline(cStream, cValue)) {
                    if (cKey == "width") {
                        iWidth = std::stoi(cValue);
                    } else if (cKey == "height") {
                        iHeight = std::stoi(cValue);
                    } else if (cKey == "day") {
                        this->m_iDay = std::stoi(cValue);
                    } else if (cKey == "populationPool") {
                        this->m_dPopulationPool = std::stod(cValue);
                    } else if (cKey == "employmentPool") {
                        this->m_dEmploymentPool = std::stod(cValue);
                    } else if (cKey == "population") {
                        this->m_dPopulation = std::stod(cValue);
                    } else if (cKey == "employable") {
                        this->m_dEmployable = std::stod(cValue);
                    } else if (cKey == "birthRate") {
                        this->m_dBirthRate = std::stod(cValue);
                    } else if (cKey == "deathRate") {
                        this->m_dDeathRate = std::stod(cValue);
                    } else if (cKey == "residentialTax") {
                        this->m_dResidentialTax = std::stod(cValue);
                    } else if (cKey == "commericalTax") {
                        this->m_dCommercialTax = std::stod(cValue);
                    } else if (cKey == "industrialTax") {
                        this->m_dIndustrialTax = std::stod(cValue);
                    } else if (cKey == "funds") {
                        this->m_dFunds = std::stod(cValue);
                    } else if (cKey == "earnings") {
                        this->m_dEarnings = std::stod(cValue);
                    }
                } else {
                    std::cerr << "Error no value for key" << cKey << std::endl;
                }
            }
        }

        fFile.close();

        this->m_oMap.load("GameFiles/" + cCityName + "_map.dat", iWidth, iHeight, mTiles);

        tileChanged();

        return;
    }

    void City::save(std::string cCityName) {
        std::string cFile = "GameFiles/" + cCityName;
        cFile + "_cfg.dat";

        std::ofstream fFile(cFile.c_str(), std::ios::out);

        fFile << "width=" << this->m_oMap.m_iWidth << std::endl;
        fFile << "height=" << this->m_oMap.m_iHeight << std::endl;
        fFile << "day=" << this->m_iDay << std::endl;
        fFile << "populationPool=" << this->m_dPopulationPool << std::endl;
        fFile << "employmentPool=" << this->m_dEmploymentPool << std::endl;
        fFile << "population=" << this->m_dPopulation << std::endl;
        fFile << "employable=" << this->m_dEmployable << std::endl;
        fFile << "birthRate=" << this->m_dBirthRate << std::endl;
        fFile << "deathRate=" << this->m_dDeathRate << std::endl;
        fFile << "residentialTax=" << this->m_dResidentialTax << std::endl;
        fFile << "commercialTax=" << this->m_dCommercialTax << std::endl;
        fFile << "industrialTax=" << this->m_dIndustrialTax << std::endl;
        fFile << "funds=" << this->m_dFunds << std::endl;
        fFile << "earnings=" << this->m_dEarnings << std::endl;

        fFile.close();

        this->m_oMap.save("GameFiles/" + cCityName + "_map.dat");

        return;
    }
};
