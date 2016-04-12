#include "Deck.h"
#include "Card.h"
#include <iostream>
#include <time.h>
using namespace std;

Deck::Deck()
{
	top = NULL;
	SIZE = 0;
}

Deck::Deck(Card *n)
{
	top = n;
}
void Deck::fill()
{
	string suit;
	//creates a deck of 52 cards
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 4; j++) {
			switch (j) {
			case 0: suit = "HEART"; break;
			case 1: suit = "DIAMOND"; break;
			case 2: suit = "CLUB"; break;
			case 3: suit = "SPADE"; break;
			}//end switch
			addCard(i, suit);
		}//end for
	}//end for
}//end fill

void Deck::drawCard(Deck &d)
{
	Card *draw = top;
	if (draw != NULL) {
		top = top->getNext();
		SIZE--;
		d.addCard(draw->getVALUE(), draw->getSUIT());
	}
}//end drawCard

void Deck::removeCard(int val, string s)
{
	//FINDS CARD
	Card *cur = top;
	while (cur != NULL && cur->getVALUE() != val && cur->getSUIT() != s)
		cur = cur->getNext();
	if (cur != NULL)
		cout << cur->getVALUE() << cur->getSUIT();
	else {
		cout << "NOT FOUND";
		return;
	}//end else

	 //REMOVES CARD
	Card *remove, *prev;
	if (top->getVALUE() == val && top->getSUIT() == s) {
		remove = top;
		top = top->getNext();
		delete remove;
		SIZE--;
		removeCard(val, s);
	}//end if
	else {
		prev = top;
		while (prev->getNext() != NULL && prev->getNext()->getVALUE() != val && prev->getNext()->getSUIT() != s)
			prev = prev->getNext();
		if (prev->getNext() != NULL) {
			remove = prev->getNext();
			prev->setNext(remove->getNext());
			delete remove;
			SIZE--;
			removeCard(val, s);
		}//end if
	}//end else
}//end removeCard

void Deck::addCard(int val, string s)
{
	SIZE++;
	top = new Card(val, s, top);
}//end addCard

void Deck::shuffle(Deck &d)
{
	srand((unsigned)time(0));

	for (int i = 0; i < 15; i++) {
		//split deck in half -- leftHalf and rightHalf
		Deck leftHalf, rightHalf;

		int j = SIZE / 2;
		for (int k = j; k > 0; k--) {
			drawCard(leftHalf);  //drawCard off Deck and addCard to leftHalf
		}
		for (j; j > 0; j--) {
			drawCard(rightHalf);  //drawCard off Deck and addCard to rightHalf
		}
		while (leftHalf.getSIZE() > 0 && rightHalf.getSIZE() > 0) {
			int probPile = leftHalf.getSIZE() * 100 / (leftHalf.getSIZE() + rightHalf.getSIZE());

			int randomNum = rand() % 100 + 1;

			if (randomNum <= probPile) {
				leftHalf.drawCard(d);   //drawCard off leftHalf and addCard to Deck
			}
			else {
				rightHalf.drawCard(d);  //drawCard off rightHalf and addCard to Deck
			}
		}
		while (leftHalf.getSIZE() > 0) {
			leftHalf.drawCard(d);
		}
		while (rightHalf.getSIZE() > 0) {
			rightHalf.drawCard(d);
		}
	}
}

void Deck::sort(Deck &d)
{
	Card *prev = top;
	Card *iter = top->next;
	
	if ((iter->getVALUE()) <= (top->getVALUE()))
	{
		prev->next = iter->next;
		iter->next = top->next;
		top = iter;
		iter = prev->next;
	}
	


}
void Deck::print()
{
	cout << "Cards in pile: " << SIZE << endl;
	Card *cur = top;
	while (cur != NULL)
	{
		cur->displayCard();
		cur = cur->getNext();
	}
	cout << endl;


}//end print

int* Deck::getCardRanks()
{
	Card *cur = top;
	int * cardRanks = new int[52];
	int i = 0;
	while (cur != NULL)
	{
		cardRanks[i] = cur->getVALUE();
		i++;
		cur = cur->getNext();
	}
	return cardRanks;
}
