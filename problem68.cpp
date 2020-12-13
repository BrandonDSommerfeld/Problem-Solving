#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int main ()
{
    //Take the numbers 1-10 and arrange them on a pentagon
    //With each side extended in 1 direction
    //Each line of 3 numbers should add up to the same value
    //For example, with a triangle you create
    /*
                4
                 \
                  3
                 /  \
                1 -  2 - 6
               /
              5

    */
   //Then you express this arrangement as a string by listing lines
   //From the lowest outer node in clockwise order, as
   //432 ; 621; 513
   //Find the pentagon like this which creates the largest possible
   //16-digit number when the numbers are placed together


   //I didn't even write code for this
   //I just forced the numbers 6-10 on the outside to start with 6
   //Because any string starting with 6 is better than others

   //Then there is only 1 inner ring which fits with this
   //Gives the ring
   /*

              6   
               \ 
                5   10
             /   \ /
          2       3
         / \     /
        7   4 - 1 - 9
             \
              8



   */


    return 0;
}