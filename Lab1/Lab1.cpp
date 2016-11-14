/*	Source.cpp
Authors: Carlos Gonzalez
Email: cgonzalezmendoza@wustl.edu
Description: This program reads in the command line argument for a file name, opens it and reads strings from it,
and parses those strings as the definitions of cards in a standard playing deck for poker. It then identifies each set of 5 cards
as a hand and returns the ranking of each hand (Flush, Straight Flush, Pair, etcc.), which is sorted in ascending order, based on the rules of poker.
Lastly, it prints each card in the deck sorted by rank first and suite second.*/

#include "stdafx.h"
#include "Lab1.h"

#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<algorithm>
#include<vector>
#include <cstring>

using namespace std;

int main(int argc, char *argv[]) {
	if (argc != 2) {
		return usage(argv[0]);
	}
	vector<Card> testing;
	
	cout << endl<<"Reading the cards from the input file..."<<endl;
	int inttest = readCards(testing, argv[1]);
	if (inttest != 0) return inttest;

	cout <<endl<< "Here are the rankings for each hand, sorted:" << endl;
	int readHand = printPokerHand(testing);
	if (readHand != 0) return readHand;
	cout <<endl<< "Here is the entire sorted deck:" << endl;

	sort(testing.begin(), testing.end());
	return printCards(testing);
}

//Parsing function that stores valid card strings in a Card vector.
int readCards(vector<Card> & cardV, char * filename) {
	ifstream ifs;
	ifs.open(filename);
	if (!ifs.is_open()) {
		cout << "Could not open the file: " << filename;
		return -2;
	}
	else {
		int lineCount = 0; //Current line being read.
		string line;
		int cardCount = 0; //Number of cards read per line.
		vector<Card> temp; //Temporary card vector in case we dont read exactly five cards.
		while (getline(ifs, line)) {
			
			istringstream iss(line);
			string word;
			if (line.empty()) {
				continue;
			}
			while (iss >> word) {
				if (word.compare("//") == 0) {
					lineCount++;
					break;
				}
					bool flag = true;
					int indexToCheck = 1;
					Suit cardS;
					Rank cardR;
					if (word.length() == 3) {
						indexToCheck = 2;
						if (word[0] == '1' && word[1] == '0') {
							cardR = ten;
							}
						else {
							flag = false;
							}
					}
					else if (word.length() == 2) {
						switch (toupper(word[0])) {
						case '2': { cardR = two; break; }
						case '3': { cardR = three; break; }
						case '4': { cardR = four; break; }
						case '5': { cardR = five; break; }
						case '6': { cardR = six; break; }
						case '7': { cardR = seven; break; }
						case '8': { cardR = eight; break; }
						case '9': { cardR = nine; break; }
						case 'J': { cardR = jack; break; }
						case 'Q': { cardR = queen; break; }
						case 'K': { cardR = king; break; }
						case 'A': { cardR = ace; break; }
						default: {flag = false; break; }
						}
					}
					if (word.length() == 2 || word.length() == 3) {
						switch (toupper(word[indexToCheck])) {
						case 'C': { cardS = C; break; }
						case 'S': { cardS = S; break; }
						case 'D': { cardS = D; break; }
						case 'H': { cardS = H; break; }
						default: { flag = false; break; }
						}
						if (flag) {
							temp.push_back({ cardS,cardR });
							cardCount++; 
						}
						else {
							cout << "Invalid card definition: " << word << endl; //Invalid character read.
						}
					}
			}
			if (cardCount == 5) {
				for (unsigned i = 0; i < temp.size(); i++) {
					cardV.push_back(temp[i]);
				}
			}
			else if (cardCount < 5){
				cout << "Not enough cards! Cards read: " << cardCount << " at line: "<<lineCount <<endl;
				}
			else if (cardCount > 5) {
				cout << "Too many cards! Cards read: " << cardCount << " at line: " << lineCount << endl;
			}
			temp.clear();
			cardCount = 0;
			lineCount++;
		}
		ifs.close();
	}
	return 0;
}

// Helper function to print out the program's usage message. 
int usage(char * program_name) {

	cout << "Usage: " << program_name << " file-to-read.txt " << endl
		<< "Purpose: Reads a set of cards from an input file."
		<< endl;
	return -1;
}

//Printing function that prints all the Cards parsed from the input file.
int printCards(const vector<Card> & cards) {
	for (size_t i = 0; i < cards.size(); i++) {
		string cardRank;
		string cardSuit;

		switch (cards[i].cardS) {
		case C: {
			cardSuit = "Clubs";
			break;
		}
		case S: {
			cardSuit = "Spades";
			break;
		}
		case D: {
			cardSuit = "Diamonds";
			break;
		}
		case H: {
			cardSuit = "Hearts";
			break;
		}
		default:
			cout << "Undefined suit!";
			return -3;
		}
		switch (cards[i].cardR) {
		case two: {
			cardRank = "Two";
			break;
		}
		case three: {
			cardRank = "Three";
			break;
		}
		case four: {
			cardRank = "Four";
			break;
		}
		case five: {
			cardRank = "Five";
			break;
		}
		case six: {
			cardRank = "Six";
			break;
		}
		case seven: {
			cardRank = "Seven";
			break;
		}
		case eight: {
			cardRank = "Eight";
			break;
		}
		case nine: {
			cardRank = "Nine";
			break;
		}
		case ten: {
			cardRank = "Ten";
			break;
		}
		case jack: {
			cardRank = "Jack";
			break;
		}
		case queen: {
			cardRank = "Queen";
			break;
		}
		case king: {
			cardRank = "King";
			break;
		}

		case ace: {
			cardRank = "Ace";
			break;
		}
		default: {
			cout << "Undefined rank!";
			return -4;
		}

		}
		cout << cardRank << " of " << cardSuit << endl;
	}
	return 0;
}


//Less than operator overload function for our Cards struct.
const bool operator<(const Card& first, const Card& second) {
	//We use internal integer values to asses rank.
	int firstR = (int)first.cardR;
	int secondR = (int)second.cardR;
	if (firstR == secondR) {
		//Similarly, we use internal integer values to asses suite too.
		firstR = (int)first.cardS;
		secondR = (int)second.cardS;
	}
		return firstR < secondR;
}


// Function that prints out the poker hand rank of a given vector.
int printPokerHand(vector<Card> & myV) {

	if (myV.size() % 5 != 0) {
		cout << ("unable to print! deck is not a multiple of 5");
		return -5;
	}
	//Iterating through each hand.
	vector<Pairs> allHands;
	for (vector<Card>::iterator it = myV.begin(); it != myV.end(); it += 5) {
		sort(it, it + 5);
		Pairs myP = pairCount(it);
		allHands.push_back(myP);
	}
	sort(allHands.begin(), allHands.end());

	for (const Pairs& i : allHands) {
		switch (i.handS) {
		case straightflush: {
			cout << "Straight Flush from  " << i.hVec[4].cardR << " to " << i.hVec[0].cardR <<endl;
			break;
		}
		case straight: {
			cout << "Straight from " << i.hVec[4].cardR<< " to " << i.hVec[0].cardR << endl;
			break;
		}
		case Flush: {
			cout << "Flush of " << i.hVec[0].cardS << endl;
			break;
		}
		case fourkind: {
			cout << "Four of " << i.hVec[2].cardR << endl;
			break;
		}
		case fullhouse: {
			cout << "Full House, three of " << i.hVec[i.index1].cardR << " and two of " << i.hVec[i.index2].cardR << endl;
			break;
		}
		case threekind: {
			cout << "Three of " << i.hVec[2].cardR << endl;
			break;
		}
		case twopairs: {
			cout << "Two Pairs, one of " << i.hVec[i.index1].cardR << " and another of " << i.hVec[i.index2].cardR<< endl;
			break;
		}
		case Pair: {
			cout << "Pair of " << i.hVec[i.index1].cardR << endl;
			break;
		}
		default: {
			cout << "No Rank, high card: " << i.hVec[4].cardR << endl;
		}
		}
	}


	return 0;
}
		

//Function used to count how many pairs per hand.
Pairs pairCount(vector<Card>::iterator it) {
	vector<Card> myVec(it, it + 5);
	//Vector used to count how many times each rank appears per hand.
	vector<int> freq;
	freq.push_back(0);

	int ind1 = -1;
	int ind2 = -1;
	int repeat = false; // Workaround to find the indeces.
	Score score;
	vector<Card>::iterator newIt = it; // We need this since we will be modifying our iterator, and we need to restore it later.

	//Finding the frequency of each rank in a given hand.
	Rank prev = it->cardR;
	for (int i = 0; i < 5; i++) {
		Rank elem = it->cardR;
		if (prev != elem) {
			freq.push_back(0);
			prev = elem;
			repeat = false;
		}
		if (repeat) {
			if (ind1 == -1) {
				ind1 = i-1;
			}
			else{
				ind2 = i-1;
			}
			repeat = false;
		}
		repeat = true;
		++freq.back();
		it++;
	}

	int firstPair = *(max_element(freq.begin(), freq.end()));
	freq.erase(max_element(freq.begin(), freq.end()));
	int secondPair = *(max_element(freq.begin(), freq.end()));
	
	switch (firstPair) {
	case 4: {
		score = fourkind;
		break;
	}
	case 3: {
		if (secondPair== 2) {
			score = fullhouse;
		}
		else {
			score = threekind;
		}
		break;
	}
	case 2: {
		if (secondPair == 2) {
			score=twopairs;
		}
		else {
			score=Pair;
		}
		break;
	}
	default: {
		score = norank;
	}
	}


	it = newIt; // Restoring our iterator to find if the hand is consecutive or of the same suit.
	int consecutiveRank = (int)(it->cardR) - (int)((it + 1)->cardR) + (int)((it + 1)->cardR) - (int)((it + 2)->cardR) + (int)((it + 2)->cardR) - (int)((it + 3)->cardR) + (int)((it + 3)->cardR) - (int)((it + 4)->cardR);
	bool sameSuit = (it->cardS) == ((it + 1)->cardS) && ((it->cardS) == ((it + 2)->cardS)) && ((it->cardS) == ((it + 3)->cardS)) && ((it->cardS) == ((it + 4)->cardS));


	if (consecutiveRank == -4 && sameSuit) {
		score = straightflush;
	}
	else if (consecutiveRank == -4) {
		score = straight;
	}
	else if (sameSuit) {
		score = Flush;
	}
	//Structure that holds how many pairs per hand.
	Pairs myPairs; 
	if (ind2 != -1) {
		int temp = ind2;
		ind2 = ind1;
		ind1 = temp;
	}
	myPairs.index1 = ind1;
	myPairs.index2 = ind2;
	myPairs.handS = score;
	myPairs.hVec = myVec;

	return myPairs;
}

//Less than operator overload function for our Pairs struct.
const bool operator<(const Pairs& first, const Pairs& second) {
	//We use internal integer values to asses Hand rank.
	int firstS = (int)first.handS;
	int secondS = (int)second.handS;
	if (firstS == secondS) {
		switch (firstS) {
		//No Rank case.
		case 1: {
			int firstR = (int)first.hVec[4].cardR;
			int secondR = (int)second.hVec[4].cardR;
			int i = 3;
			while (firstR == secondR) {
				firstR = (int)first.hVec[i].cardR;
				secondR = (int)second.hVec[i].cardR;
				i--;
				if (i < 0) {
					break;
				}
			}
			return firstR < secondR;
			break;
		}
		//Pair 
		case 2: {
			int firstR = (int)first.hVec[first.index1].cardR;
			int secondR = (int)second.hVec[first.index1].cardR;
			if (firstR == secondR) {
				vector<Card> firstVec(first.hVec.begin(), first.hVec.end());
				vector<Card> secondVec(second.hVec.begin(), second.hVec.end());
				firstVec.erase(firstVec.begin() + first.index1);
				secondVec.erase(secondVec.begin() + second.index1);
				int i = 1;
				firstR = firstVec[2].cardR;
				secondR = secondVec[2].cardR;
				while (firstR == secondR) {
					firstR = firstVec[i].cardR;
					secondR = secondVec[i].cardR;
					i--;
					if (i < 0) {
						break;
					}
				}
			}
			return firstR < secondR;
			break;
		}
		// Two Pairs
		case 3: {
			int firstR = (int)first.hVec[first.index1].cardR;
			int secondR = (int)second.hVec[second.index1].cardR;
			if (firstR == secondR) {
				int firstR = (int)first.hVec[first.index2].cardR;
				int secondR = (int)second.hVec[second.index2].cardR;

				if (firstR == secondR) {
					vector<Card> firstVec(first.hVec.begin(), first.hVec.end());
					vector<Card> secondVec(second.hVec.begin(), second.hVec.end());
					firstVec.erase(firstVec.begin() + first.index1);
					secondVec.erase(secondVec.begin() + second.index1);
					firstVec.erase(firstVec.begin() + first.index2);
					secondVec.erase(secondVec.begin() + second.index2);

					firstR = firstVec.back().cardR;
					secondR = secondVec.back().cardR;
				}
				return firstR < secondR;
				break;
			}
		}
		//Three of a Kind
		case 4: {
			int firstR = (int)first.hVec[first.index1].cardR;
			int secondR = (int)second.hVec[second.index1].cardR;
			return firstR < secondR;
			break;
		}
		//Straight
		case 5: {
			int firstR = (int)first.hVec.back().cardR;
			int secondR = (int)second.hVec.back().cardR;
			return firstR < secondR;
			break;
		}
		//Flush
		case 6: {
			int firstR = (int)first.hVec[4].cardR;
			int secondR = (int)second.hVec[4].cardR;
			int i = 3;
			while (firstR == secondR) {
				firstR = (int)second.hVec[i].cardR;
				secondR = (int)second.hVec[i].cardR;
				i--;
				if (i < 0) {
					break;
				}
			}
			return firstR < secondR;
			break;
		}
		//FullHouse
		case 7: {
			int firstR = (int)first.hVec[first.index1].cardR;
			int secondR = (int)second.hVec[second.index1].cardR;
			if (firstR == secondR) {
				firstR = first.hVec[first.index2].cardR;
				secondR = second.hVec[second.index2].cardR;
			}
			return firstR < secondR;
			break;
		}
		//FourKind
		case 8: {
			int firstR = (int)first.hVec[first.index1].cardR;
			int secondR = (int)second.hVec[second.index1].cardR;
			return firstR < secondR;
			break;
		}
		//StraightFlush
		case 9: {
			int firstR = (int)first.hVec[4].cardR;
			int secondR = (int)second.hVec[4].cardR;
			return firstR < secondR;
			break;
		}
		default: {
			cout << "Could not compare!" << endl;
			return -6;
		}

		}
	}
	return firstS < secondS;
}

ostream& operator<<(ostream& os, const Rank& myR)
{
	switch (myR) {
	case 2: {
		os << "Two";
		break;
	}
	case 3: {
		os << "Three";
		break;
	}
	case 4: {
		os << "Four";
		break;
	}
	case 5: {
		os << "Five";
		break;
	}
	case 6: {
		os << "Six";
		break;
	}
	case 7: {
		os << "Seven";
		break;
	}
	case 8: {
		os << "Eight";
		break;
	}
	case 9: {
		os << "Nine";
		break;
	}
	case 10: {
		os << "Ten";
		break;
	}
	case 11: {
		os << "Jack";
		break;
	}
	case 12: {
		os << "Queen";
		break;
	}
	case 13: {
		os << "King";
		break;
	}
	case 14: {
		os << "Ace";
		break;
	}
	default: {
		break;
	}
	}
	return os;
}

ostream& operator<<(ostream& os, const Suit& myR)
{
	switch (myR) {
	case 1: {
		os << "Clubs";
		break;
	}
	case 2: {
		os << "Diamonds";
		break;
	}
	case 3: {
		os << "Hearts";
		break;
	}
	case 4: {
		os << "Spades";
		break;
	}

	}
	return os;
}