#pragma once
#include "building/building.hpp"

class Factory : public Building {
public:
    Factory(std::string name, int cost, int sizeX, int sizeY, double hapinessEffect, int populationEffect, int moneyPerturn, int b_X, int b_Y);
    void GetInfo(int numberOfBuilding) override;
    std::string GetFullName() override;
};