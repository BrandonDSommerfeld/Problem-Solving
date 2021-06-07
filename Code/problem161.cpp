#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <random>
#include <chrono>
#include <queue>
#include <list>
#include "math_unsigned.cpp"
#include "math_signed.cpp"
#include "math_rational.cpp"
#include "math_fast_rational.cpp"
#include "algorithms.cpp"

static inline bool filled(unsigned int board, unsigned int pos)
{
  return (board >> pos) & 1;
}

static inline unsigned int flip(unsigned int board, unsigned int pos)
{
  return board ^ (1 << pos);
}

struct pair 
{
  unsigned int current;
  unsigned int next;
};

std::string binary (unsigned int num)
{
  std::string ans{};
  for(int i = 0; i < 18; i++)
  {
    if(num % 2 == 0)
    {
      ans = '0' + ans;
    }
    else
    {
      ans = '1' + ans;
    }
    num /= 2;
    if(i == 8)
    {
      ans = '\n' + ans;
    }
  }
  return ans + '\n';
}

int main ()
{
  //Consider dominoes which consist of 3 squares, triominoes. They are either 3 squares long, or 
  //form an L shape

  //How many ways can a 9 x 12 grid be tiled by these triominoes?
  
  //Advance to the left:
  //Begin with a completely empty board, and try to fill in the left column which has 9 rows
  //Then keep track of the effect this has on the 2 rows to the right of it,
  //Then move over a column and try to fill those columns in 
  
  //Keep track of boards using integers: The lowest 18 bits are 1 if the square is 
  //occupied, and 0 if it is empty
  
  //Total number of possible arrangements for 2 columns
  unsigned int numWays = 1 << 18;
  //Keep track of how many ways each arrangement can be formed
  unsigned long long* numEach = (unsigned long long*) calloc(sizeof(unsigned long long), numWays);

  //Begin with 1 way to form the empty board by placing nothing
  numEach[0] = 1;
  //Advance and fill in all 12 columns
  for(int i = 0; i < 12; i++)
  {
    unsigned long long* temp = (unsigned long long*) calloc(sizeof(unsigned long long), numWays);
    for(unsigned int j = 0; j < numWays; j++)
    {
      //Save time, only explore a board if it possible to reach
      if(numEach[j] != 0)
      {
        std::vector<pair>* possible = new std::vector<pair>{};
        //Begin with the current board
        //Current includes the current column, and 1 to the right
        //Next is the next 2 columns, so we copy over the right column of current
        pair temp1{};
        temp1.current = j;
        temp1.next = j >> 9;
        possible->push_back(temp1);
        //For each row, look at the boards we can possibly reach, and 
        //try to fill them in
        for(unsigned int row = 0; row < 9; row++)
        {
          std::vector<pair>* n = new std::vector<pair>{};
          for(size_t k = 0; k < possible->size(); k++)
          {
            unsigned int current = (*possible)[k].current;
            unsigned int next = (*possible)[k].next;
            //If the current square is not filled, it needs to be filled somehow
            //When we are done, the entire column should be filled in
            if(!filled(current, row))
            {
              //Place a horizontal piece
              if(!filled(current, row+9))
              {
                pair temp2{};
                temp2.current = flip(flip(current, row), row+9);
                temp2.next = flip(flip(next, row), row+9);
                n->push_back(temp2);
              }
              //Place a vertical piece
              if(row < 7 && !filled(current, row+1) && !filled(current, row+2))
              {
                pair temp2{};
                temp2.current = flip(flip(flip(current, row), row+1), row+2);
                temp2.next = next;
                n->push_back(temp2);
              }
              //Place an L shaped piece
              if(row < 8 && !filled(current, row+1))
              {
                pair temp2{};
                //row+10 check ommitted because there is no way for it to be filled yet
                temp2.current = flip(flip(flip(current, row), row+1), row+10);
                temp2.next = flip(next, row+1);
                n->push_back(temp2);
              }
              //Place an r shaped piece
              if(row < 8 && !filled(current, row+1) && !filled(current, row+9))
              {
                pair temp2{};
                temp2.current = flip(flip(flip(current, row), row+1), row+9);
                temp2.next = flip(next, row);
                n->push_back(temp2);
              }
              //Place a backwards L shaped piece
              if(row > 0 && !filled(current, row+8) && !filled(current, row+9))
              {
                pair temp2{};
                temp2.current = flip(flip(flip(current, row), row+8), row+9);
                temp2.next = flip(flip(next, row-1), row);
                n->push_back(temp2);
              }
              //Place a backwards r shaped piece
              if(row < 8 && !filled(current, row+9) && !filled(current, row+10))
              {
                pair temp2{};
                temp2.current = flip(flip(flip(current, row), row+9), row+10);
                temp2.next = flip(flip(next, row), row+1);
                n->push_back(temp2);
              }
            }
            //If the square wasn't filled, we just leave it and move onto the next one
            else
            {
              n->push_back((*possible)[k]);
            }
            
          }
          delete possible;
          possible = n;
        }
        //For each board that we can reach from the current, add to the number 
        //of ways it can be formed
        for(size_t k = 0; k < possible->size(); k++)
        {
          temp[(*possible)[k].next] += numEach[j];
        }
      }      
    }
    free(numEach);
    numEach = temp;
  }

  //Look at 0, because after filling in all 12 columns, the next 
  //2 columns should have nothing, because we can't go beyond the end of the board
  std::cout << numEach[0] << '\n';
  free(numEach);
  return 0;
}