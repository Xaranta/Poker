#pragma once
#include <string>
#include <vector>

using namespace std;

class Card
{
	friend class Deck;  //allows Deck class access to Card's private member variables

protected:
	int cardID;      //value of card [1,2,3...50,51,52]

public:
	//CONSTRUCTORS/DESTRUCTOR
	Card();
	Card(int val);
	~Card();
	Card *copy();

	//SETTERS: VALUE, SUIT, SYMBOL, next
	void setCardID(int val) { cardID = val; }

	//GETTERS: VALUE, SUIT, SYMBOL, next
	int getVALUE()
	{   
		if (cardID % 13 == 0) return 13; //I don't want to deal with 0's when it comes sort for straights.
		else return cardID % 13;
	} 

	int getSUIT(){ return cardID % 4; } // 0 spade 1 club 2 heart 3 diamond.

	void displayCard();
};