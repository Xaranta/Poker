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
	int * checkOfaKinds(int * cardsInPlay);
	int * checkForFlushes(int * cardsInPlay);
	int* checkForStraights(int * cardsInPlay);
	int* checkForStraightFlushes(int * cardsInPlay);

	int * compareHandStr(int * handstr1, int * handstr2);

	int getintSUIT(int val);

	int * straightSort(int * arr, int size);
	int * straightFlushSort(int * arr, int size);
};

