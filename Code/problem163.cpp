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

static constexpr int len = 2;
static constexpr int maxRow = 4*len;
static constexpr int maxCol = 4*len;
static constexpr int mid = 2*len;

static bool**** connected;

//The various directions that lines can go, measured from 
//the negative x axis
enum class direction
{
    THIRTY,
    SIXTY,
    NINETY,
    ONETWENTY,
    ONEFIFTY,
    STRAIGHT
};

bool inBounds(int row, int col)
{
    if(row > maxRow) return false;
    switch(row % 4)
    {
        //Points on the sides of a triangle
        case 0:
        case 2:
        return (col >= mid-row/2) && (col <= mid+row/2);
        //Points in the center of an upside down triangle
        case 1:
        return (col >= mid-row/2+2) && (col <= mid+row/2);
        //Points in the center of right side up triangles
        default:
        return (col >= mid - row/2 + 1) && (col <= mid+row/2);
    }
}

bool lineBetween (int row1, int col1, int row2, int col2)
{
    return connected[row1][col1][row2][col2];
}

unsigned long long helper(int row1, int col1, direction d1, direction d2, 
bool firstDirection, int row2, int col2)
{
    unsigned long long total = 0;
    switch(firstDirection ? d1 : d2)
    {
        case direction::THIRTY:
        {
            int row = row1;
            int col = col1;
            while(inBounds(row, col))
            {
                //Don't count degenerate triangles
                if(row != row1)
                {   
                    if(firstDirection)
                    {
                        total += helper(row1, col1, d1, d2, false, row, col);
                    }
                    else if (lineBetween(row, col, row2, col2))
                    {
                        total++;
                        std::cout << "Yes " << row << ' ' << col << ' '  << row1 << ' ' << col1 << 
                        ' ' << row2 << ' ' << col2 << '\n';
                    }
                    else
                    {
                        std::cout << "No " << row << ' ' << col << ' '  << row1 << ' ' << col1 << 
                        ' ' << row2 << ' ' << col2 << '\n';
                    }
                }
                switch(row % 4)
                {
                    case 0:
                    case 3:
                    row++;
                    col -= 2;
                    break;
                    default:
                    row++;
                    col--;
                    break;
                }
            }
        }
        break;
        case direction::SIXTY:
        {
            int row = row1;
            int col = col1;
            while(inBounds(row, col))
            {
                if(row != row1)
                {
                    if(firstDirection)
                    {
                        total += helper(row1, col1, d1, d2, false, row, col);
                    }
                    else if (lineBetween(row, col, row2, col2))
                    {
                        total++;
                        std::cout << "Yes " << row << ' ' << col << ' '  << row1 << ' ' << col1 << 
                        ' ' << row2 << ' ' << col2 << '\n';
                    }
                    else
                    {
                        std::cout << "No " << row << ' ' << col << ' '  << row1 << ' ' << col1 << 
                        ' ' << row2 << ' ' << col2 << '\n';
                    }
                }
                row += 2;
                col--;
            }
        }
        break;
        case direction::NINETY:
        {
            int row = row1;
            int col = col1;
            while(inBounds(row, col))
            {
                if(row != row1)
                {
                    if(firstDirection)
                    {
                        total += helper(row1, col1, d1, d2, false, row, col);
                    }
                    else if (lineBetween(row, col, row2, col2))
                    {
                        total++;
                        std::cout << "Yes " << row << ' ' << col << ' '  << row1 << ' ' << col1 << 
                        ' ' << row2 << ' ' << col2 << '\n';
                    }
                    else
                    {
                        std::cout << "No " << row << ' ' << col << ' '  << row1 << ' ' << col1 << 
                        ' ' << row2 << ' ' << col2 << '\n';
                    }
                }
                //Have to act differently based on the column, because in 
                //some you have an upside down triangle, and some 
                //you have a right side up one

                //Most likely to be wrong here
                switch(2*(row%8) + ((col-mid) % 4)/2)
                {
                    case 0:
                    case 3:
                    case 9:
                    case 10:
                    row += 3;
                    break;
                    default:
                    row++;
                    break;
                }
            }
        }
        break;
        case direction::ONETWENTY:
        {
            int row = row1;
            int col = col1;
            while(inBounds(row, col))
            {
                if(row != row1)
                {
                    if(firstDirection)
                    {
                        total += helper(row1, col1, d1, d2, false, row, col);
                    }
                    else if (lineBetween(row, col, row2, col2))
                    {
                        total++;
                        std::cout << "Yes " << row << ' ' << col << ' '  << row1 << ' ' << col1 << 
                        ' ' << row2 << ' ' << col2 << '\n';
                    }
                    else
                    {
                        std::cout << "No " << row << ' ' << col << ' '  << row1 << ' ' << col1 << 
                        ' ' << row2 << ' ' << col2 << '\n';
                    }
                }
                row += 2;
                col++;
            }
        }
        break;
        case direction::ONEFIFTY:
        {
            int row = row1;
            int col = col1;
            while(inBounds(row, col))
            {
                //Don't count degenerate triangles
                if(row != row1)
                {
                    if(firstDirection)
                    {
                        total += helper(row1, col1, d1, d2, false, row, col);
                    }
                    else if (lineBetween(row, col, row2, col2))
                    {
                        total++;
                        std::cout << "Yes " << row << ' ' << col << ' '  << row1 << ' ' << col1 << 
                        ' ' << row2 << ' ' << col2 << '\n';
                    }
                    else
                    {
                        std::cout << "No " << row << ' ' << col << ' '  << row1 << ' ' << col1 << 
                        ' ' << row2 << ' ' << col2 << '\n';
                    }
                }
                switch(row % 4)
                {
                    case 0:
                    case 3:
                    row++;
                    col += 2;
                    break;
                    default:
                    row++;
                    col++;
                    break;
                }
            }
        }
        break;
        //Straight line
        default:
        {
            int row = row1;
            int col = col1;
            while(inBounds(row, col))
            {
                //Don't count degenerate triangles
                if(col != col1)
                {
                    if(firstDirection)
                    {
                        total += helper(row1, col1, d1, d2, false, row, col);
                    }
                    else if (lineBetween(row, col, row2, col2))
                    {
                        total++;
                        std::cout << "Yes " << row << ' ' << col << ' '  << row1 << ' ' << col1 << 
                        ' ' << row2 << ' ' << col2 << '\n';
                    }
                    else
                    {
                        std::cout << "No " << row << ' ' << col << ' '  << row1 << ' ' << col1 << 
                        ' ' << row2 << ' ' << col2 << '\n';
                    }
                }
                col += 2;
            }
        }
        break;
    }
    return total;
}

void helper2(int row1, int col1, direction d1)
{
    switch(d1)
    {
        case direction::THIRTY:
        {
            int row = row1;
            int col = col1;
            while(inBounds(row, col))
            {
                //Don't count degenerate triangles
                if(row != row1)
                {   
                    connected[row][col][row1][col1] = true;
                    connected[row1][col1][row][col] = true;
                }
                switch(row % 4)
                {
                    case 0:
                    case 3:
                    row++;
                    col -= 2;
                    break;
                    default:
                    row++;
                    col--;
                    break;
                }
            }
        }
        break;
        case direction::SIXTY:
        {
            int row = row1;
            int col = col1;
            while(inBounds(row, col))
            {
                if(row != row1)
                {
                    connected[row][col][row1][col1] = true;
                    connected[row1][col1][row][col] = true;
                }
                row += 2;
                col--;
            }
        }
        break;
        case direction::NINETY:
        {
            int row = row1;
            int col = col1;
            while(inBounds(row, col))
            {
                if(row != row1)
                {
                    connected[row][col][row1][col1] = true;
                    connected[row1][col1][row][col] = true;
                }
                //Have to act differently based on the column, because in 
                //some you have an upside down triangle, and some 
                //you have a right side up one

                //Most likely to be wrong here
                switch(2*(row%8) + ((col-mid) % 4)/2)
                {
                    case 0:
                    case 3:
                    case 9:
                    case 10:
                    row += 3;
                    break;
                    default:
                    row++;
                    break;
                }
            }
        }
        break;
        case direction::ONETWENTY:
        {
            int row = row1;
            int col = col1;
            while(inBounds(row, col))
            {
                if(row != row1)
                {
                    connected[row][col][row1][col1] = true;
                    connected[row1][col1][row][col] = true;
                }
                row += 2;
                col++;
            }
        }
        break;
        case direction::ONEFIFTY:
        {
            int row = row1;
            int col = col1;
            while(inBounds(row, col))
            {
                //Don't count degenerate triangles
                if(row != row1)
                {
                    connected[row][col][row1][col1] = true;
                    connected[row1][col1][row][col] = true;
                }
                switch(row % 4)
                {
                    case 0:
                    case 3:
                    row++;
                    col += 2;
                    break;
                    default:
                    row++;
                    col++;
                    break;
                }
            }
        }
        break;
        //Straight line
        default:
        {
            int row = row1;
            int col = col1;
            while(inBounds(row, col))
            {
                
                //Don't count degenerate triangles
                if(col != col1)
                {
                    connected[row][col][row1][col1] = true;
                    connected[row1][col1][row][col] = true;
                }
                col += 2;
            }
        }
        break;
    }
}

void generate (int row, int col, std::vector<direction> d)
{
    for(size_t i = 0; i < d.size(); i++)
    {
        helper2(row, col, d[i]);
    }
}

unsigned long long count (int row, int col, std::vector<direction> directions)
{
    unsigned long long total = 0;
    for(size_t i = 1; i < directions.size(); i++)
    {
        for(size_t j = 0; j < i; j++)
        {
            total += helper(row, col, directions[i], directions[j], true, 0, 0);
        }
    }
    return total;
}


int main ()
{
    //Consider an equilateral triangle with lines drawn from each vertex to the midpoint
    //If we consider these lines, there are 16 different triangles 
    //which can be selected from within this

    //Then consider stacking these triangles into larger equilateral triangles
    //If the starting triangle has side length 1, stack them until you have
    //an equilateral triangle with side length 36
    //Find the number of sub triangles within this

    //Number the rows and columns of the triangle
    //Rows start at the top, columns start at the left
    //Then the next row or column is the next line where points occur

    connected = (bool****) calloc(sizeof(bool***), maxRow+1);
    for(int i = 0; i <= maxRow; i++)
    {
        connected[i] = (bool***) calloc(sizeof(bool**), maxCol+1);
        for(int j = 0; j <= maxCol; j++)
        {
            connected[i][j] = (bool**) calloc(sizeof(bool*), maxRow+1);
            for(int k = 0; k <= maxRow; k++)
            {
                connected[i][j][k] = (bool*) calloc(sizeof(bool), maxCol+1);
            }
        }
    }
    unsigned long long total = 0;
    for(int row = 0; row <= maxRow; row++)
    {
        switch(row % 4)
        {
            //Points on the top/bottom of a triangle
            case 0:
            for(int col = mid-row/2; col <= mid+row/2; col+= 2)
            {
                std::vector<direction> directions{};
                if(row == maxRow)
                {
                    directions.push_back(direction::STRAIGHT);
                }
                else if ((col - (mid - row/2)) % 4 == 0)
                {
                    directions.push_back(direction::SIXTY);
                    directions.push_back(direction::NINETY);
                    directions.push_back(direction::ONETWENTY);
                    if(col != mid+row/2)
                    {
                        directions.push_back(direction::ONEFIFTY);
                        directions.push_back(direction::STRAIGHT);
                    }
                    if(col != mid-row/2)
                    {
                        directions.push_back(direction::THIRTY);
                    }
                }
                else
                {
                    directions.push_back(direction::STRAIGHT);
                    directions.push_back(direction::NINETY);
                }
                generate(row, col, directions);
            }
            break;
            //Points in the center of an upside down triangle
            case 1:
            for(int col = mid-row/2+2; col <= mid+row/2; col += 4)
            {
                std::vector<direction> directions{};
                directions.push_back(direction::THIRTY);
                directions.push_back(direction::NINETY);
                directions.push_back(direction::ONEFIFTY);
                generate(row, col, directions);
            }
            break;
            //Points on the midpoints of sides
            case 2:
            for(int col = mid-row/2; col <= mid+row/2; col += 2)
            {
                std::vector<direction> directions{};
                if((col - (mid-row/2)) % 4 == 0)
                {
                    directions.push_back(direction::SIXTY);
                    directions.push_back(direction::ONEFIFTY);
                }
                else
                {
                    directions.push_back(direction::THIRTY);
                    directions.push_back(direction::ONETWENTY);
                }
                generate(row, col, directions);
            }
            break;
            //Points in the center of right side up triangles
            default:
            for(int col = mid -row/2+1; col <= mid+row/2; col += 4)
            {
                std::vector<direction> directions{};
                directions.push_back(direction::THIRTY);
                directions.push_back(direction::NINETY);
                directions.push_back(direction::ONEFIFTY);
                generate(row, col, directions);
            }
            break;
        }
    }
    
    for(int row = 0; row < maxRow; row++)
    {
        switch(row % 4)
        {
            //Points on the top/bottom of a triangle
            case 0:
            for(int col = mid-row/2; col <= mid+row/2; col+= 2)
            {
                std::vector<direction> directions{};
                if ((col - (mid - row/2)) % 4 == 0)
                {
                    directions.push_back(direction::SIXTY);
                    directions.push_back(direction::NINETY);
                    directions.push_back(direction::ONETWENTY);
                    if(col != mid+row/2)
                    {
                        directions.push_back(direction::ONEFIFTY);
                        directions.push_back(direction::STRAIGHT);
                    }
                    if(col != mid-row/2)
                    {
                        directions.push_back(direction::THIRTY);
                    }
                }
                else
                {
                    directions.push_back(direction::STRAIGHT);
                    directions.push_back(direction::NINETY);
                }
                total += count(row, col, directions);
            }
            break;
            //Points in the center of an upside down triangle
            case 1:
            for(int col = mid-row/2+2; col <= mid+row/2; col += 4)
            {
                std::vector<direction> directions{};
                directions.push_back(direction::THIRTY);
                directions.push_back(direction::NINETY);
                directions.push_back(direction::ONEFIFTY);
                total += count(row, col, directions);
            }
            break;
            //Points on the midpoints of sides
            case 2:
            for(int col = mid-row/2; col <= mid+row/2; col += 2)
            {
                std::vector<direction> directions{};
                if((col - (mid-row/2)) % 4 == 0)
                {
                    directions.push_back(direction::SIXTY);
                    directions.push_back(direction::ONEFIFTY);
                }
                else
                {
                    directions.push_back(direction::THIRTY);
                    directions.push_back(direction::ONETWENTY);
                }
                total += count(row, col, directions);
            }
            break;
            //Points in the center of right side up triangles
            default:
            for(int col = mid -row/2+1; col <= mid+row/2; col += 4)
            {
                std::vector<direction> directions{};
                directions.push_back(direction::THIRTY);
                directions.push_back(direction::NINETY);
                directions.push_back(direction::ONEFIFTY);
                total += count(row, col, directions);
            }
            break;
        }
    }
    std::cout << total << '\n';
    return 0;
}