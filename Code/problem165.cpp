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
  std::cout << '(' << segments[1989].x1 << ',' << segments[1989].y1 << ") ("
  << segments[1989].x2 << ',' << segments[1989].y2 << ")\n";
  std::cout << '(' << segments[783].x1 << ',' << segments[783].y1 << ") ("
  << segments[783].x2 << ',' << segments[783].y2 << ")\n";
  for(int i = 0; i < limit; i++)
  {
    for(int j = 0; j < i; j++)
    {
      if(segments[i].x1 == segments[i].x2)
      {
        if(between(segments[i].x1, segments[j].x1, segments[j].x2)
        && segments[j].x2 != segments[j].x1)
        {

          math::FastRational slope2{segments[j].y2 - segments[j].y1, segments[j].x2-segments[j].x1};
          math::FastRational y = slope2*(segments[i].x1-segments[j].x1) + segments[j].y1;
          if(between(y, segments[i].y1, segments[i].y2))
          {
            point p{segments[i].x1, y};
            intersections.insert(p);
          }
        }
      }
      else if(segments[j].x1 == segments[j].x2)
      {
        if(between(segments[j].x1, segments[i].x1, segments[i].x2))
        {
          math::FastRational slope1{segments[i].y2 - segments[i].y1, segments[i].x2-segments[i].x1};
          math::FastRational y = slope1*(segments[j].x1-segments[i].x1) + segments[i].y1;
          if(between(y, segments[j].y1, segments[j].y2))
          {
            point p{segments[j].x1, y};
            intersections.insert(p);
          }
        }
      }
      else
      {
        if(i == 1989 && j == 783)
        {
          std::cout << "Got here\n";
        }
        math::FastRational slope1{segments[i].y2 - segments[i].y1, segments[i].x2-segments[i].x1};
        math::FastRational slope2{segments[j].y2 - segments[j].y1, segments[j].x2-segments[j].x1};
        if(i == 1989 && j == 783)
        {
          std::cout << slope1 << ' ' << slope2 << '\n';
        }
        /*
        Point slope
        (y - y1) = m(x-x1)
        y = mx-mx1+y1
        m1*x - m1*x1 + y1 = m2*x - m2*x2 + y2
        x = (m1*x1+y2 -m2*x2 - y1) / (m1 - m2)
        */
        if(slope1 - slope2 != 0)
        {
          //Something funky happening here
          math::FastRational x{slope1*segments[i].x1 + segments[j].y2 - slope2*segments[j].x2
          - segments[i].y1};
          if(i == 1989 && j == 783)
          {
            std::cout << "Got x\n";
          }
          x *= (1 / math::FastRational(slope1-slope2));
          if(between(x, segments[i].x1, segments[i].x2) && between(x, segments[j].x2, segments[j].x1))
          {
            math::FastRational y = slope1*(x-segments[i].x1) + segments[i].y1;
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