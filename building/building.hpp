#pragma once

#include <iostream>

class Building {
    std::string _name;
    int _cost;
    int _sizeX;
    int _sizeY;
    double _hapinessEffect;
    int _populationEffect;
    int _moneyPerturn;
    int _b_X;
    int _b_Y;

public:
    Building(std::string name, int cost, int sizeX, int sizeY, double hapinessEffect, int populationEffect, int moneyPerturn, int b_X, int b_Y);
    
    virtual std::string GetFullName();
    std::string GetName();
    int GetCost();
    int GetSizeX();
    int GetSizeY();
    double GetHapinessEffect();
    int GetPopulationEffect();
    int GetMoneyPerturn();
    int GetCordX();
    int GetCordY();

    void SetCordX(int newCord);
    void SetCordY(int newCord);

    void SetSizeX(int newSize);
    void SetSizeY(int newSize);


    virtual void GetInfo(int numberOfBuilding);

    ~Building();
};