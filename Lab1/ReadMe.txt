========================================================================
    CONSOLE APPLICATION : Lab1 Project Overview
========================================================================

Name: Carlos Gonzalez
Id: 434827
Lab1

Description: 
This program reads in the command line argument for a file name, opens it and reads strings from it,
and parses those strings as the definitions of cards in a standard playing deck for poker. It then identifies each set of 5 cards
as a hand and returns the ranking of each hand (Flush, Straight Flush, Pair, etcc.), which is sorted in ascending order, based on the rules of poker.
Lastly, it prints each card in the deck sorted by rank first and suite second

Implementation Explanations:
For this project, I created an additional struct called Pairs, which contains two ints, each represents a unique pair found in the hand.
I created three additional methods, "pairCount" takes in an iterator of vector<Cards> and returns the Pairs found for the next five cards starting
from that iterator. "printPokerHand" takes in a vector of Cards and sorts them according to each hand (5 cards), and prints out what 
ranking each of those hands has. Lastly, the less than operator overlading function compares cards according to rank first, then suite.

Errors and Warnings that I ran into:
I initially ran into some errors with my iterators, as I did not know if I should pass them as const or not. I quickly learned that 
whenever I was sorting my vectors I should not make the iterators const, only when I am just reading from them should I make the iterator 
const.

Additionally, working with the iterators could prove tricky at times; I would often make arithmetic errors when traversing my vectors.

Running the Program:

When I ran the program I ran it with the following input, notice that I added a couple of hands with the same rank to test:

KD JD 6s 5s 3c // no rank (king high)

QD JD 6s 5s 3c // no rank (Queen high)

6H // not a hand (too few)

Qs QH	 JH Qc Jc // full house 

10s 10H JH 10c Jc // smaller full house 

6c 10s 9H  8s  7H // straight

Jc 10s 9H  8s  7H // higher straight

AH Ks Js AD Ac // three of a kind

2H Ks Js 2D 2c // smaller three of a kind

9D  6D 5D 8D 7D // straight flush

9D  6D 10D 8D 7D // straight flush, bigger

7s 8c 2s 5H 2c // one pair

7s 8c 5s 5H 2c // higher one pair
     
Kc 3s 3D 2D 7c 5c  // not a hand (too many)

4s 4H  4D As 4c  // four of a kind

3s 3H  3D As 3c  // four of a kind

KH   10H 3H 2H 8H // flush

QD   10D 3D 2D 8D // flush

9c QD 10c 10D 9s // two pairs

Qc QD 10c 10D 9s // two pairs

I ran my program in the command line with the following command: Lab1.exe test.txt
And the output for my program was the following:
C:\Users\cgonzalezmendoza_000\Documents\Visual Studio 2015\Projects\Lab1\Debug>L
ab1.exe test.txt

Reading the cards from the input file...
Not enough cards! Cards read: 1 at line: 5
Not enough cards! Cards read: 0 at line: 26
Too many cards! Cards read: 6 at line: 28

Here are the rankings for each hand, sorted:
No Rank, high card: Queen
No Rank, high card: King
Pair of Two
Pair of Five
Two Pairs, one of Ten and another of Nine
Two Pairs, one of Queen and another of Ten
Three of Two
Three of Ace
Straight from Ten to Six
Straight from Jack to Seven
Flush of Diamonds
Flush of Hearts
Full House, three of Jack and two of Ten
Full House, three of Queen and two of Jack
Four of Three
Four of Four
Straight Flush from  Nine to Five
Straight Flush from  Ten to Six

Here is the entire sorted deck:
Two of Clubs
Two of Clubs
Two of Clubs
Two of Diamonds
Two of Diamonds
Two of Hearts
Two of Hearts
Two of Spades
Three of Clubs
Three of Clubs
Three of Clubs
Three of Diamonds
Three of Diamonds
Three of Hearts
Three of Hearts
Three of Spades
Four of Clubs
Four of Diamonds
Four of Hearts
Four of Spades
Five of Diamonds
Five of Hearts
Five of Hearts
Five of Spades
Five of Spades
Five of Spades
Six of Clubs
Six of Diamonds
Six of Diamonds
Six of Spades
Six of Spades
Seven of Diamonds
Seven of Diamonds
Seven of Hearts
Seven of Hearts
Seven of Spades
Seven of Spades
Eight of Clubs
Eight of Clubs
Eight of Diamonds
Eight of Diamonds
Eight of Diamonds
Eight of Hearts
Eight of Spades
Eight of Spades
Nine of Clubs
Nine of Diamonds
Nine of Diamonds
Nine of Hearts
Nine of Hearts
Nine of Spades
Nine of Spades
Ten of Clubs
Ten of Clubs
Ten of Clubs
Ten of Diamonds
Ten of Diamonds
Ten of Diamonds
Ten of Diamonds
Ten of Hearts
Ten of Hearts
Ten of Spades
Ten of Spades
Ten of Spades
Jack of Clubs
Jack of Clubs
Jack of Clubs
Jack of Diamonds
Jack of Diamonds
Jack of Hearts
Jack of Hearts
Jack of Spades
Jack of Spades
Queen of Clubs
Queen of Clubs
Queen of Diamonds
Queen of Diamonds
Queen of Diamonds
Queen of Diamonds
Queen of Hearts
Queen of Spades
King of Diamonds
King of Hearts
King of Spades
King of Spades
Ace of Clubs
Ace of Diamonds
Ace of Hearts
Ace of Spades
Ace of Spades

EXTRA CREDIT: 
For the extra credit I sorted each of the hands based on rules of poker. 
The extra credit portion was particularly challenging I had to create a new struct of type Pairs which is essentially a hand that contains
the vector of the Cards, the rank of the hand (pair, three of a kind, etc..) and the two indeces at which the rank begins, if needed. This
was necessary when comparing hands of the same rank.