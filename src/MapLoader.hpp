/////////////////////////////////////////////
// Filename:        MapLoader.h
//
// Description:     Header file for MapLoader.cpp
//
// Author:          Stefan Russo - 26683320
//
// Group:           Sandra Buchen
//                  Le Cherng Lee
//                  Zahra Nikbakht
//                  Matthew Pan
//                  Stefan Russo
//
/////////////////////////////////////////////

#pragma once

#include <string>
#include <vector>
#include "Map.h"


class MapFileTerritory;

class Continent;

class MapFile;

// Class: Continent
//
// Contains the data for each continent
class Continent {
   public:
    int number;
    std::string name;
    int value;
    std::string colour;
    int number_of_territories;
    static int count;

    // Constructors
    Continent();

    Continent(std::string new_name, int new_value, std::string new_colour);

    Continent(const Continent &other_continent);

    // Assignment Operator
    Continent &operator=(const Continent &other_continent);

    // Stream Insertion
    friend std::ostream &operator<<(std::ostream &output,
                                    const Continent &continent);

    // Destructor
    ~Continent();
};

std::ostream &operator<<(std::ostream &output, const Continent &continent);

class MapFileTerritory {
   public:
    int number;
    std::string short_name;
    int continent_number;
    int x_coord;
    int y_coord;
    std::vector<int> borders;

    static int count;

    // Constructors
    MapFileTerritory();

    MapFileTerritory(int new_number, std::string new_short_name,
                     int new_continent_number, int new_x_coord,
                     int new_y_coord);

    MapFileTerritory(const MapFileTerritory &other_territory);

    // Assignment Operator
    MapFileTerritory &operator=(const MapFileTerritory &other_territory);

    // Stream Insertion
    friend std::ostream &operator<<(std::ostream &output,
                                    const MapFileTerritory &territory);

    ~MapFileTerritory();
};

std::ostream &operator<<(std::ostream &output,
                         const MapFileTerritory &territory);

// Struct that can be passed as a parameter, to obtain the success or failure of
// an operation, outside of the return value of the function
template <typename T>
struct Result {
    T *returnValue;
    bool success;
    std::string message;

    Result<T>(){};
    Result<T>(T *newReturnvalue, bool newSuccess, std::string newMessage)
        : returnValue(newReturnvalue),
          success(newSuccess),
          message(newMessage) {};

    // // ~Result<Void>(){};
    // ~Result<T>() {
    //     if (returnValue) delete returnValue;
    //     returnValue = nullptr;
    // }
};

// Class: MapFile
//
// Contains the filename of the map to be loaded, and the data contained within
// the map file.
//
class MapFile {
   public:
    std::string map_file_name;
    std::string pic_file_name;
    std::string map_pic_file_name;
    std::string cards_file_name;
    std::string prv_file_name;
    std::vector<Continent *> map_continents;
    std::vector<MapFileTerritory *> map_territories;

    // Constructors
    MapFile();

    MapFile(std::string new_map_file_name);

    MapFile(const MapFile &other_map_file);

    MapFile &operator=(const MapFile &other_map_file);

    friend std::ostream &operator<<(std::ostream &output,
                                    const MapFile *map_file);

    // void readMapFile();
    Result<void> readMapFile();

    Result<void> processFileSectionLine(const std::string line);
    Result<void> processContinentSectionLine(const std::string line);
    Result<void> processTerritorySectionLine(const std::string line);
    Result<void> processBordersSectionLine(const std::string line);
    Result<MapFileTerritory> getTerritoryByNumber(int territory_number);
    Result<Continent> getContinentByNumber(int continent_number);

    bool isValidTerritoryNumber(int territory_number);
    bool isValidContinentNumber(int continent_number);

    Map generateMap();
    // Result<void> generateMap();

    Result<void> validate();

    ~MapFile();
};

std::string toLowerCase(const std::string toLower);

//////////////////
// Source:
// https://www.toptip.ca/2010/03/trim-leading-or-trailing-white-spaces.html
void trim(std::string &s);
/////////////////

// Returns a bool after checking each char for a space character
bool isStringBlank(const std::string line);

// Source: https://thispointer.com/how-to-split-a-string-in-c/
std::vector<std::string> split(std::string strToSplit, char delimiter);

std::ostream &operator<<(std::ostream &output, const MapFile *map_file);
