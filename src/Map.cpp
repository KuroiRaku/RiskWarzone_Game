/////////////////////////////////////////////
// Filename:        Map.cpp
//
// Description:     Implementation of Part 1 - Map
//
// Author:          Le Cherng Lee - 40122814
//
// Group:           Sandra Buchen - 26317987
//                  Le Cherng Lee - 40122814
//                  Zahra Nikbakht - 40138253
//                  Matthew Pan - 40135588
//                  Stefan Russo - 26683320
//
/////////////////////////////////////////////

#include "Map.h"

#include <algorithm>
#include <iostream>

#include "Player.h"

Territory::Territory() {
  this->Name = "default";
  this->TerritoryID = 999;
  this->Continent = "";
  this->XCoordinate = 0;
  this->YCoordinate = 0;
  this->PlayerOwned = nullptr;
  this->OwnedBy = "uninitializedT";
}

Territory::Territory(std::string name, int territoryID, std::string continent,
                     float x, float y) {
  this->Name = name;
  this->TerritoryID = territoryID;
  this->Continent = continent;
  this->XCoordinate = x;
  this->YCoordinate = y;
  this->PlayerOwned = nullptr;
  this->OwnedBy = "uninitializedT";
}

Territory::Territory(std::string name, int territoryID, std::string continent,
                     float x, float y, Player* playerOwned) {
  this->Name = name;
  this->TerritoryID = territoryID;
  this->Continent = continent;
  this->XCoordinate = x;
  this->YCoordinate = y;
  this->PlayerOwned = playerOwned;
  if (playerOwned != nullptr) {
    this->OwnedBy = playerOwned->PID;
  } else {
    this->OwnedBy = "uninitializedT";
  }
}

bool Territory::operator==(Territory& Territory) const {
  return this->TerritoryID == Territory.TerritoryID;
}

Territory::Territory(const Territory& t) {
  this->Name = t.Name;
  this->TerritoryID = t.TerritoryID;
  this->Continent = t.Continent;
  this->XCoordinate = t.XCoordinate;
  this->YCoordinate = t.YCoordinate;
  // we want to refer to the same player address not a new one
  this->PlayerOwned = t.PlayerOwned;
  this->OwnedBy = t.OwnedBy;
}

Territory& Territory::operator=(const Territory& t) {
  this->Name = t.Name;
  this->TerritoryID = t.TerritoryID;
  this->Continent = t.Continent;
  this->XCoordinate = t.XCoordinate;
  this->YCoordinate = t.YCoordinate;
  // we want to refer to the same player address not a new one
  this->PlayerOwned = t.PlayerOwned;
  this->OwnedBy = t.OwnedBy;
  return *this;
}

Territory::~Territory() { this->PlayerOwned = nullptr; }

//////////////////////
// ContinentData Class
//////////////////////

ContinentData::ContinentData() {
  this->Name = "default";
  this->ContinentID = 0;
  this->NumberOfTerritories = 0;
  this->BonusValue = 0;
}

ContinentData::ContinentData(std::string name, int continentID,
                             int numberOfTerritories, int bonusValue) {
  this->Name = name;
  this->ContinentID = continentID;
  this->NumberOfTerritories = numberOfTerritories;
  this->BonusValue = bonusValue;
}

ContinentData::ContinentData(const ContinentData& c) {
  this->Name = c.Name;
  this->ContinentID = c.ContinentID;
  this->NumberOfTerritories = c.NumberOfTerritories;
  this->BonusValue = c.BonusValue;
}

ContinentData& ContinentData::operator=(const ContinentData& c) {
  this->Name = c.Name;
  this->ContinentID = c.ContinentID;
  this->NumberOfTerritories = c.NumberOfTerritories;
  this->BonusValue = c.BonusValue;
  return *this;
}

std::ostream& operator<<(std::ostream& out, const ContinentData& c) {
  out << "\tName: " << c.Name << "\n";
  out << "\tID: " << c.ContinentID << "\n";
  out << "\tNumber of Territories: " << c.NumberOfTerritories << "\n";
  out << "\tBonus Value: " << c.BonusValue << "\n";
  return out;
}

std::ostream& operator<<(std::ostream& out, const Territory& t) {
  out << "\tName: " << t.Name << "\n";
  out << "\tID: " << t.TerritoryID << "\n";
  out << "\tContinent: " << t.Continent << "\n";
  out << "\tOwnedBy: " << t.OwnedBy << "\n";
  out << "\tArmies: " << t.Armies << "\n";
  return out;
}

std::ostream& operator<<(std::ostream& out, const Map& map) {
  std::cout << "\n\nMap Name: " << map.MapName << std::endl;

  for (int i = 0; i < *map.NumberOfCountries; i++) {
    int j = 0;

    for (Territory* country : *(map.ListOfCountries[i])) {
      if (j == 0) {
        std::cout << "Territory: " << i << std::endl;
        std::cout << "Name: " << country->Name << std::endl;
        std::cout << "Adjacent Countries " << std::endl;
        j++;
      } else {
        std::cout << "-> ";
        std::cout << "Country ID: " << country->TerritoryID << " ";
        std::cout << country->Name << "\n";
        j++;
      }
    }
    j = 0;
    std::cout << std::endl;
  }
  return out;
}

Map::Map() {
  // Log("Default Constructor" << std::endl);
  NumberOfCountries = new int(0);
  ListOfCountries = new std::vector<struct ::Territory*>*[1000];
  for (int i = 0; i < 1000; i++)
    ListOfCountries[i] = new std::vector<struct ::Territory*>;

  MapName = new std::string("World Default");
}

// size defining the size of the map, name defining the map of the name
Map::Map(int size, std::string name) {
  NumberOfCountries = new int(size);

  ListOfCountries = new std::vector<Territory*>*[1000];
  for (int i = 0; i < 1000; i++)
    ListOfCountries[i] = new std::vector<struct ::Territory*>;

  MapName = new std::string(name);
}

// other constructors that other programmers could work with :)
Map::Map(std::vector<struct ::Territory*>** listOfCountries,
         std::string mapName, int size, Map& continent) {
  NumberOfCountries = new int(size);
  ListOfCountries = listOfCountries;
  MapName = new std::string(mapName);
}

Map::Map(std::vector<struct ::Territory*>** listOfCountries,
         std::string mapName, int size) {
  NumberOfCountries = new int(size);
  ListOfCountries = listOfCountries;
  MapName = new std::string(mapName);
}

// copy constructor
// iterate each of the countries and create a copy of it
Map::Map(Map& Copy) {
  MapName = new std::string(*Copy.MapName);
  ListOfCountries = new std::vector<Territory*>*[1000];

  for (int i = 0; i < 1000; i++)
    ListOfCountries[i] = new std::vector<struct ::Territory*>;

  if (!(**Copy.ListOfCountries).empty()) {
    for (int i = 0; i < *Copy.NumberOfCountries; i++) {
      for (Territory* country : *Copy.ListOfCountries[i]) {
        // calling copy constructor of each Territory
        ListOfCountries[i]->push_back(country);
      }
    }
  }
  // Log("Copied successful\n");

  NumberOfCountries = new int(*Copy.NumberOfCountries);
}

Map::~Map() {
  for (int i = 0; i < 1000; i++) {
    // Log("Deleting! : " << i);
    ListOfCountries[i]->clear();
    delete ListOfCountries[i];
    ListOfCountries[i] = nullptr;
  }

  delete[] ListOfCountries;

  for (auto i = 0; i < AllContinents.size(); i++) {
    delete AllContinents[i];
    AllContinents[i] = nullptr;
  }

  //  AllContinents.clear();

  for (auto* countries : AllCountries) {
    delete countries;
  }

  delete NumberOfCountries;
  NumberOfCountries = nullptr;
  delete MapName;
  MapName = nullptr;
}

void Map::AddEdges(Territory& country1, Territory& country2) {
  // Log("Passed by Add Edges\n");

  // When the Array still doesn't have the country yet, it will automatically
  // add a new country
  if (this->ListOfCountries[country1.TerritoryID]->size() == 0) {
    // Log("Added" << country1.Name);
    this->ListOfCountries[country1.TerritoryID]->push_back(&country1);
    this->AllCountries.push_back(&country1);
  }

  if (this->ListOfCountries[country2.TerritoryID]->size() == 0) {
    // Log("Added" << country2.Name);
    this->ListOfCountries[country2.TerritoryID]->push_back(&country2);
    this->AllCountries.push_back(&country2);
  }

  // error handling
  // if list of country1 contains country2
  int first = 0;
  for (Territory* country : *(ListOfCountries[country1.TerritoryID])) {
    // Log("Error Handling" << country->Name);
    if (*country == country2) return;
  }

  this->ListOfCountries[country2.TerritoryID]->push_back(&country1);
  this->ListOfCountries[country1.TerritoryID]->push_back(&country2);
}

void Map::AddContinent(ContinentData* new_continent) {
  ContinentData* newContinent = new ContinentData(*new_continent);
  this->AllContinents.push_back(newContinent);
}

// Returns the list of all continents
std::vector<struct ::ContinentData*> Map::getListOfContinents() {
  return this->AllContinents;
}

// iterate through the array and return the country at first index which is
// unique according to the ID same method will be same for every other method
// that return countries by ID or player name etc
std::vector<struct ::Territory*> Map::ReturnListOfCountries() {
  std::vector<Territory*> Temp;
  for (int i = 0; i < *NumberOfCountries; i++) {
    Temp.push_back(ListOfCountries[i]->at(0));
  }

  return Temp;
}

std::vector<struct ::Territory*> Map::DebugListOfUnitializedTerritories() {
  std::vector<Territory*> Temp;
  for (int i = 0; i < *NumberOfCountries; i++) {
    if (ListOfCountries[i]->at(0)->PlayerOwned == nullptr ||
        ListOfCountries[i]->at(0)->OwnedBy == "UnitializedT") {
      Temp.push_back(ListOfCountries[i]->at(0));
      // Log("This country "<< ListOfCountries[i]->at(0)->Name <<"Owned by
      // player "<< PlayerName<< std::endl);
    }
  }
  return Temp;
}

std::vector<struct ::Territory*> Map::ReturnListOfAdjacentCountriesByID(
    int ID) {
  std::vector<Territory*> ReturnList;
  for (Territory* Temp : *ListOfCountries[ID]) {
    ReturnList.push_back(Temp);
    // Log(Temp->Name << std::endl);
  }
  return ReturnList;
}

std::vector<struct ::Territory*>
Map::ReturnListOfAdjacentCountriesByIDAndPlayer(int TID,
                                                std::string PlayerName) {
  std::vector<Territory*> ReturnList;
  for (Territory* Temp : *ListOfCountries[TID]) {
    if (Temp->OwnedBy == PlayerName) {
      ReturnList.push_back(Temp);
    }
  }
  return ReturnList;
}

//this one does not return the territory itself
std::vector<struct ::Territory*> Map::ReturnListOfAdjacentCountriesByIDAndByPlayer(int TID,
    std::string PlayerName) {
    std::vector<Territory*> ReturnList;
    for (Territory* Temp : *ListOfCountries[TID]) {
        if (Temp->OwnedBy == PlayerName && Temp->TerritoryID != TID) {
            ReturnList.push_back(Temp);
        }
    }
    return ReturnList;
}

std::vector<struct ::Territory*>
Map::ReturnListOfAdjacentCountriesByIDAndNotPlayer(int TID,
                                                std::string PlayerName) {
  std::vector<Territory*> ReturnList;
  for (Territory* Temp : *ListOfCountries[TID]) {
    if (Temp->OwnedBy != PlayerName) {
      ReturnList.push_back(Temp);
    }
  }
  return ReturnList;
}

std::vector<struct ::Territory*> Map::ReturnListOfCountriesOwnedByPlayer(
    std::string PlayerName) {
  std::vector<Territory*> Temp;
  for (int i = 0; i < *NumberOfCountries; i++) {
    if (ListOfCountries[i]->at(0)->OwnedBy == PlayerName) {
      Temp.push_back(ListOfCountries[i]->at(0));
      // Log("This country "<< ListOfCountries[i]->at(0)->Name <<"Owned by
      // player "<< PlayerName<< std::endl);
    }
  }
  return Temp;
}

std::vector<struct ::Territory*> Map::ReturnListOfCountriesByContinent(
    std::string ContinentName) {
  std::vector<Territory*> Temp;
  for (int i = 0; i < *NumberOfCountries; i++) {
    if (ListOfCountries[i]->at(0)->Continent == ContinentName) {
      Temp.push_back(ListOfCountries[i]->at(0));
      // Log("This country " << ListOfCountries[i]->at(0)->Name << "Is in
      // continent" << ContinentName << std::endl);
    }
  }
  return Temp;
}

// method to check whether the player own continent
// there's one possibility to break the code, if the parameter ContinentName
// didn't match any of the continent name in the map it will return true
// Although it shouldn't even be any way for it to happen but yeah
bool Map::IfPlayerOwnContinent(std::string PlayerName,
                               std::string ContinentName) {
  for (int i = 0; i < *NumberOfCountries; i++) {
    // If the continent is found then it will check
    if (ListOfCountries[i]->at(0)->Continent == ContinentName) {
      // Log("This country " << ListOfCountries[i]->at(0)->Name
      //                    << "Is in continent" << ContinentName << std::endl);
      if (ListOfCountries[i]->at(0)->OwnedBy != PlayerName) {
        // Log("This country " << ListOfCountries[i]->at(0)->Name << "Owned by"
        //                    << ListOfCountries[i]->at(0)->OwnedBy <<
        //                    std::endl);

        return false;
      } else {
        // Log("This country " << ListOfCountries[i]->at(0)->Name << "Owned by"
        // << ContinentName << std::endl);
      }
    }
  }
  return true;
}
// show list of adjacent of countries by ID
// aka where player can attack from this territory
void Map::ShowListOfAdjacentCountriesByID(int ID) {
  std::cout << "Country adjacent by country with ID: " << ID << std::endl;

  for (Territory* Temp : *ListOfCountries[ID]) {
    std::cout << Temp->Name << std::endl;
    std::cout << Temp->OwnedBy << std::endl;
  }
}
// method to display the countries owned by player
void Map::ShowListOfAdjacentCountriesOwnedByPlayer(std::string PlayerName) {
  std::cout << PlayerName << " owns : " << std::endl;
  for (int i = 0; i < *NumberOfCountries; i++) {
    if (ListOfCountries[i]->at(0)->OwnedBy == PlayerName) {
      std::cout << "Territory ID" << ListOfCountries[i]->at(0)->TerritoryID
                << ": " << ListOfCountries[i]->at(0)->Name << std::endl;
    }
  }
}

int Map::NumOfCountries() { return *this->NumberOfCountries; }

/// <summary>
/// Display the map and list of countries with its adjacent countries :O
/// </summary>
void Map::Display() {
  std::cout << "\n\nMap Name: " << *MapName << std::endl;

  for (int i = 0; i < *this->NumberOfCountries; i++) {
    int j = 0;

    for (Territory* country : *(this->ListOfCountries[i])) {
      if (j == 0) {
        std::cout << "Territory: " << i << std::endl;
        std::cout << "Name: " << country->Name << std::endl;
        std::cout << "Owned By: " << country->OwnedBy << std::endl;
        std::cout << "Armies: " << country->Armies << std::endl;
        std::cout << "Adjacent Countries " << std::endl;
        j++;
      } else {
        std::cout << "-> ";
        std::cout << "Country ID: " << country->TerritoryID << " ";
        std::cout << country->Name << "\n";
        std::cout << "Owned By: " << country->OwnedBy << std::endl;
        std::cout << "Armies: " << country->Armies << std::endl;
        j++;
      }
    }
    j = 0;
    std::cout << std::endl;
  }
}

// use this function when you want to display the countries that are in certain
// continent
void Map::Display(std::string continent) {
  std::cout << "\n\nMap Name: " << continent << std::endl;

  for (int i = 0; i < *this->NumberOfCountries; i++) {
    int j = 0;
    bool SameCountry = false;

    for (Territory* country : *(this->ListOfCountries[i])) {
      if (j == 0) {
        if (country->Continent == continent) {
          std::cout << "Territory: " << i << std::endl;
          std::cout << "Name: " << country->Name << std::endl;
          std::cout << "Owned By: " << country->OwnedBy << std::endl;
          std::cout << "Armies: " << country->Armies << std::endl;
          std::cout << "Adjacent Countries " << std::endl;
          SameCountry = true;
        }
        j++;
      } else {
        if (SameCountry) {
          std::cout << "-> ";
          std::cout << "Country ID: " << country->TerritoryID << " ";
          std::cout << country->Name << "\n";
          std::cout << "Owned By: " << country->OwnedBy << std::endl;
          std::cout << "Armies: " << country->Armies << std::endl;
          j++;
        }
      }
    }
    j = 0;
    std::cout << std::endl;
  }
}

// setters for the map name
// not really necessary
void Map::SetMapName(std::string mapName) {
  MapName = new std::string(mapName);
}

// getter for the map name
std::string Map::GetMapName() { return *MapName; }

// validate the map by checking many stuff
bool Map::Validate() {
  std::cout << "\n\n\nVALIDATING\n\n\n" << std::endl;

  if (*this->NumberOfCountries == NULL) return false;

  for (int i = 0; i < *this->NumberOfCountries; i++) {
    for (int x = i + 1; x < *this->NumberOfCountries; x++) {
      if (i == *this->NumberOfCountries) {
        x++;
        break;
      }

      // checking over2d arrays whether there are same ID with different names
      for (Territory* country : *(this->ListOfCountries[i])) {
        for (Territory* country2 : *(this->ListOfCountries[x])) {
          if (country->TerritoryID == country2->TerritoryID) {
            if (country->Name != country2->Name) {
              return false;
            }
          }
        }
      }
    }

    for (unsigned int j = 0; j < this->ListOfCountries[i]->size() - 1; j++) {
      // using my code, and how I design it. You don't even need to check
      // whether a country has two continents. They will have each individual
      // string

      if (this->ListOfCountries[i]->at(j)->Continent == "") {
        return false;
      }
      /*if (ListOfCountries[i]->at(j)->TerritoryID == NULL) {
              std::cout << "CountryID is empty! Error " << std::endl;
              return false;
      }*/
      if (ListOfCountries[i]->at(j)->Name == "") {
        return false;
      }

      // checking whether same country ID is found or same country name is found
      for (unsigned int k = j + 1; k < this->ListOfCountries[i]->size(); k++) {
        if (ListOfCountries[i]->at(j)->TerritoryID ==
            ListOfCountries[i]->at(k)->TerritoryID) {
          return false;
        }
        if (ListOfCountries[i]->at(j)->Name ==
            ListOfCountries[i]->at(k)->Name) {
          return false;
        }
      }
    }

    std::cout << std::endl;
  }
  // Log("Checking the visited");
  // thie section are responsible for finding whether the graph are connected a
  // not array of pointers this two variable are used to contain arrays C++
  // doesn't allow initializing Array of variable length
  bool** VisitedA = new bool*[*NumberOfCountries];
  bool** VisitedB = new bool*[*NumberOfCountries];

  // filling up the array with false
  for (int i = 0; i < *NumberOfCountries; i++) {
    VisitedA[i] = new bool(false);
    VisitedB[i] = new bool(false);
  }
  // Log("Filling up the array\n\n");
  /*if (_DEBUG) {
      DFS(0, VisitedA);
  }*/
  // DFS(*NumberOfCountries-1, VisitedB);

  bool IsConnected = true;
  // for the boolean array to check which country is visited
  /*for (int i = 0; i < *NumberOfCountries; i++) {
    std::cout << "Country: " << i << "  " << *VisitedA[i] << std::endl;
    ;
    if (!*VisitedA[i]) {
      std::cout << "The Country is not connected!" << std::endl;
      IsConnected = false;
    }
  }*/

  // Delete the boolean array
  for (int i = 0; i < *NumberOfCountries; i++) {
    delete VisitedA[i];
    delete VisitedB[i];
  }
  delete[] VisitedA;
  delete[] VisitedB;

  if (IsConnected)
    return true;
  else
    return false;
}

// DFS to check whether the graph is connected, visit through the objects and it
// will knows
void Map::DFS(int x, bool** visited) {
  *visited[x] = true;
  // Log("visited: " << x << " " << *visited[x] << "\n");
  int i = 0;

  for (Territory* temp : *ListOfCountries[0]) {
    // Log("Country???: " << temp->Name << temp->TerritoryID << std::endl);
    // Log("temp->territoryID: " << *visited[temp->TerritoryID]);

    if (i == 0) {
      i++;
    } else {
      // Log("Country: " << temp->Name);
      if (!*visited[temp->TerritoryID]) {
        // Log("Visit: " << temp->Name << "\n");
        DFS(temp->TerritoryID, visited);
      }
    }
  }
}

Map& Map::operator=(const Map* map) {
  // Log("Using Assignment Operator");
  MapName = new std::string(*(map->MapName));
  ListOfCountries = new std::vector<Territory*>*[1000];

  for (int i = 0; i < 1000; i++)
    ListOfCountries[i] = new std::vector<struct ::Territory*>;

  if (!(**(map->ListOfCountries)).empty()) {
    for (int i = 0; i < *(map->NumberOfCountries); i++) {
      for (Territory* country : *(map->ListOfCountries[i])) {
        // calling copy constructor of each Territory
        ListOfCountries[i]->push_back(country);
      }
    }
  }
  // Log("Copied successful\n");

  NumberOfCountries = new int(*(map->NumberOfCountries));
  // TODO: insert return statement here

  return *this;
}
