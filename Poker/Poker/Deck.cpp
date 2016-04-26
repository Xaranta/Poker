#include "Deck.h"
#include "Card.h"
#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>  

using namespace std;

Deck::Deck()
{
	vector<int> deck;
	SIZE = 0;
}

Deck::Deck(const vector<int>& x)
{
	deck = x;
}
void Deck::fill()
{

	//creates a deck of 52 cards
	for (int i = 0; i < 52; i++) {
			addCard(i);
	}

}//end fill

void Deck::addCard(int val)
{
	vector<int>::iterator it;

	it = deck.begin();
	it = deck.insert(it, val);
	SIZE++;

	//top = new Card(val, s, top);
}//end addCard

void Deck::drawCard(Deck &d)
{
	if (deck.size() == 0) return;

	vector<int>::iterator it;
	it = deck.begin();
	d.addCard(*it);
	deck.erase(it);
	return;

}//end drawCard

void Deck::removeCard(int val)
{
	//FINDS CARD
	vector<int>::iterator it;

	it = deck.begin();

	for (int i = 0; i < SIZE; i++)
	{
		if (*it == val)
		{
			deck.erase(it);
			cout << "Found it and removed it: " << val << endl;
			return;
		}
	}
	cout << "Didn't find it" << endl;
	return;

	/*
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

	*/
}//end removeCard

//int myrandom(int i) { return rand() % i; }

void Deck::shuffle(Deck &d)
{

	srand((unsigned)time(0));
	for (int i = 0; i < 15; i++)
	{
		random_shuffle(deck.begin(), deck.end());
	}
	d = deck;
	d.SIZE = SIZE;
	/*
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
	*/
	return;
}

/*void Deck::sort(Deck &d)
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
*/

void Deck::print()
{
	if (deck.size() == 0) return;

	cout << "Cards in pile: " << deck.size() << endl;

	for (int i = 0; i< deck.size(); ++i)
		std::cout << ' ' << deck[i];
	std::cout << '\n';

}//end print

void Deck::printCards()
{
	if (deck.size() == 0) return;
	cout << "Cards in pile: " << deck.size() << endl;

	for (int i = 0; i< deck.size(); ++i)
	{ 
		cout << getRANK(deck[i]) << " - " << getSUIT(deck[i]) << endl;
	}
	return;

}//end printCards


//int* Deck::getCardRanks()
//{
//	Card *cur = top;
//	int * cardRanks = new int[52];
//	int i = 0;
//	while (cur != NULL)
//	{
//		cardRanks[i] = cur->getVALUE();
//		i++;
//		cur = cur->getNext();
//	}
//	return cardRanks;
//}
