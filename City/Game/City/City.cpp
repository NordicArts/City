#include <City/City.hpp>

namespace NordicArts {
    City::City() : m_dBirthRate(0.00055), m_dDeathRate(0.00023), m_fPropCanWork(0.50), m_dPopulationPool(0), m_dEmploymentPool(0), m_dResidentialTax(0.05), m_dCommercialTax(0.05), m_dIndustrialTax(0.05), m_dEarnings(0), m_dFunds(0), m_fCurrentTime(0.0), m_fTimePerDay(1.0), m_iDay(0) {
        m_dPopulation   = m_dPopulationPool;
        m_dEmployable   = m_dEmploymentPool;
    }

    City::City(std::string cCityName, int iTileSize, std::map<std::string, Tile> &mTiles) : City() {
        this->m_oMap.setTileSize(iTileSize);
        
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
        for (int iPos = 0; iPos < (this->m_oMap.getWidth() * this->m_oMap.getHeight()); ++iPos) {
            if (this->m_oMap.m_vSelected[iPos] == 1) {
                if (this->m_oMap.m_vTiles[iPos].getTileType() == TileType::RESIDENTIAL) {
                    this->m_dPopulationPool += this->m_oMap.m_vTiles[iPos].m_dPopulation;
                } else if (this->m_oMap.m_vTiles[iPos].getTileType() == TileType::COMMERCIAL) {
                    this->m_dEmploymentPool += this->m_oMap.m_vTiles[iPos].m_dPopulation;
                } else if (this->m_oMap.m_vTiles[iPos].getTileType() == TileType::INDUSTRIAL) {
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

        fFile << "width=" << this->m_oMap.getWidth() << std::endl;
        fFile << "height=" << this->m_oMap.getHeight() << std::endl;
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

    void City::update(float fDT) {
        double dPopTotal            = 0;
        double dCommercialRevenue   = 0;
        double dIndustrialRevenue   = 0;

        this->m_fCurrentTime += fDT;
        if (this->m_fCurrentTime < this->m_fTimePerDay) {
            return;
        }
        ++m_iDay;
        this->m_fCurrentTime = 0.0;
        
        if ((m_iDay % 30) == 0) {
            this->m_dFunds += this->m_dEarnings;

            this->m_dEarnings = 0;
        }

        for (int i = 0; i < this->m_oMap.m_vTiles.size(); ++i) {
            Tile &oTile = this->m_oMap.m_vTiles[this->m_iShuffledTiles[i]];
            if (oTile.getTileType() == TileType::RESIDENTIAL) {
                this->distributePool(this->m_dPopulationPool, oTile, (this->m_dBirthRate - m_dDeathRate));

                dPopTotal += oTile.m_dPopulation;
            } else if (oTile.getTileType() == TileType::COMMERCIAL) {
                if ((rand() % 100) <  (15 * (1.0 - this->m_dCommercialTax))) {
                    this->distributePool(this->m_dEmploymentPool, oTile, 0.00);
                }
            } else if (oTile.getTileType() == TileType::INDUSTRIAL) {
                if ((this->m_oMap.m_vResources[i] > 0) && ((rand() % 100) < this->m_dPopulation)) {
                    ++oTile.m_fProduction;

                    --this->m_oMap.m_vResources[i];
                }

                if ((rand() % 100) < (15 * (1.0 - this->m_dIndustrialTax))) {
                    this->distributePool(this->m_dEmploymentPool, oTile, 0.0);
                }
            }

            oTile.update();
        }

        for (int i = 0; i < this->m_oMap.m_vTiles.size(); ++i) {
            Tile &oTile = this->m_oMap.m_vTiles[this->m_iShuffledTiles[i]];
            if (oTile.getTileType() == TileType::INDUSTRIAL) {
                int iReceivedResources = 0;
                for (auto &oTiles : this->m_oMap.m_vTiles) {
                    if ((oTiles.m_iRegions[0] == oTile.m_iRegions[0]) && (oTiles.getTileType() == TileType::INDUSTRIAL)) {
                        if (oTiles.m_fProduction > 0) {
                            ++iReceivedResources;
                
                            --oTiles.m_fProduction;
                        }

                        if (iReceivedResources >= (oTile.m_iTileVariant + 1)) {
                            break;
                        }
                    }
                }

                oTile.m_fStoredGoods += ((iReceivedResources + oTile.m_fProduction) * (oTile.m_iTileVariant + 1));
            }
        }

        for (int i = 0; i < this->m_oMap.m_vTiles.size(); ++i) {
            Tile &oTile = this->m_oMap.m_vTiles[this->m_iShuffledTiles[i]];
            if (oTile.getTileType() == TileType::COMMERCIAL) {
                int iRecievedGoods = 0;
                double dMaxCustomers = 0.0;
                
                for (auto &oTiles : this->m_oMap.m_vTiles) {
                    if ((oTiles.m_iRegions[0] == oTile.m_iRegions[0]) && (oTiles.getTileType() == TileType::INDUSTRIAL) && (oTiles.m_fStoredGoods > 0)) {
                        while ((oTiles.m_fStoredGoods > 0) && (iRecievedGoods != (oTile.m_iTileVariant + 1))) {
                            --oTiles.m_fStoredGoods;
                        
                            ++iRecievedGoods;
        
                            dIndustrialRevenue += (100 * (1.0 - m_dIndustrialTax));
                        }
                    } else if ((oTiles.m_iRegions[0] == oTile.m_iRegions[0]) && (oTiles.getTileType() == TileType::RESIDENTIAL)) {
                        dMaxCustomers += oTiles.m_dPopulation;
                    }

                    if (iRecievedGoods == (oTile.m_iTileVariant + 1)) {
                        break;
                    }
                }

                oTile.m_fProduction = (((iRecievedGoods * dMaxCustomers) + (rand() % 20)) * (1.0 - this->m_dCommercialTax));

                double dRevenue = ((oTile.m_fProduction * dMaxCustomers * oTile.m_dPopulation) / 100.0);
                dCommercialRevenue += dRevenue;
            }
        }

        this->m_dPopulationPool += (this->m_dPopulationPool * (this->m_dBirthRate - this->m_dDeathRate));
        dPopTotal += this->m_dPopulationPool;

        float fNewWorkers = ((dPopTotal - this->m_dPopulationPool) * this->m_fPropCanWork);
        fNewWorkers *= ((fNewWorkers < 0) ? -1 : 1);
        this->m_dEmploymentPool += fNewWorkers;
        this->m_dEmployable += fNewWorkers;
        if (this->m_dEmploymentPool < 0) { 
            this->m_dEmploymentPool = 0;
        }
        if (this->m_dEmployable < 0) {
            this->m_dEmployable = 0;
        }

        this->m_dPopulation = dPopTotal;

        this->m_dEarnings = ((this->m_dPopulation - this->m_dPopulationPool) * 15 * this->m_dResidentialTax);
        this->m_dEarnings += (dCommercialRevenue * this->m_dCommercialTax);
        this->m_dEarnings += (dIndustrialRevenue * this->m_dIndustrialTax);

        return;
    }
};
