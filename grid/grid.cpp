#include "grid.hpp"

Grid::Grid(GridType type, int x, int y) : _type(type), _x(x), _y(y) {};

GridType Grid::GetType() {
    return this->_type;
}

std::string Grid::GetTypeToString() {
    switch (this->_type) {
        case GridType::HOUSE :
            return "HH";
        case GridType::FACTORY :
            return "FF";
        case GridType::EMPTY :
            return "..";
        default : return "..";
    }
}

int Grid::GetX() {
    return this->_x;
}

int Grid::GetY() {
    return this->_y;
}

void Grid::SetType(GridType type) {
    this->_type = type;
}