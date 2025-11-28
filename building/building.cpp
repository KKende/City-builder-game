#include "building.hpp"

Building::Building(std::string name, int cost, int sizeX, int sizeY, double hapinessEffect, int populationEffect, int moneyPerturn, int b_X, int b_Y) 
:_name(name), _cost(cost), _sizeX(sizeX), _sizeY(sizeY), _hapinessEffect(hapinessEffect), _populationEffect(populationEffect), _moneyPerturn(moneyPerturn), _b_X(b_X), _b_Y(b_Y) {};

std::string Building::GetFullName() {
    return "Building " + _name;
}

std::string Building::GetName() {
    return _name;
}

int Building::GetCost() {
    return _cost;
}

int Building::GetSizeX() {
    return _sizeX;
}

int Building::GetSizeY() {
    return _sizeY;
}

double Building::GetHapinessEffect() {
    return _hapinessEffect;
}

int Building::GetPopulationEffect() {
    return _populationEffect;
}

int Building::GetMoneyPerturn() {
    return _moneyPerturn;
}

int Building::GetCordX() {
    return _b_X;
}

int Building::GetCordY() {
    return _b_Y;
}

void Building::SetCordX(int newCord) {
    _b_X = newCord;
}

void Building::SetCordY(int newCord) {
    _b_Y = newCord;
}

void Building::SetSizeX(int newSize) {
    _sizeX = newSize;
}

void Building::SetSizeY(int newSize) {
    _sizeY = newSize;
}

void Building::GetInfo(int numberOfBuilding) {
    std::cout 
            << numberOfBuilding << "th building \n"
            << "Name : " << _name << "\n"
            << "Cost : " << _cost << "\n"
            << "Size : " << _sizeX << " X " << _sizeY << "\n"
            << "Hapiness : " << _hapinessEffect << "\n"
            << "Population : " << _populationEffect << "\n"
            << "Money per turn : " << _moneyPerturn << "\n"
            << "Cordinates : X = " << _b_X << " Y = " << _b_Y << "\n";
}

Building::~Building(){}
