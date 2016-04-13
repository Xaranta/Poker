#include "Game.h"
#include "Deck.h"
#include <iostream>
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
	
	int winningHands[10][4];
	int rounds = 10;
	for (int i = 0; i < rounds; i++)
	{
		cout << endl << endl;
		cout << "Round #: " << i << endl;
		cout << "Round #: " << i << endl;

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

		int* playerHandStr = checkHand(myHand, communityCards);
		int* comp1HandStr = checkHand(compHand1, communityCards);
		int* comp2HandStr = checkHand(compHand2, communityCards);
		int* comp3HandStr = checkHand(compHand3, communityCards);

		int* winningHand = playerHandStr;
		if (comp1HandStr[0] > winningHand[0]) { winningHand = comp1HandStr; }
		if (comp2HandStr[0] > winningHand[0]) { winningHand = comp2HandStr; }
		if (comp3HandStr[0] > winningHand[0]) { winningHand = comp3HandStr; }


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

	int * handStrength = new int[4];// [0]= hand strength - [1] = high card - whats the third cell for...? flush suit? 2nd pair in the case of two pair and full house? kicker?

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

	
	cout << "printing out the full hand" << endl; //alright we got all 7 cards in an array
	for (int i = 0; i < 7; i++)
	{
		cout << result[i]%13 << "   ";
	}

	cout << endl;
	


	int ofAKind1 = 0, ofAKind2 = 0;
	bool pocketPair = false; // is this needed? for any reason.
	int highCard = 0;
	int kicker = 0;

	if (result[0]%13 == result[1]%13)  //pocket pair
	{
		pocketPair = true;
		ofAKind1++;
		highCard = result[0];
		for (int i = 2; i < 5; i++)
		{
			if (result[0]%13 == result[i]%13)
			{
				ofAKind1++;
			}
		}
	}
	else //everything else
	{
		for (int i = 0; i < 5; i++)
		{
			if (result[0]%13 == result[i + 2]%13)
			{
				ofAKind1++;
			}
		}
		for (int j = 0; j < 5; j++)
		{
			if (result[1]%13 == result[j + 2]%13)
			{
				ofAKind2++;
			}
		}
	}
	cout << "                                        of a kind1 = " << ofAKind1 << "  and of a kind2 = " << ofAKind2 << endl;

	if (ofAKind1 == 0 && ofAKind2 == 0) //Nothing in the hand, just need to set highcard and kicker
	{
		if (result[0]%13 > result[1]%13)
		{
			highCard = result[0]%13;
			kicker = result[1]%13;
		}
		else
		{
			highCard = result[1]%13;
			kicker = result[0]%13;
		}
	}

	if (ofAKind1 != 0 && ofAKind2 != 0) //at least a 2 pair, can lead to full house. 
	{
		if (ofAKind1 == ofAKind2)
		{
			if (result[0]%13 > result[1]%13)
			{
				highCard = result[0]%13;
				kicker = result[1]%13;
			}
			else
			{
				highCard = result[1]%13;
				kicker = result[0]%13;
			}
		}

		if (ofAKind1 > ofAKind2)
		{
			highCard = result[0]%13;
			kicker = result[1]%13;
		}

		if (ofAKind1 < ofAKind2)
		{
			highCard = result[1]%13;
			kicker = result[0]%13;
		}
	}

	if (ofAKind1 != 0 && ofAKind2 == 0) //single pair, first card of a kind.
	{
		highCard = result[0]%13;
		kicker = result[1]%13;
	}

	if (ofAKind1 == 0 && ofAKind2 != 0) //single pair, second card of a kind. 
	{
		highCard = result[1]%13;
		kicker = result[0]%13;
	}

	/* pretty sure I wrote this up earlier
	if ((ofAKind1 != 0 && ofAKind2 != 0) && (ofAKind1 > ofAKind2)) //basically in the case of a 2 pair, full house, or in the weird ass case that you have a four of a kind and a kicker pair
	{
		highCard = result[0];
		kicker = result[1];
	}

	if ((ofAKind1 != 0 && ofAKind2 != 0) && (ofAKind1 < ofAKind2)) //basically in the case of a 2 pair, full house, or in the weird ass case that you have a four of a kind and a kicker pair
	{
		highCard = result[1];
		kicker = result[0];
	}
	*/

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
		case 3: handStrength[0] = 8; handStrength[2] = highCard; handStrength[3] = kicker; break;//4 of a kind
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


	// I will get to tint sameSuit = 0; 


	/*
	cout << "printing ofaKind1 " << ofAKind1 << " and ofaKind2 " << ofAKind2 << endl;
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

	return handStrength;
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