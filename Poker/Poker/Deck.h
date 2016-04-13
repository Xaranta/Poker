#pragma once
#include "Card.h"
#include <vector>

class Deck
{
protected:
	
	int SIZE;   //SIZE variable - indicates how many cards in deck

public:
	//CONSTRUCTOR
	Deck();
	
	Deck(const vector<int>& x); //wut do with this

	//Card *top;  //pointer to TOP of linked structure of cards
	vector<int> deck;

	int getSIZE() { return SIZE; }

	//FILL DECK
	void fill();                        //initialize the Deck to contain the standard 52 cards
	void addCard(int val);      //*insert* a new card into the Deck

										//DRAW CARD
	void Deck::drawCard(Deck &d); //*remove* top card from the Deck and return it

								  //FIND AND REMOVE
	void removeCard(int val); //*find* a specific card and remove it from the Deck

									   //SHUFFLE
	void shuffle(Deck &d);                     //randomize the order of cards in the Deck

	void sort(Deck &d);					 //sort the deck by value

										 //PRINT
	void print();                       //displays the contents of the Deck
	void printCards();

	string getRANK(int val)
	{
		string rank = "";
		int r = (val % 13) + 1;
		switch (r) {
		case 1: rank = "ACE"; break;
		case 2: rank = "2"; break;
		case 3: rank = "3"; break;
		case 4: rank = "4"; break;
		case 5: rank = "5"; break;
		case 6: rank = "6"; break;
		case 7: rank = "7"; break;
		case 8: rank = "8"; break;
		case 9: rank = "9"; break;
		case 10: rank = "10"; break;
		case 11: rank = "JACK"; break;
		case 12: rank = "QUEEN"; break;
		case 13: rank = "KING"; break;
		}
		return rank;
	}

	string getSUIT(int val)
	{
		string suit = "";
		int s = val / 13;
		switch (s) {
		case 0: suit = "SPADE"; break;
		case 1: suit = "CLUBS"; break;
		case 2: suit = "HEART"; break;
		case 3:
		case 4: suit = "DIAMOND"; break; suit = "DIAMOND"; break;

		} // 0 spade 1 club 2 heart 3 diamond.
		return suit;
	}

	int getintSUIT(int val)
	{
		int suit = -1;
		int s = val / 13;
		switch (s) {
		case 0: suit = 0; break;
		case 1: suit = 1; break;
		case 2: suit = 2; break;
		case 3:
		case 4: suit = 3; break;

		} // 0 spade 1 club 2 heart 3 diamond.
		return suit;
	}

	//int* getCardRanks();
	//pretty sure this is unnessicary. 
};