#include "game.hpp"

Game::Game() : _turnNumber(0), _score(0), _happyness(50.0), _population(50), _money(10000) {
    for (int y = 0; y < 25; y++) {
        std::vector<Grid> row;
        for (int x = 0; x < 25; x++) {
            row.push_back(Grid(GridType::EMPTY, x, y));
        }
        _map.push_back(row);
    }
};

void Game::AddBuildings() {
    std::cout << "Current money . " << _money << std::endl;
    std::cout << "Factory(1) or House(2)? 1/2" << std::endl;
    int forh;
    std::cin >> forh;
    std::cout << "Size small(s), medium(m) or large(l)? s/m/l" << std::endl;
    std::string size;
    std::cin >> size;
    int u_x, u_y;
    std::cout << "Place the building \n"
        << "cord x ";
        std::cin >> u_x;
    std::cout << "cord y " << std::endl;
        std::cin >> u_y;
    std::cout << "Rotate? y/n" << std::endl;
    std::string user_answere;
    bool rotate;
    std::cin >> user_answere;
    if(user_answere == "y") {
        rotate = true;
    }
    else if (user_answere == "n") {
        rotate = false;
    }
    else {
        return;
    }
    Building *building;
    GridType new_gridType;
    if(forh == 1) {
        new_gridType = GridType::FACTORY;
        if (size == "s") {
            building = new Factory("small", 2000, 2, 4, -5, 0, 100, u_x, u_y);
        }
        else if (size == "m") {
            building = new Factory("medium", 5000, 4, 4, -12, 0, 250, u_x, u_y);
        }
        else {
            building = new Factory("large", 10000, 6, 8, -25, 0, 500, u_x, u_y);
        }
    }
    else {
        new_gridType = GridType::HOUSE;
        if (size == "s") {
            building = new House("small", 500, 1, 1, 2, 5, -10, u_x, u_y);
        }
        else if (size == "m") {
            building = new House("medium", 1500, 2, 2, 6, 15, -30, u_x, u_y);
        }
        else {
            building = new House("large", 3000, 2, 4, 10, 30, -60, u_x, u_y);
        }
    }
    if(rotate) {
        int temp = building->GetSizeX();
        building->SetSizeX(building->GetSizeY());
        building->SetSizeY(temp);
    }
    bool canBuild = true;
    if (u_x < 0 || u_y < 0 || u_x + building->GetSizeX() > 25 || u_y + building->GetSizeY() > 25) canBuild = false;
    for (int y = u_y; y < u_y + building->GetSizeY() && canBuild; y++) {
        if (y > 24 || y < 0) canBuild = false;
        for (int x = u_x; x < u_x + building->GetSizeX(); x++) {
            if (_map[y][x].GetType() != GridType::EMPTY) {
                canBuild = false;
                break;
            }
        }
        if (!canBuild) break;;
    }
    if (!canBuild) {
        std::cout << "Invalid placement" << std::endl;
        delete building;
        return;
    }
    if (_money >= building->GetCost()) {
        for (int y = u_y; y < u_y + building->GetSizeY() ; y++) {
            for (int x = u_x; x < u_x + building->GetSizeX(); x++) {
                _map[y][x].SetType(new_gridType);
            }
        }
    }
    else {
        std::cout << "You dont have enough money!" << std::endl;
        delete building;
        return;
    }
    this->PrintMap();
    std::cout << "Are you sure you want to place the building here? y/n" << std::endl;
    std::string user_answere2;
    std::cin >> user_answere2;
    if(user_answere2 == "y") {
        _money -= building->GetCost();
        buildings.push_back(building);
        _population += building->GetPopulationEffect();
        std::cout << "Building has been placed." << std::endl;
    }
    else {
        for (int y = u_y; y < u_y + building->GetSizeY() ; y++) {
            for (int x = u_x; x < u_x + building->GetSizeX(); x++) {
                _map[y][x].SetType(GridType::EMPTY);
            }
        }
        std::cout << "Building has been canceled." << std::endl;
        delete building;
    }
}

void Game::DestroyBuilding() {
    this->PrintBuildings();
    std::cout << "Select the building number to destroy" << std::endl;
    int userChoice;
    std::cin >> userChoice;
    if (userChoice < 0 || userChoice >= buildings.size()) return;
    for (int y = buildings[userChoice]->GetCordY(); y < buildings[userChoice]->GetCordY() + buildings[userChoice]->GetSizeY(); y++) {
        for (int x = buildings[userChoice]->GetCordX(); x < buildings[userChoice]->GetCordX() + buildings[userChoice]->GetSizeX(); x++) {
            _map[y][x].SetType(GridType::EMPTY);
        }
    }
    _money = _money + (buildings[userChoice]->GetCost() /2);
    delete buildings[userChoice];
    buildings.erase(buildings.begin() + userChoice);
}

void Game::PrintBuildings() {
    for (int i = 0; i < buildings.size() ; i++) {
        buildings[i]->GetInfo(i);
        std::cout << std::endl;
    }
}

void Game::DisplayScore() {
    _score = (_turnNumber * 10) + (_money * 0.5) + (_happyness * 20) + (_population * 5);
    std::cout 
        << "Turn number : " << _turnNumber << "\n"
        << "Score :" << _score << "\n"
        << "Happyness :" << _happyness << "\n"
        << "Money :" << _money << "\n" 
        << "Population :" << _population << std::endl;
}

void Game::PrintMap() {
    for (int y = 0; y < 25; y++) {
        for (int x = 0; x < 25; x++) {
            std::cout << _map[y][x].GetTypeToString() << " ";
        }
        std::cout << std::endl;
    }
}

bool Game::EndTurn() {
    _turnNumber ++;
    for (int i = 0; i < buildings.size(); i++) {
        _happyness += buildings[i]->GetHapinessEffect();
        _money += buildings[i]->GetMoneyPerturn();
    }
    if (_happyness <= 0) {
        return false;
    }
    else if(_happyness > 100) {
        _happyness = 100;
    }
    this->DisplayScore();
    std::cout << std::endl;
    return true;
}   

void Game::SaveGame() {
    std::cout << "Enter a file name!" << std::endl;
    std::string filename;
    std::cin >> filename;
    _saveFile.open(filename + ".txt", std::ios::out);
    if(!_saveFile.is_open()) {
        std::cout << "Save file write unsuccesful" << std::endl;
        return;
    }
    _saveFile << _turnNumber << "\n";
    _saveFile << _score << "\n";
    _saveFile << _happyness << "\n";
    _saveFile << _population << "\n";
    _saveFile << _money << "\n";
    for(int i = 0; i < buildings.size() ; i++) {
        _saveFile << buildings[i]->GetFullName() << " "
        << buildings[i]->GetSizeX() << " "
        << buildings[i]->GetSizeY() << " "
        << buildings[i]->GetCordX() << " "
        << buildings[i]->GetCordY() << "\n";
    }
    _saveFile.close();
    std::cout << "Save was successfull" << std::endl;
}

void Game::LoadGame() {
    std::cout << "Give the save file's name" << std::endl;
    std::string saveFileName;
    std::cin >> saveFileName;
    std::string line;
    _saveFile.open(saveFileName + ".txt", std::ios::in);
    if(!_saveFile.is_open()) {
        std::cout << "Save open has failed" << std::endl;
        return;
    }
    std::getline(_saveFile, line);
    _turnNumber = std::stoi(line);
    std::getline(_saveFile, line);
    _score = std::stoi(line);
    std::getline(_saveFile, line);
    _happyness = std::stoi(line);
    std::getline(_saveFile, line);
    _population = std::stoi(line);
    std::getline(_saveFile, line);
    _money = std::stoi(line);
    for(int i = 0; i < buildings.size(); i ++) {
        delete buildings[i];
    }
    buildings.clear();
    for (int y = 0; y < 25; y++)
        for (int x = 0; x < 25; x++)
            _map[y][x].SetType(GridType::EMPTY);
    while (std::getline(_saveFile, line)) {
        Building *building;
        GridType new_gridType;
        std::string type;
        std::string size;
        int sizeX;
        int sizeY;
        int cordX;
        int cordY;
        bool rotation;
        std::istringstream stream(line);

        stream >> type >> size >> sizeX >> sizeY>> cordX >> cordY;

        if(type == "Factory") {
            new_gridType = GridType::FACTORY;
            if (size == "small") {
                building = new Factory("small", 2000, sizeX, sizeY, -5, 0, 100, cordX, cordY);
            }
            else if (size == "medium") {
                building = new Factory("medium", 5000, sizeX, sizeY, -12, 0, 250, cordX, cordY);
            }
            else {
                building = new Factory("large", 10000, sizeX, sizeY, -25, 0, 500, cordX, cordY);
            }
        }
        else {
            new_gridType = GridType::HOUSE;
            if (size == "small") {
                building = new House("small", 500, sizeX, sizeY, 2, 5, -10, cordX, cordY);
            }
            else if (size == "medium") {
                building = new House("medium", 1500, sizeX, sizeY, 6, 15, -30, cordX, cordY);
            }
            else {
                building = new House("large", 3000, sizeX, sizeY, 10, 30, -60, cordX, cordY);
            }
        }
        for (int y = cordY; y < cordY + building->GetSizeY() ; y++) {
            for (int x = cordX; x < cordX + building->GetSizeX(); x++) {
                _map[y][x].SetType(new_gridType);
            }
        }
        buildings.push_back(building);
    }
    _saveFile.close();
    std::cout << "Load was succesfull" << std::endl;
}

void Game::Menu() {
    bool exit = false;
    while (!exit) {
        std::cout 
            << std::endl
            << "____________MENU____________ \n"
            << "Add building : " << MenuPoints::ADD_BUILDING << "\n"
            << "Destroy building : " << MenuPoints::DESTROY_BUILDING << "\n"
            << "Print buildings : " << MenuPoints::PRINT_BUILDINGS << "\n"
            << "Display Score : " << MenuPoints::DISPLAY_SCORE << "\n"
            << "Print Map : " << MenuPoints::PRINTMAP << "\n"
            << "End Turn : " << MenuPoints::ENDTURN << "\n"
            << "Save game :" << MenuPoints::SAVE << "\n"
            << "Load game :" << MenuPoints::LOAD << "\n"
            << "Exit : " << MenuPoints::EXIT << std::endl;
            int userChoice;
            std::cin >> userChoice;
        switch (userChoice) {
            case MenuPoints::ADD_BUILDING :
                system("cls");
                this->AddBuildings();
                break;
            case MenuPoints::DESTROY_BUILDING :
                system("cls");
                this->DestroyBuilding();
                break;
            case MenuPoints::PRINT_BUILDINGS :
                system("cls");
                this->PrintBuildings();
                break;
            case MenuPoints::DISPLAY_SCORE :
                system("cls");
                this->DisplayScore();
                break;
            case MenuPoints::PRINTMAP :
                system("cls");
                this->PrintMap();
                break;
            case MenuPoints::ENDTURN :
                system("cls");
                exit = !this->EndTurn();
                break;
            case MenuPoints::SAVE :
                this->SaveGame();
                break;
            case MenuPoints::LOAD :
                this->LoadGame();
                break;
            case MenuPoints::EXIT :
                exit = true;
                break;
        }
    }
}