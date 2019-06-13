#include <iostream>
#include <fstream>
#include <time.h>

#define dp(p0, p1) ((p0.x * p1.x) + (p0.y * p1.y))

using namespace std;

const static int n = 1000;

struct point {double x, y, z;};
struct triangle {point a, b, c;};

triangle next_triangle(ifstream & in, triangle & t)
{
  in >> t.a.x;
  in.ignore(1, ',') ;
  in >> t.a.y;
  in.ignore(1, ',');
  in >> t.b.x;
  in.ignore(1, ',');
  in >> t.b.y;
  in.ignore(1, ',');
  in >> t.c.x;
  in.ignore(1, ',');
  in >> t.c.y;
  in.ignore(1, '\n');

  return t;
}

bool contains_origin(const triangle & t)
{
  point v0, v1, v2;

  double invDen, u, v;

  v0.x = t.c.x - t.a.x;
  v0.y = t.c.y - t.a.y;

  v1.x = t.b.x - t.a.x;
  v1.y = t.b.y - t.a.y;

  v2.x = 0 - t.a.x;
  v2.y = 0 - t.a.y;

  double d00 = dp(v0, v0), d01 = dp(v0, v1),
         d02 = dp(v0, v2), d12 = dp(v1, v2),
         d11 = dp(v1, v1);

  invDen = 1 / ((d00 * d11) - (d01 * d01));
  u = ((d11 * d02) - (d01 * d12)) * invDen;
  v = ((d00 * d12) - (d01 * d02)) * invDen;

  return (u > 0 && v > 0) && (u + v < 1);
}

int main(int argc, char**)
{
  int      numOrigins = 0;
  clock_t  start, end;
  ifstream in;
  triangle t;

  start = clock();
  in.open("triangles.txt");
  for(int i = 0; i < n; i++)
  {
    t = next_triangle(in, t);
    if(contains_origin(t))
      numOrigins++;
  }
  in.close();
  end = clock();

  cout << "Num Triangles Containing Origin: " << numOrigins << endl
       << "Computation Time: " << (end - start) / (double) CLOCKS_PER_SEC << "ms\n";

  return 0;
}
