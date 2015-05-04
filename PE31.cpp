#include <iostream>

int main()
{
  const int  n  = 201, m = 8;
  int  a[n][m],
      denom[m]  = {1, 2, 5, 10, 20, 50, 100, 200},
             i  = 0, j = 0;

  for(i = 0; i < n; ++i)
    for(j = 0; j < m; ++j) a[i][j] = 1;

  for(i = 1; i < n; ++i)
  {
    for(j = 1; j < m; ++j)
      a[i][j] = i - denom[j] >= 0 ? a[i][j-1] + a[i-denom[j]][j] : a[i][j-1];
  }

  std::cout << a[n-1][m-1] << std::endl;

  return 0;
}
