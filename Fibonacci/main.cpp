#include <iostream>
#include <cstdlib>
#include <cassert>

/*
  \brief calculates the nth fibonacci number
  \param unsigned n - nth number to calculate
  \return unsigned fib number
*/
unsigned fib( unsigned n )
{
    // 0 and 1 are base numbers, return them
    if ( n<2 )
    {
        return n;
    }
    // if not 0 or 1
    else
    {
        return fib( n-1 )+fib( n-2 );
    }
}

/*
  \brief calculates whether a number is prime
  \param unsigned n - number to assess
  \return bool, true is n is prime
*/
bool isPrime( unsigned n )
{
    // 0 and 1 are NOT prime
    if ( n < 2 )
    {
        return false;
    }
    // cycle through numbers less than n
    // is any divide without leaving a remainder, return false (not prime)
    for ( unsigned i=2; i<n; ++i )
    {
        if ( !(n%i) )
        {
            return false;
        }
    }
    // otherwise the number IS prime
    return true;
}

/*
  \brief calculates the greatest common divisor using Euclidean algorithm
  \param unsigned a
  \param unsigned b (b<a)
  \return unsigned value of gcd
*/
unsigned gcd( unsigned a, unsigned b )
{
    // make sure a is greater than b
    assert( a>=b );
    // if there is no remainder for a/b
    // b was the previous remainder, return it
    if ( !(a%b) )
    {
        return b;
    }
    // if there was a remainder for a/b
    // a = b, b = a%b
    else
    {
        return gcd( b, (a%b) );
    }
}

/*
  \brief calculates the phi function value of a number (Euler's totient)
  \param unsigned n - number to calculate
  \return unsigned phi function of n
*/
unsigned phiFn( unsigned n )
{
    unsigned phi = 0;
    // cycle through all values 1<=i<=n
    for ( unsigned i=1; i<=n; ++i )
    {
        // n and i are co-prime (share no common prime factors)
        // if their gcd is 1, ergo increment phi value
        if ( gcd( n,i ) == 1 )
        {
            phi++;
        }
    }
    return phi;
}

/*
  \brief calculates nth triangle number
  \param unsigned n - number to calculate
  \return unsigned triangle value
*/
unsigned triNum( unsigned n )
{
    return ((n*n)+n)*0.5;
}

int main()
{
    return 0;
}
