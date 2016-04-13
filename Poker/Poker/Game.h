#pragma once
#include "Deck.h"

class Game
{
	friend class Deck;  //allows Deck class access to Card's private member variables
	friend class Card;  //allows Deck class access to Card's private member variables
protected:
	Deck unShuffled, shuffled, discardPile, communityCards, myHand, compHand1, compHand2, compHand3;

	//Card *drawCard;
public:
	Game();
	int* checkHand(Deck &playerhand, Deck &communityCards);
	void printHandStrength(int * handStrength);
};
