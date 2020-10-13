/////////////////////////////////////////////
// Filename:        Map.h
//
// Description:     Header file for Implementation of Part 1 - Map
//
// Author:          Le Cherng Lee
//
// Group:           Sandra Buchen
//                  Le Cherng Lee
//                  Zahra Nikbakht
//                  Matthew Pan
//                  Stefan Russo - 26683320
//
/////////////////////////////////////////////

#pragma once
#include <string>
#include <vector>


#include "Player.h"
//this macro will only print when in debug mode :3
#ifdef _DEBUG
#define Log(x) std::cout << x << std::endl;
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define FindMemoryLeak()_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define FindMemoryLeak();
#define Log(x)
#endif

#ifndef H_PLAYER
#define H_PLAYER
class Player;
#endif
// country only need name, a unique ID and a continent
// is a struct and not a class, so do what you need to do :)
struct Territory {
 public:
  std::string Name;
  int TerritoryID;
  std::string Continent;
  float XCoordinate;
  float YCoordinate;
  std::string OwnedBy;
  int Armies;

  bool operator==(Territory &Territory) const;

  Territory();
  Territory(std::string name, int territoryID, std::string continent, float x,
            float y);
  Territory(const Territory &t);
  friend std::ostream &operator<<(std::ostream &out, const Territory &t);
  Territory &operator=(const Territory &t);
};

struct ContinentData {
  std::string Name;
  int ContinentID;
  int NumberOfTerritories;
  std::string Colour;
  static int Count;

  bool operator==(ContinentData &ContinentData) const {
    return this->ContinentID == ContinentData.ContinentID;
  }
};

class Map {
  std::string *MapName;
  std::vector<Territory *> **ListOfCountries;
  int *NumberOfCountries;

  std::vector<Territory *> AllCountries;

 public:
  // minimal Constructor
  Map();

  // another minimal constructor
  Map(int size, std::string mapName);
  // full constructor
  Map(std::vector<struct ::Territory *> **listOfCountries, std::string mapName,
      int size, Map &continent);
  // partial constructor when the country doesn't have other maps
  Map(std::vector<struct ::Territory *> **listOfCountries, std::string mapName,
      int size);

  Map(Map &Copy);

  ~Map();

  void AddEdges(Territory &country1, Territory &country2);

  std::vector<struct ::Territory *> ReturnListOfCountries();

  int NumOfCountries();
  void Display();
  void Display(std::string continent);
  void SetMapName(std::string mapName);

  bool Validate();
  void DFS(int x, bool **visited);

  friend std::ostream& operator<<(std::ostream& out, const Map& map);
  
  Map& operator=(const Map* map);
};
