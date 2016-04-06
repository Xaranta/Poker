#pragma once
#include "Card.h"

class Deck
{
protected:
	int SIZE;   //SIZE variable - indicates how many cards in deck

public:
	//CONSTRUCTOR
	Deck();
	Deck(Card *n);

	Card *top;  //pointer to TOP of linked structure of cards

	int getSIZE() { return SIZE; }

	//FILL DECK
	void fill();                        //initialize the Deck to contain the standard 52 cards
	void addCard(int v, string s);      //*insert* a new card into the Deck

										//DRAW CARD
	void Deck::drawCard(Deck &d); //*remove* top card from the Deck and return it

								  //FIND AND REMOVE
	void removeCard(int val, string s);//*find* a specific card and remove it from the Deck

									   //SHUFFLE
	void shuffle(Deck &d);                     //randomize the order of cards in the Deck

	void sort(Deck &d);					 //sort the deck by value

										 //PRINT
	void print();                       //displays the contents of the Deck

	int* getCardRanks();
};