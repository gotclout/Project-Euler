#include <iostream>
#include <fstream>
#include <time.h>

#define minVal adj[i][j].value < min &&  adj[i][j].value != -1 
#define setMin min = adj[i][j].value; k = i; l = j;

using namespace std;

const static int n = 40;

struct data
{
  bool marked, connected; int value;
  data(){marked = connected = 0; value = -1;};
};

data adj[n][n];

int initialize()
{
  int initial = 0;
  char temp;
  ifstream in;
  in.open("PEInputFiles/network.txt");
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < n; j++)
    {
      temp = in.peek();
      if(temp == '-')in >> temp;
      else
      {
        in >> adj[i][j].value;
        initial += adj[i][j].value;
      }
      j == n - 1 ? in.ignore(1, '\n') : in >> temp;
    }
  }
  in.close();

  return initial;
}

bool is_connected()
{
  for(int i = 0; i < n; i++)
    if(!adj[0][i].connected) return false;
  return true;
}

void mark_connected(const int & jj, const int & ll)
{
  for(int i = 0; i < n; i++)
  {
    if(i == jj)
      for(int j = 0; j < n; j++)
        adj[i][j].marked = true;
    adj[i][ll].connected = true;
  }
}

int optimize(int & k, int & l)
{
  int i, j, min = 0, pruned = 0;

  do
  {
    min = INT_MAX;
    for(i = 0; i < n; i++)
    {
      if(adj[i][0].marked)
      {
        for(j = 1; j < n; j++)
          if(!adj[i][j].connected && minVal) { setMin; }
      }
    }
    pruned += min;
    adj[k][l].value = -1;
    mark_connected(l, l);
  }
  while(!is_connected());

  return pruned;
}

int main()
{
  clock_t start, end;
  
  start = clock();
  
  int initial = 0, pruned = 0, min = 0, i = 0, j = 0, k, l;
  
  initial = initialize();
  
  while(adj[i++][j].value == -1) setMin;
  for(i; i < n; i++)
    if(minVal){ setMin; }
  adj[k][l].value = -1;
  mark_connected(0, l);
  pruned = optimize(k, l);
  
  end = clock();
  cout << initial / 2 - pruned << endl;
  cout << "Computation Time: " << (end - start) / (double) CLOCKS_PER_SEC << "ms\n";
  
  return 0;
}
