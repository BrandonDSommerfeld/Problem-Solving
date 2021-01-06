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
#include "math_signed.cpp"

static std::vector<int*> pair3;
static std::vector<int*> pair4;
static std::vector<int*> pair5;
static std::vector<int*> pair6;


bool works (int *set1, int *set2, int size)
{
    if(set1[0] > set2[0])
    {
        return false;
    }
    for(int i = 1; i < size; i++)
    {
        if(set1[i] > set2[i])
        {
            return true;
        }
    }
    return false;
}

void generate ()
{
    int *test1 = new int[6];
    for(int i = 0; i < 6; i++)
    {
        test1[i] = i+1;
    }
    for(int num1 = 0; num1 < 6; num1++)
    {
        for(int num2 = num1+1; num2 < 6; num2++)
        {
            for(int num3 = num2+1; num3 < 6; num3++)
            {
                int set1[3];
                int set2[3];
                set1[0] = test1[num1];
                set1[1] = test1[num2];
                set1[2] = test1[num3];
                int used = 0;
                for(int i = 0; i < 6; i++)
                {
                    if(i != num1 && i != num2 && i != num3)
                    {
                        set2[used] = test1[i];
                        used++;
                    }
                }
                if(works(set1, set2, 3))
                {
                    int *temp = new int[6];
                    for(int i = 0; i < 3; i++)
                    {
                        temp[i] = set1[i];
                        temp[i+3] = set2[i];
                    }
                    pair3.push_back(temp);
                }
            }
        }
    }
    delete[] test1;
    test1 = new int[8];
    for(int i = 0; i < 8; i++)
    {
        test1[i] = i+1;
    }
    for(int num1 = 0; num1 < 8; num1++)
    {
        for(int num2 = num1+1; num2 < 8; num2++)
        {
            for(int num3 = num2+1; num3 < 8; num3++)
            {
                for(int num4 = num3+1; num4 < 8; num4++)
                {
                    int set1[4];
                    int set2[4];
                    set1[0] = test1[num1];
                    set1[1] = test1[num2];
                    set1[2] = test1[num3];
                    set1[3] = test1[num4];
                    int used = 0;
                    for(int i = 0; i < 8; i++)
                    {
                        if(i != num1 && i != num2 && i != num3
                        && i != num4)
                        {
                            set2[used] = test1[i];
                            used++;
                        }
                    }
                    if(works(set1, set2, 4))
                    {
                        int *temp = new int[8];
                        for(int i = 0; i < 4; i++)
                        {
                            temp[i] = set1[i];
                            temp[i+4] = set2[i];
                        }
                        pair4.push_back(temp);
                    }
                }
            }
        }
    }
    delete[] test1;
    test1 = new int[10];
    for(int i = 0; i < 10; i++)
    {
        test1[i] = i+1;
    }
    for(int num1 = 0; num1 < 10; num1++)
    {
        for(int num2 = num1+1; num2 < 10; num2++)
        {
            for(int num3 = num2+1; num3 < 10; num3++)
            {
                for(int num4 = num3+1; num4 < 10; num4++)
                {
                    for(int num5 = num4+1; num5 < 10; num5++)
                    {
                        int set1[5];
                        int set2[5];
                        set1[0] = test1[num1];
                        set1[1] = test1[num2];
                        set1[2] = test1[num3];
                        set1[3] = test1[num4];
                        set1[4] = test1[num5];
                        int used = 0;
                        for(int i = 0; i < 10; i++)
                        {
                            if(i != num1 && i != num2 && i != num3
                            && i != num4 && i != num5)
                            {
                                set2[used] = test1[i];
                                used++;
                            }
                        }
                        if(works(set1, set2, 5))
                        {
                            int *temp = new int[10];
                            for(int i = 0; i < 5; i++)
                            {
                                temp[i] = set1[i];
                                temp[i+5] = set2[i];
                            }
                            pair5.push_back(temp);      
                        }
                    }
                }
            }
        }
    }
    delete[] test1;
    test1 = new int[12];
    for(int i = 0; i < 12; i++)
    {
        test1[i] = i+1;
    }
    for(int num1 = 0; num1 < 12; num1++)
    {
        for(int num2 = num1+1; num2 < 12; num2++)
        {
            for(int num3 = num2+1; num3 < 12; num3++)
            {
                for(int num4 = num3+1; num4 < 12; num4++)
                {
                    for(int num5 = num4+1; num5 < 12; num5++)
                    {
                        for(int num6 = num5+1; num6 < 12; num6++)
                        {
                            int set1[6];
                            int set2[6];
                            set1[0] = test1[num1];
                            set1[1] = test1[num2];
                            set1[2] = test1[num3];
                            set1[3] = test1[num4];
                            set1[4] = test1[num5];
                            set1[5] = test1[num6];
                            int used = 0;
                            for(int i = 0; i < 12; i++)
                            {
                                if(i != num1 && i != num2 && i != num3
                                && i != num4 && i != num5 && i != num6)
                                {
                                    set2[used] = test1[i];
                                    used++;
                                }
                            }
                            if(works(set1, set2, 6))
                            {
                                int *temp = new int[12];
                                for(int i = 0; i < 6; i++)
                                {
                                    temp[i] = set1[i];
                                    temp[i+6] = set2[i];
                                }
                                pair6.push_back(temp); 
                            }
                        }
                    }
                }
            }
        }
    }
}

bool works(int *set, int size)
{
    //Initial checks on different sized sets
    if(set[0] + set[1] <= set[size-1])
    {
        return false;
    }
    if(set[0] + set[1] + set[2] <= set[size-2]+set[size-1])
    {
        return false;
    }
    if(set[0]+set[1]+set[2]+set[3] <= set[size-3]+set[size-2]+set[size-1])
    {
        return false;
    }
    if(size >= 9 && set[0]+set[1]+set[2]+set[3]+set[4] <= set[size-4]+set[size-3]+set[size-2]+set[size-1])
    {
        return false;
    }
    if(size >= 11 && set[0]+set[1]+set[2]+set[3]+set[4]+set[5] <= set[size-5]+set[size-4]+set[size-3]+set[size-2]+set[size-1])
    {
        return false;
    }

    //2 element sets
    //For each possible pairing, only the set where we add
    //the largest and smallest element could be equal,
    //because in the others all elements in the second 
    //second are larger than one in the first set
    for(int num1 = 0; num1 < size; num1++)
    {
        for(int num2 = num1+1; num2 < size; num2++)
        {
            for(int num3 = num2+1; num3 < size; num3++)
            {
                for(int num4 = num3+1; num4 < size; num4++)
                {
                    if(set[num1]+set[num4] == set[num2]+set[num3])
                    {
                        return false;
                    }
                }
            }
        }
    }

    //3 element sets
    for(int num1 = 0; num1 < size; num1++)
    {
    for(int num2 = num1+1; num2 < size; num2++)
    {
    for(int num3 = num2+1; num3 < size; num3++)
    {
    for(int num4 = num3+1; num4 < size; num4++)
    {
    for(int num5 = num4+1; num5 < size; num5++)
    {
    for(int num6 = num5+1; num6 < size; num6++)
    {
        int temp[6];
        temp[0] = set[num1];
        temp[1] = set[num2];
        temp[2] = set[num3];
        temp[3] = set[num4];
        temp[4] = set[num5];
        temp[5] = set[num6];
        for(int i = 0; i < pair3.size(); i++)
        {
            int *order = pair3[i];
            if(temp[order[0]-1]+temp[order[1]-1]+temp[order[2]-1]
            == temp[order[3]-1]+temp[order[4]-1]+temp[order[5]-1])
            {
                return false;
            }
        }
    }
    }
    }
    }
    }
    }

    if(size >= 8)
    {
    for(int num1 = 0; num1 < size; num1++)
    {
    for(int num2 = num1+1; num2 < size; num2++)
    {
    for(int num3 = num2+1; num3 < size; num3++)
    {
    for(int num4 = num3+1; num4 < size; num4++)
    {
    for(int num5 = num4+1; num5 < size; num5++)
    {
    for(int num6 = num5+1; num6 < size; num6++)
    {
    for(int num7 = num6+1; num7 < size; num7++)
    {
    for(int num8 = num7+1; num8 < size; num8++)
    {
        int temp[8];
        temp[0] = set[num1];
        temp[1] = set[num2];
        temp[2] = set[num3];
        temp[3] = set[num4];
        temp[4] = set[num5];
        temp[5] = set[num6];
        temp[6] = set[num7];
        temp[7] = set[num8];
        for(int i = 0; i < pair4.size(); i++)
        {
            int *order = pair4[i];
            if(temp[order[0]-1]+temp[order[1]-1]+temp[order[2]-1]
            + temp[order[3]-1]
            == temp[order[4]-1]+temp[order[5]-1]+temp[order[6]-1]
            + temp[order[7]-1])
            {
                return false;
            }
        }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    
    if(size >= 10)
    {
    for(int num1 = 0; num1 < size; num1++)
    {
    for(int num2 = num1+1; num2 < size; num2++)
    {
    for(int num3 = num2+1; num3 < size; num3++)
    {
    for(int num4 = num3+1; num4 < size; num4++)
    {
    for(int num5 = num4+1; num5 < size; num5++)
    {
    for(int num6 = num5+1; num6 < size; num6++)
    {
    for(int num7 = num6+1; num7 < size; num7++)
    {
    for(int num8 = num7+1; num8 < size; num8++)
    {
    for(int num9 = num8+1; num9 < size; num9++)
    {
    for(int num10 = num9+1; num10 < size; num10++)
    {
        int temp[10];
        temp[0] = set[num1];
        temp[1] = set[num2];
        temp[2] = set[num3];
        temp[3] = set[num4];
        temp[4] = set[num5];
        temp[5] = set[num6];
        temp[6] = set[num7];
        temp[7] = set[num8];
        temp[8] = set[num9];
        temp[9] = set[num10];
        for(int i = 0; i < pair5.size(); i++)
        {
            int *order = pair5[i];
            if(temp[order[0]-1]+temp[order[1]-1]+temp[order[2]-1]
            + temp[order[3]-1] + temp[order[4]-1]
            == temp[order[5]-1]+temp[order[6]-1]+temp[order[7]-1]
            + temp[order[8]-1] + temp[order[9]-1])
            {
                return false;
            }
        }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }

    if(size >= 12)
    {
    for(int num1 = 0; num1 < size; num1++)
    {
    for(int num2 = num1+1; num2 < size; num2++)
    {
    for(int num3 = num2+1; num3 < size; num3++)
    {
    for(int num4 = num3+1; num4 < size; num4++)
    {
    for(int num5 = num4+1; num5 < size; num5++)
    {
    for(int num6 = num5+1; num6 < size; num6++)
    {
    for(int num7 = num6+1; num7 < size; num7++)
    {
    for(int num8 = num7+1; num8 < size; num8++)
    {
    for(int num9 = num8+1; num9 < size; num9++)
    {
    for(int num10 = num9+1; num10 < size; num10++)
    {
    for(int num11 = num10+1; num11 < size; num11++)
    {
    for(int num12 = num11+1; num12 < size; num12++)
    {
        int temp[12];
        temp[0] = set[num1];
        temp[1] = set[num2];
        temp[2] = set[num3];
        temp[3] = set[num4];
        temp[4] = set[num5];
        temp[5] = set[num6];
        temp[6] = set[num7];
        temp[7] = set[num8];
        temp[8] = set[num9];
        temp[9] = set[num10];
        temp[10] = set[num11];
        temp[11] = set[num12];
        for(int i = 0; i < pair6.size(); i++)
        {
            int *order = pair6[i];
            if(temp[order[0]-1]+temp[order[1]-1]+temp[order[2]-1]
            + temp[order[3]-1] + temp[order[4]-1] + temp[order[5]-1]
            == temp[order[6]-1]+temp[order[7]-1]+temp[order[8]-1]
            + temp[order[9]-1] + temp[order[10]-1]+temp[order[11]-1])
            {
                return false;
            }
        }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    return true;
}

int main ()
{
    //Problem has a text file, where each line has a set
    //Determine if the set is a special set or not:
    //Special set means any disjoint subsets cannot have the same
    //sum, and if one subset has more elements, it must
    //have a greater sum

    //Find the sum of all elements in the special sets

    std::ifstream inf{"p105_sets.txt"};
    if(!inf)
    {
        std::cout << "Couldn't find file\n";
        return 1;
    }

    generate();
    int total = 0;
    for(std::string in; std::getline(inf, in); )
    {
        int *set = new int[12];
        int used = 0;
        int current = 0;
        for(int loc = 0; loc < in.length(); loc++)
        {
            if(in[loc] != ',')
            {
                current *= 10;
                current += in[loc]-48;
            }
            else
            {
                set[used] = current;
                used++;
                current = 0;
            }
        }
        set[used] = current;
        used++;

        std::sort(set, set+used);
        if(works(set, used))
        {
            for(int i = 0; i < used; i++)
            {
                total += set[i];
            }
        }
    }
    std::cout << total << '\n';
    return 0;
}