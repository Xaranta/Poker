#include "Game.h"
#include "Deck.h"
#include <iostream>
#include <algorithm>
using namespace std;

Game::Game()
{
	unShuffled.fill(); //myHand = NULL; compHand = NULL; discardPile = NULL;
	unShuffled.print();

	
	unShuffled.shuffle(shuffled);
	shuffled.print();
	cout << " first cell of shuffled " << shuffled.deck[0] << endl;
	//cout >> endl;
	
	//

	cout << "beginning game loop" << endl << endl;
	
	int winningHands[15][4];
	int rounds = 15;
	for (int i = 0; i < rounds; i++)
	{
		cout << endl << endl;
		cout << "Round #: " << i << endl;
		cout << "------------------------------------------------------------------------------" << endl;
		cout << "------------------------------------------------------------------------------" << endl;

		//Array to hold the winning hands

		


		unShuffled.shuffle(shuffled);
		//------------------------------------ This is essentially the code for the round function.
		// void playRound( round #, playerArray[]) - each round a player has to put in the big blind. 
		// maybe we can pass in the round number and decide that way. So if we are passing in the case of the first round with 4 players in the player array,
		//it would look like this: big blind = playerArray[ (round# + playerArray.size() - 1) % playerArray.size() ].
		//If we did this, then round 1 would put the big blind on playerArray[0].

		//There are 4 rounds of betting. First after the players are dealt their cards, then the flop, then the "turn", then the river.

		//Turn 1
		// int pot = 0;
		//All players put an ante into the pot. One player places big ante. Players must either call the big ante, raise past it, or fold their hand.

		// deal all players their cards cards. 
		for (int i = 0; i < 2; i++) {
			//drawCard = drawPile.drawCard();
			shuffled.drawCard(myHand);
			shuffled.drawCard(compHand1);
			shuffled.drawCard(compHand2);
			shuffled.drawCard(compHand3);
		}

		//first betting round goes here. betRound(playerArray[]);

		/*
		cout << "My hand" << endl;
		myHand.printCards();
		cout << "Computer 1's hand" << endl;
		compHand1.printCards();
		cout << "Computer 2's hand" << endl;
		compHand2.printCards();
		cout << "Computer 3's hand" << endl;
		compHand3.printCards();
		*/

		//Turn 2: the flop

		shuffled.drawCard(discardPile); //first burn card

		shuffled.drawCard(communityCards); // deal three cards for the flop
		shuffled.drawCard(communityCards);
		shuffled.drawCard(communityCards);

		//cout << endl << "THE FLOP" << endl;
		//communityCards.printCards();

		//Betting round goes here

		//Turn 3: The "turn"
		shuffled.drawCard(discardPile); // second burn card
		shuffled.drawCard(communityCards); //deal turn card

		//cout << endl << "THE TURN" << endl;
		//communityCards.printCards();

		//betting round here

		//Turn 4: The River
		shuffled.drawCard(discardPile); // third burn card
		shuffled.drawCard(communityCards); //deal river card

		//cout << endl << "THE RIVER" << endl;
		//communityCards.printCards();

		//final round of betting.
		//compare the handStrengths of all remaining players. 

		//shuffled.print(); Just wanted to make sure cards were being removed
		cout << "now checking player's hand" << endl;
		int* playerHandStr = checkHand(myHand, communityCards);

		cout << "now checking Computer21's hand" << endl;
		int* comp1HandStr = checkHand(compHand1, communityCards);

		cout << "now checking Computer2's hand" << endl;
		int* comp2HandStr = checkHand(compHand2, communityCards);

		cout << "now checking Computer3's hand" << endl;
		//int* comp3HandStr = checkHand(compHand3, communityCards);

		vector<int> test1 = { 14,15 };
		vector<int> test2 = { 29,30,28,44,7 };

		Deck t1(test1);
		Deck t2(test2);

		int* comp3HandStr = checkHand(t1,t2);

		int* winningHand = playerHandStr;
		winningHand = compareHandStr(winningHand, comp1HandStr);
		winningHand = compareHandStr(winningHand, comp2HandStr);
		winningHand = compareHandStr(winningHand, comp3HandStr);


		//------------------------------------------------
		//calculate and print players hands

		/*cout << endl << "player hand strength" << endl;
		printHandStrength(playerHandStr);

		cout << "Computer 1 hand strength" << endl;
		printHandStrength(comp1HandStr);

		cout << "Computer 2 hand strength" << endl;
		printHandStrength(comp2HandStr);

		cout << "Computer 3 hand strength" << endl;
		printHandStrength(comp3HandStr);
		*/

		for (int j = 0; j<4; j++)
		{
			winningHands[i][j] = winningHand[j];
		}

		//compare all the remaining handStrengths. Just cycle through the indexes of the handStrength arrays and, the loop will run until one of the players has the
		//highest value. For instance, if 2 players both have a pair of jacks, having 1 jack in their hand, and the other as a community card, you would then
		//compare high cards. If the highest card in both of their hands was that jack, then the loop would check who has the highest kicker card. If the players 
		// match all the way through the array, the pot is split between those players. 
	}
	cout << "The winning hands of the games " << endl;
	
	for (int k = 0; k < rounds; k++)
	{
		printHandStrength(winningHands[k]);
	}

	return;
}


int* Game::checkHand(Deck &playerHand, Deck &communityCards)
{
	//What is the best way to keep track of the best hand?
	//Deck bestFive; //In texas holdem, you make the best 5 card hand you can with the two cards you are holding in addition to the 5 community cards. 


	//I'm just going to define a discrete value system for the strength of the hands. Maybe the best thing to do is to define an array. 

	// [0]= hand strength - [1] = high card - whats the third cell for...? flush suit? 2nd pair in the case of two pair and full house? kicker?

	//hand strength ----------------------------------------------------------------------------------
	// nothing / high card ----- [0] = 1 ----- [1] = 0 - 12 (2 - ACE) ----- no additional cells needed ---- [0] represents hand rank, [1] represents the high card
	// single pair ------------- [0] = 2 ----- [1] = 0 - 12 (2 - ACE) ----- no additional cells needed ---- [0] represents hand rank, [1] represents the high card
	// two pair ---------------- [0] = 3 ----- [1] = 0 - 12 (2 - ACE) ----- [2] = 0 - 12 (2 - ACE) --------- [0] represents hand rank, [1] represents the first pair, [2] the second
												// is a extra cell needed for the high card? or will we assume [2] is the high card

												// Three pair -------------- [0] = 4 ----- [1] = 0 - 12 (2 - ACE) ----- no additional cells needed ---- [0] represents hand rank, [1] represents the high card
												// Straight ---------------- [0] = 5 ----- [1] = 0 - 12 (2 - ACE) ----- no additional cells needed ---- [0] represents hand rank, [1] represents the high card
												// Flush ------------------- [0] = 6 ----- [1] = 0 - 12 (2 - ACE) ----- [2] = 0 - 3 (The suit) ----- no additional cells needed ---- [0] represents hand rank, [1] represents the high card, [2] card suit
												// Full House -------------- [0] = 7 ----- [1] = 0 - 12 (2 - ACE) ----- [2] = 0 - 12 (2 - ACE) --------- [0] represents hand rank, [1] represents the first pair, [2] the second pair. 
												//same question as two pair, should I set it up with the high card? Or just program it so [2] is also the high card

												// Four of a Kind ---------- [0] = 8 ----- [1] = 0 - 12 (2 - ACE) ----- no additional cells needed ---- [0] represents hand rank, [1] represents the high card
												// Straight Flush ---------- [0] = 9 ----- [1] = 0 - 12 (2 - ACE) ----- [2] = 0 - 3 (The suit) ----- no additional cells needed ---- [0] represents hand rank, [1] represents the high card, [2] card suit
												// Royal Flush ------------- [0] = 10 ---- [1] = 0-3 (suits) ----- no additional cells ----- the only variance this hand can have is the suit. 


	int * cardRanks = new int[7];

	int * result = new int[7];
	// this is ugly fucking code but I was trying to just get it done. 
	result[0] = playerHand.deck[0];
	result[1] = playerHand.deck[1];
	result[2] = communityCards.deck[0];
	result[3] = communityCards.deck[1];
	result[4] = communityCards.deck[2];
	result[5] = communityCards.deck[3];
	result[6] = communityCards.deck[4];

	int * handStrength1 = new int[4];
	int * handStrength2 = new int[4];
	int * handStrength3 = new int[4];
	int * handStrength4 = new int[4];

	cout << "now checking of a kinds" << endl;
	handStrength1 = checkOfaKinds(result);

	cout << "now checking flush" << endl;
	handStrength2 = checkForFlushes(result);

	cout << "now checking straights" << endl;
	handStrength3 = checkForStraights(result);

int* winningHand = handStrength1;
winningHand = compareHandStr(winningHand, handStrength2);

winningHand = compareHandStr(winningHand, handStrength3);


	/*
	cout << "printing inSequence1 " << inSequence1 << " and ofaKind2 " << ofAKind2 << endl;
	cout << "printing highcard " << highCard << " and kicker " << kicker << endl;
	
	cout << "printing handStrength array" << endl << endl;
	for (int i = 0; i < 4; i++)
	{
		if (handStrength[i] > 0)
		{
			cout << handStrength[i] << "---";
		}

	}
	cout << endl;
	*/

	return winningHand;
}


void Game::printHandStrength(int * handStrength) //for testing purposes to print out hand strenght
{
	for (int i = 0; i < 4; i++)
	{
		if (handStrength[i] > -1)
		{
			cout << handStrength[i] << "---";
		}

	}
	cout << endl;
	return;
}


//--------------------------------------------------------------------------------------
// Check for of a kinds
//--------------------------------------------------------------------------------------
int* Game::checkOfaKinds(int * cardsInPlay) 
{
	/*
	result[0] = playerHand.deck[0];
	result[1] = playerHand.deck[1];
	result[2] = communityCards.deck[0];
	result[3] = communityCards.deck[1];
	result[4] = communityCards.deck[2];
	result[5] = communityCards.deck[3];
	result[6] = communityCards.deck[4];
	*/
	int * handStrength = new int[4];

	int * cardsInSuit = new int[7];

	for (int i = 0; i < 7; i++)
	{
		cardsInSuit[i] = cardsInPlay[i]/13;

	}
	cout << "printing out the full hand" << endl; //alright we got all 7 cards in an array
	for (int i = 0; i < 7; i++)
	{
		cout << cardsInPlay[i] % 13 << "   ";
	}

	cout << endl;



	int ofAKind1 = 0, ofAKind2 = 0;
	bool pocketPair = false; // is this needed? for any reason.
	int highCard = 0;
	int kicker = 0;

	if (cardsInPlay[0] % 13 == cardsInPlay[1] % 13)  //pocket pair
	{
		pocketPair = true;
		ofAKind1++;
		highCard = cardsInPlay[0];
		for (int i = 2; i < 5; i++)
		{
			if (cardsInPlay[0] % 13 == cardsInPlay[i] % 13)
			{
				ofAKind1++;
			}
		}
	}
	else //everything else
	{
		for (int i = 0; i < 5; i++)
		{
			if (cardsInPlay[0] % 13 == cardsInPlay[i + 2] % 13)
			{
				ofAKind1++;
			}
		}
		for (int j = 0; j < 5; j++)
		{
			if (cardsInPlay[1] % 13 == cardsInPlay[j + 2] % 13)
			{
				ofAKind2++;
			}
		}
	}
	cout << "                                        of a kind1 = " << ofAKind1 << "  and of a kind2 = " << ofAKind2 << endl;

	if (ofAKind1 == 0 && ofAKind2 == 0) //Nothing in the hand, just need to set highcard and kicker
	{
		if (cardsInPlay[0] % 13 > cardsInPlay[1] % 13)
		{
			highCard = cardsInPlay[0] % 13;
			kicker = cardsInPlay[1] % 13;
		}
		else
		{
			highCard = cardsInPlay[1] % 13;
			kicker = cardsInPlay[0] % 13;
		}
	}

	if (ofAKind1 != 0 && ofAKind2 != 0) //at least a 2 pair, can lead to full house. 
	{
		if (ofAKind1 == ofAKind2)
		{
			if (cardsInPlay[0] % 13 > cardsInPlay[1] % 13)
			{
				highCard = cardsInPlay[0] % 13;
				kicker = cardsInPlay[1] % 13;
			}
			else
			{
				highCard = cardsInPlay[1] % 13;
				kicker = cardsInPlay[0] % 13;
			}
		}

		if (ofAKind1 > ofAKind2)
		{
			highCard = cardsInPlay[0] % 13;
			kicker = cardsInPlay[1] % 13;
		}

		if (ofAKind1 < ofAKind2)
		{
			highCard = cardsInPlay[1] % 13;
			kicker = cardsInPlay[0] % 13;
		}
	}

	if (ofAKind1 != 0 && ofAKind2 == 0) //single pair, first card of a kind.
	{
		highCard = cardsInPlay[0] % 13;
		kicker = cardsInPlay[1] % 13;
	}

	if (ofAKind1 == 0 && ofAKind2 != 0) //single pair, second card of a kind. 
	{
		highCard = cardsInPlay[1] % 13;
		kicker = cardsInPlay[0] % 13;
	}


	switch (ofAKind1) {
	case 0: //card one is nothing.
		switch (ofAKind2) {
		case 0:
			handStrength[0] = 1;
			handStrength[1] = highCard;
			handStrength[2] = kicker;
			break;
		case 1:
			handStrength[0] = 2;
			handStrength[1] = highCard;
			handStrength[2] = kicker;
			break; //pair
		case 2:
			handStrength[0] = 4;
			handStrength[1] = highCard;
			handStrength[2] = kicker;
			break; //3 of a kind
		case 3: handStrength[0] = 8; handStrength[1] = highCard; handStrength[2] = kicker; break;//4 of a kind
		}
		break;
	case 1: //pair
		switch (ofAKind2) {
		case 0:
			handStrength[0] = 2;
			handStrength[1] = highCard;
			handStrength[2] = kicker;
			break;
		case 1:
			handStrength[0] = 3;
			handStrength[1] = highCard;
			handStrength[2] = kicker;
			break;
		case 2:
			handStrength[0] = 7;
			handStrength[1] = highCard;
			handStrength[2] = kicker;
			break;
		case 3:
			handStrength[0] = 8;
			handStrength[1] = highCard;
			handStrength[2] = kicker;
			break;
		}
		break;
	case 2: //three of a kind
		switch (ofAKind2) {
		case 0:
			handStrength[0] = 4;
			handStrength[1] = highCard;
			handStrength[2] = kicker;
			break;
		case 1:
			handStrength[0] = 7;
			handStrength[1] = highCard;
			handStrength[2] = kicker;
			break;
		case 2:
			handStrength[0] = 7;
			handStrength[1] = highCard;
			handStrength[2] = kicker;
			break;
		case 3:
			handStrength[0] = 8;
			handStrength[1] = highCard;
			handStrength[2] = kicker;
			break;
		}
		break;
	case 3: //four of a kind
		switch (ofAKind2) {
		case 0:
			handStrength[0] = 8;
			handStrength[1] = highCard;
			handStrength[2] = kicker;
			break;
		case 1:
			handStrength[0] = 8;
			handStrength[1] = highCard;
			handStrength[2] = kicker;
			break;
		case 2:
			handStrength[0] = 8;
			handStrength[1] = highCard;
			handStrength[2] = kicker;
			break;
		case 3:
			handStrength[0] = 8;
			handStrength[1] = highCard;
			handStrength[2] = kicker;
			break; //2 four of a kinds, not possible.
		}
		break;
	}
	printHandStrength(handStrength);
	return handStrength;
}

//--------------------------------------------------------------------------------------
// Check for Flushes
//--------------------------------------------------------------------------------------
int * Game::checkForFlushes(int * cardsInPlay){
	int * handStrength = new int[4];

	int * cardSUITS = new int[7];
	for (int i = 0; i < 7; i++)
	{
		cardSUITS[i] = getintSUIT(cardsInPlay[i]);
	}

	//checkOfaKinds(cardsInPlay);
	/*cout << "printing out the full hand" << endl; //alright we got all 7 cards in an array
	for (int i = 0; i < 7; i++)
	{
		cout << cardsInPlay[i] % 13 << "   ";
	}*/

	cout << endl << "printing out suit" << endl; //alright we got all 7 cards in an array

	for (int i = 0; i < 7; i++)
	{
		cout << cardSUITS[i] << "   ";
	}

	cout << endl;

	int sameSuit1 = 0, sameSuit2 = 0;
	bool pocketSuits = false; // is this needed? for any reason.
	int highCard = 0;
	int kicker = 0;

	if (cardSUITS[0] == cardSUITS[1])  //pocket pair
	{
		pocketSuits = true;
		sameSuit1++;
		highCard = cardSUITS[0];
		for (int i = 2; i < 5; i++)
		{
			if (cardSUITS[0] == cardSUITS[i])
			{
				sameSuit1++;
			}
		}
	}
	else //everything else
	{
		for (int i = 0; i < 5; i++)
		{
			if (cardSUITS[0] == cardSUITS[i + 2])
			{
				sameSuit1++;
			}
		}
		for (int j = 0; j < 5; j++)
		{
			if (cardSUITS[1] == cardSUITS[j + 2])
			{
				sameSuit2++;
			}
		}
	}
	cout << "                                        sameSuit1 = " << sameSuit1 << "  and sameSuit2 = " << sameSuit2 << endl << endl;

	if(sameSuit1 == 4)
	{
		highCard = cardsInPlay[0] % 13;
		kicker = cardsInPlay[1] % 13;
	}
	if (sameSuit2 == 4)
	{
		highCard = cardsInPlay[1] % 13;
		kicker = cardsInPlay[0] % 13;
	}

	else
	{
		if (cardsInPlay[0] % 13 > cardsInPlay[1] % 13)
		{
			highCard = cardsInPlay[0] % 13;
			kicker = cardsInPlay[1] % 13;
		}
		else
		{
			highCard = cardsInPlay[1] % 13;
			kicker = cardsInPlay[0] % 13;
		}
	}


	switch (sameSuit1) {
	case 0:
	case 1:
	case 2:
	case 3:
		switch (sameSuit2) {
		case 0:
		case 1:
		case 2:
		case 3:
			handStrength[0] = 1;
			handStrength[1] = highCard;
			handStrength[2] = kicker;
			break;
		
		case 4:
			handStrength[0] = 6; handStrength[1] = highCard; handStrength[2] = kicker; handStrength[3] = getintSUIT(cardsInPlay[1]); break; //card2 has a flush
		}
		break;

	case 4: //four of a kind
		switch (sameSuit2) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4: //not possible. 
			handStrength[0] = 6; handStrength[2] = highCard; handStrength[3] = kicker; handStrength[4] = getintSUIT(cardsInPlay[0]); break; //card2 has a flush
		}
		break;
	}
	printHandStrength(handStrength);
	return handStrength;
}

int Game::getintSUIT(int val)
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

//--------------------------------------------------------------------------------------
// Check Straights
//--------------------------------------------------------------------------------------

int* Game::checkForStraights(int * cardsInPlay)
{
	/*
	result[0] = playerHand.deck[0];
	result[1] = playerHand.deck[1];
	result[2] = communityCards.deck[0];
	result[3] = communityCards.deck[1];
	result[4] = communityCards.deck[2];
	result[5] = communityCards.deck[3];
	result[6] = communityCards.deck[4];
	*/

	int * handStrength = new int[4];

	int * cardsInStraight = new int[7];
	
	int handCard1 = cardsInPlay[0];
	int handCard2 = cardsInPlay[1];

	cardsInStraight = cardsInPlay;
	/*do we need this?
	
	for (int i = 0; i < 7; i++)
	{
		cardsInStraight[i] = cardsInPlay[i] % 13;

	}
	*///-------

	cout << "printing out the full hand" << endl; //alright we got all 7 cards in an array
	for (int i = 0; i < 7; i++)
	{
		cout << cardsInPlay[i] % 13 << "   ";
	}

	cout << endl;
	

	cardsInStraight = straightSort(cardsInStraight, 7);

	cout << "printing out the sorted hand" << endl; //alright we got all 7 cards in an array
	for (int i = 0; i < 7; i++)
	{
		cout << cardsInStraight[i] << "   ";
	}

	cout << endl;

	

	int inSequence1 = 0, inSequence2 = 0;
	bool pocketPair = false; // is this needed? for any reason.
	int highCard = -1;
	int kicker = -1;

	int seqHigh = -1; // I want to save the highest point in the sequence;

	int seqStart = 0; //keep track of the low card in the straight

	int offset = 0; //for when there are doubles in the sequence. IMPLEMENT THIS NEXT

	for (int i = 1; i < 7; i++)
	{
		if (cardsInStraight[seqStart] == cardsInStraight[i]) //for example if the first 2 are the same value, just move seqStart to the next index.
		{
			seqStart++;
		}
		if(cardsInStraight[seqStart]+i-offset==cardsInStraight[i])
		{
			inSequence1++;
			seqHigh = cardsInStraight[i];
		}
		if (inSequence1 >= 4 && cardsInStraight[seqStart] + 1 - offset == cardsInStraight[i]) //if you have a straight longer than 5 cards
		{
			inSequence1++;
			seqHigh = cardsInStraight[i];
			seqStart++;
		}

		if(cardsInStraight[seqStart] + i - offset != cardsInStraight[i])
		{
			if (cardsInStraight[i-1] == cardsInStraight[i])
			{
				offset++;
			}
			else if (inSequence1 < 4 )
			{
				inSequence1 = 0;
				seqStart++;
			}
			if (inSequence1 >4)
			{
				seqStart++;
			}
			
		}
	}
	cout << " hand cards" << handCard1 << " " << handCard2 << endl;
	cout << "                                   number of cards in sequence = " << inSequence1 << endl;

	if (inSequence1 < 4) //No straight just need to set highcard and kicker
	{
		if (handCard1 > handCard2)
		{
			highCard = handCard1;
			kicker = handCard2;
		}
		else
		{
			highCard = handCard2;
			kicker = handCard1;
		}
	}

	if (inSequence1 >=4) //at least a 2 pair, can lead to full house. 
	{
		highCard = seqHigh;
		if (handCard1 > handCard2)
		{
			kicker = handCard1;
		}
		else
		{
			kicker = handCard2;
		}
		
	}


	switch (inSequence1) {
	case 0: //card one is nothing.
	case 1:
	case 2:
	case 3:
		handStrength[0] = 1;
		handStrength[1] = highCard;
		handStrength[2] = kicker;
		break;
	case 4:
	case 5:
	case 6:
		handStrength[0] = 5;
		handStrength[1] = highCard;
		handStrength[2] = kicker;
		break;
	}
	printHandStrength(handStrength);
	return handStrength;
}





int * Game::compareHandStr(int * handstr1, int * handstr2)
{
	for (int i = 0; i < 4; i ++){
		if (handstr1[i] > handstr2[i]) { return handstr1; }
		if (handstr1[i] < handstr2[i]) { return handstr2; }
	}
	if (handstr1[3] == handstr2[3]) { return handstr1; }
}

int * Game::straightSort(int * arr, int size)
{
	int min, temp;
	for (int i = 0; i < size; i++)
	{
		min = i;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] % 13 <= arr[min] % 13)
			{
				min = j;
			}
		}
		temp = arr[i]% 13;
		arr[i] = arr[min] % 13;
		arr[min] = temp % 13;
	}
	return arr;
}