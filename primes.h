#ifndef _primes_
#define _primes_

#include <vector>
#include <cmath>

using namespace std;

typedef unsigned long long tulong;

class primes
{
  private:

    vector<bool> primeV;
    tulong idx,
           max,
           next,
           count;

    bool retVal;

  public:

    inline const tulong& nump() const { return count; };

    inline const tulong& maxp() const { return max; };

    explicit primes() : primeV(ULLONG_MAX, false)
    {
      primeV[2] = true;
    };

    explicit primes(const tulong & init) : primeV(init, true)
    {
      tulong jdx, j;
      idx = 2;
      count = idx + 1;
      primeV[0] = primeV[1] = false;

      for(; idx*idx <= init; idx++)
        if(primeV[idx])
          for(jdx = idx*idx, j = 0; jdx <= init; j++, jdx = (idx*idx) + (j*idx))
            if(primeV[jdx])
              primeV[jdx] = false;

      for(; idx < init; idx++)
      {
        if(primeV[idx])
        {
          count++;
          max = idx;
        }
      }
    };

    inline tulong nextprime(const tulong & i)
    {
      tulong rval = i;

      if(++rval > max)
        while(!isprime(rval)) rval++;
      else
        while(!primeV[rval]) rval++;

      return rval;
    };

    inline tulong nextprime()
    {
      while(!primeV[++idx]) {;}

      return idx;
    };

    inline bool isprime(const tulong & p)
    {
      retVal = true;

      if(p > max)
      {
        next = idx = 2;
        do
        {
          if(p % next == 0)
          {
            primeV.push_back(false);
            retVal = false;
          }
          else
            next = nextprime();
        }while(retVal && next < sqrt(p) + 1);

        if(retVal)
        {
          primeV.push_back(true);
          max = p;
          count++;
        }
      }
      else
        retVal = primeV[p];

      return retVal;
    };
};

#endif //_primes_
