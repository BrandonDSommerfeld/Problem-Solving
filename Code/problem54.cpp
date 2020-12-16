#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

bool better (int* hand1, int* hand2)
{
    //Rank hands based on flush/pairs/whatever
    int rank1{8};
    int rank2{8};
    /* Ranking is as follows
    0: Straight Flush
    1: Four of a kind
    2: Full house
    3: Flush
    4: Straight
    5: 3 of a kind
    6: 2 pairs
    7: pair
    8: nothing
    */

    //All cards of same suit, flush
    bool flush1{false};
    if(hand1[0]/13 == hand1[1]/13
    && hand1[0]/13 == hand1[2]/13
    && hand1[0]/13 == hand1[3]/13
    && hand1[0]/13 == hand1[4]/13)
    {
        rank1 = 3;
        flush1 =true;
    }
    bool flush2{false};
    if(hand2[0]/13 == hand2[1]/13
    && hand2[0]/13 == hand2[2]/13
    && hand2[0]/13 == hand2[3]/13
    && hand2[0]/13 == hand2[4]/13)
    {
        rank2 = 3;
        flush2 = true;
    }

    int used1[13];
    for(int i{0}; i < 13; i++)
    {
        used1[i] = 0;
    }
    int used2[13];
    for(int i{0}; i < 13; i++)
    {
        used2[i] = 0;
    }
    for(int i{0}; i < 5; i++)
    {
        used1[hand1[i] % 13]++;
        used2[hand2[i] % 13]++;
    }

    //Straight check
    int start{-1};
    for(int i{0}; i < 13 && start == -1; i++)
    {
        if(used1[i] != 0)
        {
            start = i;
        }
    }
    if(start < 9 && used1[start+1] > 0
    && used1[start+2] > 0
    && used1[start+3] > 0
    && used1[start+4] > 0 )
    {
        if(rank1 == 3)
        {
            rank1 = 0;
        }
        else
        {
            rank1 = 4;
        }
    }

    start = -1;
    for(int i{0}; i < 13 && start == -1; i++)
    {
        if(used2[i] != 0)
        {
            start = i;
        }
    }
    if(start < 9 && used2[start+1] > 0
    && used2[start+2] > 0
    && used2[start+3] > 0
    && used2[start+4] > 0 )
    {
        if(rank2 == 3)
        {
            rank2 = 0;
        }
        else
        {
            rank2 = 4;
        }
    }

    //Case on pairs/stuff
    for(int i{0}; i < 13; i++)
    {
        //Four of a kind
        if(used1[i] == 4)
        {
            rank1 = 1;
        }
        if(used2[i] == 4)
        {
            rank2 = 1;
        }

        if(used1[i] == 3)
        {
            //Full house check
            if(rank1 == 7)
            {
                rank1 = 2;
            }
            else
            {
                rank1 = 5;
            }
        }

        if(used2[i] == 3)
        {
            if(rank2 == 7)
            {
                rank2 = 2;
            }
            else
            {
                rank2 = 5;
            }
        }

        if(used1[i] == 2)
        {   
            //2 Pairs
            if(rank1 == 7)
            {
                rank1 = 6;
            }
            //Full house
            else if (rank1 == 5)
            {
                rank1 = 2;
            }
            else
            {
                rank1 = 7;
            }
        }

        if(used2[i] == 2)
        {   
            //2 Pairs
            if(rank2 == 7)
            {
                rank2 = 6;
            }
            //Full house
            else if (rank2 == 5)
            {
                rank2 = 2;
            }
            else
            {
                rank2 = 7;
            }
        }
    }
    if(flush1 && rank2 > 3) return true;
    if(flush2 && rank1 > 3) return false;
    if(rank1 < rank2)
    {
        return true;
    }
    if(rank2 < rank1) return false;

    //Tiebreaker by highest card
    if(rank1 == 8)
    {
        for(int i{12}; i >= 0; i--)
        {
            if(used1[i] > used2[i])
            {
                return true;
            }
            else if (used1[i] < used2[i])
            {
                return false;
            }
        }
    }
    if(rank1 == 7 || rank1 == 6)
    {
        for(int i{12}; i >= 0; i--)
        {
            if(used1[i] == 2 && used2[i] < 2) return true;
            if(used2[i] == 2 && used1[i] < 2) return false;
        }
        for(int i{12}; i >= 0; i--)
        {
            if(used1[i] > used2[i])
            {
                return true;
            }
            else if (used1[i] < used2[i])
            {
                return false;
            }
        }
    }
    return true;
}

int main ()
{
    //In the file p054_poker.txt, there are lines with lots of poker
    //hands. Determine how many the first player wins
    std::ifstream inf{"p054_poker.txt"};
    if(!inf)
    {
        std::cout << "Couldn't find file\n";
        return 1;
    }
    //Absolutely awful and tedious to do all the cases in above function
    int wins{0};
    for(int i{0}; i < 1000; i++)
    {
        std::string input{};
        std::getline(inf, input);
        int hand1[5];
        int hand2[5];
        for(int i{0}; i < 10; i++)
        {
            char rank = input[i*3];
            char suit = input[3*i + 1];

            int value{0};
            switch(rank)
            {
                case 'T':
                    value = 8;
                    break;
                case 'J':
                    value = 9;
                    break;
                case 'Q':
                    value = 10;
                    break;
                case 'K':
                    value = 11;
                    break;
                case 'A':
                    value = 12;
                    break;
                default:
                    value = rank-50;
                    break;
            }
            int s{0};
            switch(suit)
            {
                case 'D':
                    s = 1;
                    break;
                case 'H':
                    s = 2;
                    break;
                case 'S':
                    s = 3;
                    break;
            }
            int card = s*13+value;
            if(i < 5)
            {
                hand1[i] = card;
            }
            else
            {
                hand2[i-5] = card;
            }
        }
        
        if(better(hand1, hand2))
        {
            wins++;
        }
    }
    std::cout << wins << '\n';
    return 0;
}