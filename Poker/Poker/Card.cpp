#include "Card.h"
#include <iostream>
using namespace std;

Card::Card()
{
	cardID = 0;
}

Card::Card(int val)
{
	cardID = val;
}

Card::~Card()
{
	//anything needed?
}

Card *Card::copy()
{
	Card *newCard = new Card(cardID);
	return newCard;
}

void Card::displayCard()
{
	cout << getVALUE() << "-";
	int s = getSUIT();
	string suit = " ";
	switch (s) {
		case 0: suit = "SPADE"; break;
		case 1: suit = "CLUBS"; break;
		case 2: suit = "HEART"; break;
		case 3: suit = "DIAMOND"; break;
	}
	cout << suit << endl;
}

//tests whether two cards "match" -- comparison operator overload
bool operator == (Card &c1, Card &c2)
{
	// I think this may still be valid?
	return (c1.getVALUE() == c2.getVALUE() || c1.getSUIT() == c2.getSUIT());
}