#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "building/house/house.hpp"
#include "building/factory/factory.hpp"
#include "grid/grid.hpp"

enum MenuPoints {
    ADD_BUILDING,
    DESTROY_BUILDING,
    PRINT_BUILDINGS,
    DISPLAY_SCORE,
    PRINTMAP,
    ENDTURN,
    SAVE,
    LOAD,
    EXIT
};

class Game {
    int _turnNumber;
    int _score;
    double _happyness;
    int _population;
    int _money;

    std::vector<Building*> buildings;
    std::vector<std::vector<Grid>> _map;
    std::fstream _saveFile;

public:
    Game();

    void Menu();
    void SaveGame();
    void LoadGame();
    void DestroyBuilding();
    void AddBuildings();
    void PrintBuildings();
    void PrintMap();
    void DisplayScore();
    bool EndTurn();
};