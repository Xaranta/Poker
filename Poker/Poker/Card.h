#pragma once
#include <string>
using namespace std;

class Card
{
	friend class Deck;  //allows Deck class access to Card's private member variables

protected:
	int VALUE;      //value of card [1,2,3...11,12,13]
	string SUIT;    //HEART, DIAMOND, CLUB, SPADE
	Card *next;

public:
	//CONSTRUCTORS/DESTRUCTOR
	Card();
	Card(int val, string s, Card *n);
	~Card();
	Card *copy();

	//SETTERS: VALUE, SUIT, SYMBOL, next
	void setVALUE(int val) { VALUE = val; }
	void setSUIT(string s) { SUIT = s; }
	void setNext(Card *n) { next = n; }

	//GETTERS: VALUE, SUIT, SYMBOL, next
	int getVALUE() { return VALUE; }
	string getSUIT() { return SUIT; }
	Card *getNext() { return next; }

	void displayCard();
};