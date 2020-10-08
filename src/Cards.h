#pragma once
#include <vector> 
#include <iostream> 
#include <queue> 
#include <deque> 
#include "Player.h"
using namespace std;


class Card;
class Hand;
class Deck;


enum CardType {
	BOMB = 1,
	REINFORCEMENT,
	BLOCKADE,
	AIRLIFT,
	DIPLOMACY,

	EMPTY
};


class Card {
private:
	CardType* type;

public:

	//constructors
	Card();
	Card(CardType c);
	Card(const Card& c);
	~Card();

	//functions
	CardType* getType();
	void Play(Player& p, Deck& d);

	//operator overloading
	friend ostream& operator << (ostream& out, const Card& card);
	Card& operator = (const Card& c);
};


class Hand {

private:
	vector<Card*> hand;

public:

	//constructors
	Hand();
	Hand(const Hand& h);
	~Hand();

	//functions
	void add(CardType& const type);
	void remove(int index);
	int find(Card c);
	Card returnByPos(int pos);

	//operator overloading
	friend ostream& operator << (ostream& out, const Hand& h);
	Hand& operator = (const Hand& h);

};

class Deck {

private:
	queue<Card*> deck;
	int* size;
public:

	//constructors
	Deck();
	Deck(int const deckSize);
	Deck(const Deck& deck);
	~Deck();

	//functions
	Card draw(Hand& h);
	void add(CardType const type);
	int GetSize();

	//operator overloading
	friend ostream& operator << (ostream& out, const Deck& d);
	Deck& operator = (const Deck& d);

};
