#ifndef HEADER_H
#define HEADER_H

#include<iostream>
#include<vector>
using namespace std;

#pragma once
enum Suit { C = 1, D = 2, H = 3, S = 4 };
enum Rank { two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7, eight = 8, nine = 9, ten = 10, jack = 11, queen = 12, king = 13, ace = 14 };
enum Score { straightflush = 9 , fourkind = 8, fullhouse = 7, Flush = 6, straight = 5, threekind = 4, twopairs = 3, Pair = 2, norank = 1};

struct Card {
	Suit cardS;
	Rank cardR;
};

//This struct identifies the score of each hand.
struct Pairs {
	//Indeces of the two pairs found, if any. Otherwise -1 for either.
	int index1;
	int index2;

	//The reank of the hand.
	Score handS;
	//The hand itself.
	//Testing how changes would work.
	vector<Card> hVec;


};

int readCards(vector<Card> & cardV, char * filename);
int printCards(const vector<Card> & cards);
int usage(char * program_name);
int printPokerHand( vector<Card> & myV);
const bool operator<(const Card& first, const Card& second);
Pairs pairCount(vector<Card>::iterator it);
ostream& operator<<(ostream& os, const Rank& myR);
ostream& operator<<(ostream& os, const Suit& myR);


#endif
