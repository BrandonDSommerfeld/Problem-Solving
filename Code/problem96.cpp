#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <random>
#include <chrono>
#include <set>
#include <queue>
#include "math_unsigned.cpp"



std::vector<int>* remove(std::vector<int>* nums, int elem)
{
    //Remove an element, if it is present, and
    //return a vector with it removed
    std::vector<int> *temp = new std::vector<int>{};
    for(int i = 0; i < nums->size(); i++)
    {
        if((*nums)[i] != elem)
        {
            temp->push_back((*nums)[i]);
        }
    }
    delete nums;
    return temp;
}

bool contains(std::vector<int>* nums, int elem)
{
    for(int i = 0; i < nums->size(); i++)
    {
        if((*nums)[i] == elem)
        {
            return true;
        }
    }
    return false;
}

void freeGrid(std::vector<int> ***grid)
{
    for(int i = 0 ; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            delete grid[i][j];
        }
        delete[] grid[i];
    }
    delete [] grid;
}

bool noSolutions(std::vector<int> ***grid)
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(grid[i][j]->size() == 0)
            {
                return true;
            }
        }
    }
    return false;
}

int solve(int **input)
{
    std::vector<int> ***grid = new std::vector<int>**[9];
    for(int i = 0; i < 9; i++)
    {
        grid[i] = new std::vector<int>*[9];
        for(int j = 0; j < 9; j++)
        {
            std::vector<int> *temp = new std::vector<int>{};
            for(int n = 1; n < 10; n++)
            {
                temp->push_back(n);
            }
            grid[i][j] = temp;
        }
    }
    std::queue<int> queue{};
    bool done[9][9];
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            done[i][j] = false;
            if(input[i][j] != 0)
            {
                done[i][j] = true;
                queue.push(9*i+j);
                delete grid[i][j];
                grid[i][j] = new std::vector<int>{};
                grid[i][j]->push_back(input[i][j]);
            }
        }
    }
    while(!queue.empty())
    {
        int loc = queue.front();
        queue.pop();
        int row = loc/9;
        int col = loc % 9;
        done[row][col] = true;
        //Remove all penciled in numbers in same col
        for(int r = 0; r < 9; r++)
        {
            if(r != row)
            {
                grid[r][col] = remove(grid[r][col], (*grid[row][col])[0]);
            }
        }
        if(noSolutions(grid))
        {
            freeGrid(grid);
            return 0;
        }
        //Remove in col
        for(int c = 0; c < 9; c++)
        {
            if(c != col)
            {
               grid[row][c] = remove(grid[row][c], (*grid[row][col])[0]);
            }
        }
        if(noSolutions(grid))
        {
            freeGrid(grid);
            return 0;
        }
        
        //Remove in same square
        for(int r = 0; r < 3; r++)
        {
            for(int c = 0; c < 3; c++)
            {
                if((row/3)*3+r != row || (col/3)*3+c != col)
                {
                    grid[(row/3)*3+r][(col/3)*3+c] = remove(grid[(row/3)*3+r][(col/3)*3+c], (*grid[row][col])[0]);
                }
            }
        }
        if(noSolutions(grid))
        {
            freeGrid(grid);
            return 0;
        }
        
        //If a number only appears once in a column, place it there
        for(int c = 0; c < 9; c++)
        {
            for(int num = 1; num < 10; num++)
            {
                int place = -1;
                bool works = true;
                for(int r = 0; r < 9 && works; r++)
                {
                    if(contains(grid[r][c], num))
                    {
                        if(place == -1)
                        {
                            place = r;
                        }
                        else
                        {
                            works = false;
                        }
                        
                    }
                }
                if(works)
                {
                    if(!done[place][c])
                    {
                        std::vector<int> *temp = new std::vector<int>{};
                        grid[place][c] = temp;
                        grid[place][c]->push_back(num);
                        done[place][c] = true;
                    }
                }
            }
        }
        if(noSolutions(grid))
        {
            freeGrid(grid);
            return 0;
        }
        
        //If a number only appears once in a row, place it there
        for(int r = 0; r < 9; r++)
        {
            for(int num = 1; num < 10; num++)
            {
                int place = -1;
                bool works = true;
                for(int c = 0; c < 9 && works; c++)
                {
                    if(contains(grid[r][c], num))
                    {
                        if(place == -1)
                        {
                            place = c;
                        }
                        else
                        {
                            works = false;
                        }
                        
                    }
                }
                if(works)
                {
                    if(!done[r][place])
                    {
                        std::vector<int> *temp = new std::vector<int>{};
                        grid[r][place] = temp;
                        grid[r][place]->push_back(num);
                        done[r][place] = true;
                    }
                }
            }
        }
        if(noSolutions(grid))
        {
            freeGrid(grid);
            return 0;
        }
    
        //If a number only appears once in a square, place it there

        for(int r = 0; r < 3; r++)
        {
            for(int c = 0; c < 3; c++)
            {
                for(int num = 1; num < 10; num++)
                {
                    int place = -1;
                    bool works = true;
                    for(int r1 = 0; r1 < 3 && works; r1++)
                    {
                        for(int c1 = 0; c1 < 3; c1++)
                        {  
                            if(contains(grid[3*r+r1][3*c+c1], num))
                            {
                                if(place == -1)
                                {
                                    place = 9*(3*r+r1)+3*c+c1;
                                }
                                else
                                {
                                    works = false;
                                }
                                
                            }
                        }
                    }
                    if(works)
                    {
                        if(!done[place/9][place%9])
                        {
                            std::vector<int> *temp = new std::vector<int>{};
                            grid[place/9][place%9] = temp;
                            grid[place/9][place%9]->push_back(num);
                            done[place/9][place%9] = true;
                        }
                    }
                }
            }
        }
        if(noSolutions(grid))
        {
            freeGrid(grid);
            return 0;
        }
        //If a number only appears in a single row of a square,
        //remove that number from the row in other squares
        for(int r = 0; r < 3; r++)
        {
            for(int c = 0; c < 3; c++)
            {
                for(int num = 1; num < 10; num++)
                {
                    int place = -1;
                    bool oneRow = true;
                    for(int r1 = 0; r1 < 3; r1++)
                    {
                        for(int c1 = 0; c1 < 3; c1++)
                        {
                            if(contains(grid[r*3+r1][c*3+c1], num))
                            {
                                if(place == -1 || r1 == place)
                                {
                                    place = r1;
                                }
                                else
                                {
                                    oneRow = false;
                                }
                            }
                        }
                    }
                    if(oneRow && place != -1)
                    {
                        for(int c1 = 0; c1 < 9; c1++)
                        {
                            if(c1/3 != c)
                            {
                                grid[r*3+place][c1] = remove(grid[r*3+place][c1], num);
                            }
                        }
                    }

                    place = -1;
                    bool oneCol = true;
                    for(int r1 = 0; r1 < 3; r1++)
                    {
                        for(int c1 = 0; c1 < 3; c1++)
                        {
                            if(contains(grid[r*3+r1][c*3+c1], num))
                            {
                                if(place == -1 || c1 == place)
                                {
                                    place = c1;
                                }
                                else
                                {
                                    oneCol = false;
                                }
                                
                            }
                        }
                    }
                    if(oneCol && place != -1)
                    {
                        for(int r1 = 0; r1 < 9; r1++)
                        {
                            if(r1/3 != r)
                            {
                                grid[r1][c*3+place] = remove(grid[r1][c*3+place], num);
                            }
                        }
                    }
                }
            }
        }
        if(noSolutions(grid))
        {
            freeGrid(grid);
            return 0;
        }
        //If the only times a number occurs is in one square, 
        //that number must be in that row of the square, and
        //remove the other instances
        for(int r = 0; r < 9; r++)
        {
            for(int num = 1; num < 10; num++)
            {
                int place = -1;
                bool oneSquare = true;
                for(int c = 0; c < 9; c++)
                {
                    if(contains(grid[r][c], num))
                    {
                        if(place == -1 || c/3 == place)
                        {
                            place = c/3;
                        }
                        else
                        {
                            oneSquare = false;
                        }
                    }
                }
                if(oneSquare && place != -1)
                {
                    for(int r1 = 0; r1 < 3; r1++)
                    {
                        for(int c1 = 0; c1 < 3; c1++)
                        {
                            if(r/3*3+r1 != r)
                            {
                                grid[r/3*3+r1][place*3+c1] = remove(grid[r/3*3+r1][place*3+c1], num);
                            }
                        }
                    }
                }
            }
        }
        if(noSolutions(grid))
        {
            freeGrid(grid);
            return 0;
        }
        for(int c = 0; c < 9; c++)
        {
            for(int num = 1; num < 10; num++)
            {
                int place = -1;
                bool oneSquare = true;
                for(int r = 0; r < 9; r++)
                {
                    if(contains(grid[r][c], num))
                    {
                        if(place == -1 || r/3 == place)
                        {
                            place = r/3;
                        }
                        else
                        {
                            oneSquare = false;
                        }
                    }
                }
                if(oneSquare && place != -1)
                {
                    for(int r1 = 0; r1 < 3; r1++)
                    {
                        for(int c1 = 0; c1 < 3; c1++)
                        {
                            if(c/3*3+c1 != c)
                            {
                                grid[place*3+r1][c/3*3+c1] = remove(grid[place*3+r1][c/3*3+c1], num);
                            }
                        }
                    }
                }
            }
        }
        if(noSolutions(grid))
        {
            freeGrid(grid);
            return 0;
        }
        
        //Check if any squares have just 1 number left
        for(int r = 0; r < 9; r++)
        {
            for(int c = 0; c < 9; c++)
            {
                if(grid[r][c]->size() == 1 && !done[r][c])
                {
                    done[r][c] = true;
                    queue.push(9*r+c);
                }
            }
        }
    }
    //Check whether we have a solution or not
    int lowest = 10;
    int place = -1;
    for(int r = 0; r < 9; r++)
    {
        for(int c = 0; c < 9; c++)
        {
            if(grid[r][c]->size() != 1)
            {
                if(grid[r][c]->size() < lowest)
                {
                    lowest = grid[r][c]->size();
                    place = r*9+c;
                }
            }
        }
    }
    if(place != -1)
    {
        //If there is no solution, just guess and check on a square
        int** boi = new int*[9];
        for(int i = 0; i < 9; i++)
        {
            boi[i] = new int[9];
            for(int j = 0; j < 9; j++)
            {
                if(grid[i][j]->size() == 1)
                {
                    boi[i][j] = (*grid[i][j])[0];
                }
                else
                {
                    boi[i][j] = 0;
                }
            }
        }

        for(int i = 0; i < grid[place/9][place%9]->size(); i++)
        {
            boi[place/9][place%9] = (*grid[place/9][place%9])[i];
            int ans = solve(boi);
            if(ans != 0)
            {
                return ans;
            }
        }
    }
    return (*grid[0][0])[0]*100 + (*grid[0][1])[0]*10+(*grid[0][2])[0];
}

int main ()
{
    //Has a text file with a number of sudokus
    //Solve them, then compute the sum of the 3 digit numbers
    //in the top left corner
    //Answer: 24702
    //This code is correct, but I think has some undefined behavior?

    std::ifstream inf{"p096_sudoku.txt"};
    if(!inf)
    {
        std::cout << "Couldn't find file\n";
        return 1;
    }

    int total = 0;
    for(int i = 0; i < 50; i++)
    {
        std::string in{};
        std::getline(inf, in);
        int **grid = new int*[9];
        for(int j = 0; j < 9; j++)
        {
            grid[j] = new int[9];
            std::getline(inf, in);
            for(int k = 0; k < 9; k++)
            {
                grid[j][k] = in[k]-48;
            }
        }
        total += solve(grid);
    }
    std::cout << total << '\n';
    return 0;
}