#include "Card.h"
#include <iostream>
using namespace std;

Card::Card()
{
	VALUE = 0; SUIT = " "; next = NULL;
}

Card::Card(int val, string s, Card *n)
{
	VALUE = val; SUIT = s; next = n;
}

Card::~Card()
{
	if (next) free(next);
}

Card *Card::copy()
{
	Card *newCard = new Card(VALUE, SUIT, next);
	return newCard;
}

void Card::displayCard()
{
	cout << VALUE << " ";
	cout << SUIT << endl;
}

//tests whether two cards "match" -- comparison operator overload
bool operator == (Card &c1, Card &c2)
{
	return (c1.getVALUE() == c2.getVALUE() || c1.getSUIT() == c2.getSUIT());
}