/////////////////////////////////////////////
// Filename:        GameObservers.cpp
//
// Description:     Implementation of the Observer class
//                    and associated functionality
//
// Author:          Stefan Russo - 26683320
//
// Group:           Sandra Buchen - 26317987
//                  Le Cherng Lee - 40122814
//                  Zahra Nikbakht - 40138253
//                  Matthew Pan - 40135588
//                  Stefan Russo - 26683320
//
/////////////////////////////////////////////

#include "GameObservers.hpp"

#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

#include "GameEngine.h"
#include "Map.h"
#include "Player.h"

/////////////////////////////////////////////
// Observer Class
/////////////////////////////////////////////

/**
 * @brief Construct a new Observer:: Observer object
 *
 */
Observer::Observer() {}

/**
 * @brief Destroy the Observer:: Observer object
 *
 */
Observer::~Observer() {}

/////////////////////////////////////////////
// Subject Class
/////////////////////////////////////////////

/**
 * @brief Construct a new Subject:: Subject object
 *
 */
Subject::Subject() { _observers = new std::list<Observer *>; }

/**
 * @brief Attach the observer to the subject
 *
 * @param o
 */
void Subject::Attach(Observer *o) { _observers->push_back(o); }

/**
 * @brief Detatch the observer from the subject
 *
 * @param o
 */
void Subject::Detach(Observer *o) {
  // BUG there list no longer exists here
  _observers->remove(o);
}

/**
 * @brief Notify observers of a change in state
 *
 */
void Subject::Notify() {
  std::list<Observer *>::iterator i = _observers->begin();
  for (; i != _observers->end(); ++i) {
    (*i)->Update();
  }
}

/**
 * @brief Destroy the Subject:: Subject object
 *
 */
Subject::~Subject() {
  delete _observers;
  _observers = nullptr;
}

/**
 * @brief Set the new state of subject
 *
 * @param new_state
 */
void Subject::setState(State new_state) { current_state = new_state; }

/**
 * @brief Returns current_state
 *
 * @return State_enum
 */
State_enum Subject::getStateEnum() {
  State_enum returnState = current_state.current_state;
  return returnState;
}

/**
 * @brief Get the current state
 *
 * @return State
 */
State Subject::getState() { return current_state; }

/////////////////////////////////////////////
// PhaseObserver Class
/////////////////////////////////////////////

/**
 * @brief Construct a new Phase Observer:: Phase Observer object
 *
 * @param passed_phase_subject
 */
PhaseObserver::PhaseObserver(Subject *passed_phase_subject) {
  _phase_subject = passed_phase_subject;
  _phase_subject->Attach(this);
}

/**
 * @brief Process the updated new state
 *
 */
void PhaseObserver::Update() {
  Player *player_subject = dynamic_cast<Player *>(_phase_subject);
  Territory *territory_subject = dynamic_cast<Territory *>(_phase_subject);

  switch (_phase_subject->getStateEnum()) {
    case State_enum::SETUP_PHASE_RECEIVE_TERRITORY:
      std::cout << "[Phase Observer] Setup Phase";
      if (player_subject)
        std::cout << ": " << player_subject->PID << " received territory \""
                  << player_subject->Territories.back()->Name << "\".";
      if (territory_subject)
        std::cout << ": " << territory_subject->Name << " now owned by \""
                  << territory_subject->OwnedBy << "\".";
      std::cout << std::endl;
      break;
    case State_enum::SETUP_PHASE_RECEIVE_REINFORCEMENTS:
      std::cout << "[Phase Observer] Setup Phase";
      if (player_subject)
        std::cout << ": " << player_subject->PID << " received "
                  << player_subject->getState().newReinforcements
                  << " reinforcements.";
      std::cout << std::endl;
      break;
    case State_enum::REINFORCEMENT_PHASE:
      std::cout << "[Phase Observer] Reinforcement Phase";
      if (player_subject)
        std::cout << ": " << player_subject->PID << " received "
                  << player_subject->getState().newReinforcements
                  << " reinforcements.";
      std::cout << std::endl;
      break;
    case State_enum::ISSUE_ORDERS_PHASE:
      std::cout << "[Phase Observer] Issue Orders Phase ";
      if (player_subject) {
          std::shared_ptr<Order> temp = player_subject->ListOfOrders->peek();
          if (temp != nullptr)
              std::cout << ": " << player_subject->PID << " issued order \"" <<
              temp->getName() << "\"" << std::endl;
      }
      break;
    case State_enum::EXECUTE_ORDERS_PHASE:
      std::cout << "[Phase Observer] Execute Orders Phase ";
      if (player_subject) {
        std::string success = "Failed";
        if (player_subject->getState().execute_order_success)
          success = "Succeeded";
        std::cout << ": " << player_subject->PID << " executed order \""
                  << player_subject->getState().executed_order_name
                  << "\" - Result: " << success;
      }
      if (territory_subject) {
        if (territory_subject->getState().execute_order_success)
          std::cout << ": \"" << territory_subject->Name
                    << "\"- Owner: " << territory_subject->OwnedBy
                    << " Armies: " << territory_subject->Armies;
      }
      std::cout << std::endl;
      break;
    default:
      break;
  }
}

/**
 * @brief Destroy the Phase Observer:: Phase Observer object
 *
 */
PhaseObserver::~PhaseObserver() {
  _phase_subject->Detach(this);
}

/////////////////////////////////////////////
// Game Statistics Observer Class
/////////////////////////////////////////////

/**
 * @brief Construct a new Game Statistics Observer:: Game Statistics Observer
 * object
 *
 * @param passed_game_observer_subject
 */
GameStatisticsObserver::GameStatisticsObserver(
    Subject *passed_game_observer_subject) {
  _game_observer_subject = passed_game_observer_subject;
  _game_observer_subject->Attach(this);
}

/**
 * @brief Process the updated new state
 *
 */
void GameStatisticsObserver::Update() {
  GameEngine *game_engine_subject =
      dynamic_cast<GameEngine *>(_game_observer_subject);
  Territory *territory_subject =
      dynamic_cast<Territory *>(_game_observer_subject);

  switch (_game_observer_subject->getStateEnum()) {
    case State_enum::TERRITORY_CONQUERED:
      if (_game_observer_subject->getState().execute_order_success) {
        std::string order =
            _game_observer_subject->getState().executed_order_name;
        if (order == "ADVANCE" || order == "AIRLIFT") {
          std::cout << "[Game Statistics Observer] Territory Conquered";
          if (game_engine_subject) {
            game_engine_subject->displayStatistics();
          }
          if (territory_subject) {
            std::cout << ": \"" << territory_subject->Name << " conquered by "
                      << territory_subject->OwnedBy;
          }
          std::cout << std::endl;
        }
      }
      break;
    case State_enum::PLAYER_ELIMINATED:
      std::cout << "[Game Statistics Observer] Player Eliminated";
      if (game_engine_subject) {
        std::cout << ": " << game_engine_subject->getState().player_name;
        game_engine_subject->displayStatistics();
      }
      std::cout << std::endl;
      break;
    case State_enum::PLAYER_OWNS_ALL_TERRITORIES:
      std::cout
          << "[Game Statistics Observer] Player Owns All Territories. Game Won."
          << std::endl;
      if (game_engine_subject) {
        std::cout << "Congratulations!! Player \""
                  << game_engine_subject->getState().player_name
                  << "\" is the winner!" << std::endl;
        game_engine_subject->displayStatistics();
      }
      break;
    default:
      break;
  }
}

/**
 * @brief Destroy the Game Statistics Observer:: Game Statistics Observer object
 *
 */
GameStatisticsObserver::~GameStatisticsObserver() {
  _game_observer_subject->Detach(this);
}
