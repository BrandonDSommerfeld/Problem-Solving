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

struct line
{
  int x1;
  int y1;
  int x2;
  int y2;
};

struct point
{
  math::FastRational x;
  math::FastRational y;
};

bool operator< (const point& p1, const point& p2)
{
  if(p1.x < p2.x) return true;
  if(p1.x > p2.x) return false;
  return p1.y < p2.y;
}

bool between(const math::FastRational& num, 
const math::FastRational boundary1, const math::FastRational& boundary2)
{
  return (boundary1 < num && num < boundary2) || (boundary2 < num && num < boundary1);
}

int main ()
{
  //Consider creating 5,000 line segments by generating 20,000 random numbers, 
  //and the line goes from (n1, n2) to (n3, n4) for 4 consecutive numbers

  //How many intersection points exist between the segments, not 
  //counting intersections at the endpoints or overlapping lines

  int limit = 5000;
  line* segments = (line*) calloc(sizeof(line), limit);
  long long gen = 290797;
  for(int i = 0; i < limit; i++)
  {
    gen = (gen*gen) % 50515093;
    segments[i].x1 = (gen % 500);
    gen = (gen*gen) % 50515093;
    segments[i].y1 = (gen % 500);
    gen = (gen*gen) % 50515093;
    segments[i].x2 = (gen % 500);
    gen = (gen*gen) % 50515093;
    segments[i].y2 = (gen % 500);
  }
  std::set<point> intersections{};
  for(int i = 0; i < limit; i++)
  {
    for(int j = 0; j < i; j++)
    {
      //Special cases for vertical lines since they don't have defined slope
      if(segments[i].x1 == segments[i].x2) 
      {
        if(segments[j].x1 != segments[j].x2)
        {
          /*
          Point slope for line 2:
          y = m(x-x1)+y1
          */
          math::FastRational slope{segments[j].y2-segments[j].y1, segments[j].x2-segments[j].x1};
          math::FastRational y = slope*(segments[i].x1 - segments[j].x1) + segments[j].y1;
          if(between(y, segments[i].y1, segments[i].y2)
          && between(segments[i].x1, segments[j].x1, segments[j].x2))
          {
            point p{segments[i].x1, y};
            intersections.insert(p);
          }
        }
      }    
      else if(segments[j].x1 == segments[j].x2)
      {
        if(segments[i].x1 != segments[i].x2)
        {
          math::FastRational slope{segments[i].y2-segments[i].y1, segments[i].x2-segments[i].x1};
          math::FastRational y = slope*(segments[j].x1 - segments[i].x1) + segments[i].y1;
          if(between(y, segments[j].y1, segments[j].y2)
          && between(segments[j].x1, segments[i].x1, segments[i].x2))
          {
            point p{segments[j].x1, y};
            intersections.insert(p);
          }
        }
      } 
      else
      {
        math::FastRational slope1{segments[i].y2-segments[i].y1, segments[i].x2-segments[i].x1};
        math::FastRational slope2{segments[j].y2-segments[j].y1, segments[j].x2-segments[j].x1};
        if(slope1 != slope2)
        {
          /*
          y = m1(x-x1) + y1
          y = m2(x-x2) + y2
          m1x-m1x1+y1 = m2x-m2x2+y2
          x(m1-m2) = m1x1-m2x2-y1+y2
          x = (m1x1-m2x2-y1+y2)/(m1-m2)
          */
          math::FastRational x = slope1*segments[i].x1 - slope2*segments[j].x2 
          - segments[i].y1 + segments[j].y2;
          x /= (slope1 - slope2);

          if(between(x, segments[i].x1, segments[i].x2) && 
          between(x, segments[j].x1, segments[j].x2))
          {  
            math::FastRational y = slope1*(x - segments[i].x1) + segments[i].y1;
            point p{x, y};
            intersections.insert(p);
          }
        }
      }   

    }
  }
  std::cout << intersections.size() << '\n';
  return 0;
}