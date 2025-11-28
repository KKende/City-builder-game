#include "factory.hpp"

Factory::Factory(std::string name, int cost, int sizeX, int sizeY, double hapinessEffect, int populationEffect, int moneyPerturn, int b_X, int b_Y) 
:Building(name, cost, sizeX, sizeY, hapinessEffect, populationEffect, moneyPerturn, b_X, b_Y) {};

std::string Factory::GetFullName() {
    return "Factory " + GetName();
}

void Factory::GetInfo(int numberOfBuilding) {
    std::cout
    << numberOfBuilding << " building number \n"
    << "Name : Factory " << GetName() << "\n"
    << "Cost : " << GetCost() << "\n"
    << "Size : " << GetSizeX() << " X " << GetSizeY() << "\n"
    << "Hapiness : " << GetHapinessEffect() << "\n"
    << "Population : " << GetPopulationEffect() << "\n"
    << "Money per turn : " << GetMoneyPerturn() << "\n"
    << "Cordinates : X = " << GetCordX() << " Y = " << GetCordY() << std::endl;
}