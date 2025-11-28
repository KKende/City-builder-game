#pragma once
#include <iostream>

enum GridType{
    HOUSE,
    FACTORY,
    EMPTY
};

class Grid {
    int _x;
    int _y;
    GridType _type;

public:
    Grid(GridType type, int x, int y);

    GridType GetType();
    std::string GetTypeToString();
    int GetX();
    int GetY();
    
    void SetType(GridType type);

};