#include <cstdlib>
#include <iostream>
#include <cassert>

/*********************************************
  Code by Lewis Haley (www.lewishaley.co.uk)
  - lewismhaley@gmail.com

  Challenge set by SN Systems

  TODO
  - see if I can reduce/find a better solution
  - to the long IF statement... maybe too many
  - IFs altogether?
**********************************************/

/*
atoi_ex

Write a function in C or C++ that reads an ASCII character string and returns the integer
value that it represents. The function should ignore leading whitespace and stop conversion
at the first non-digit character.

Where conversion is not possible, the function should return 0 and indicate an error
condition.

If the string is prefixed with "0x" then treat the input as hexadecimal.
*/

/*
\param const char *s, a constant pointer to the ASCII to analyse
\param int *error, variable indicates whether an error has occured
\return int, the numerical value of the ASCII text
*/
int atoi_ex( const char *s, int *error )
{
    // if the string is null
    if ( strlen(s) == 0 )
    {
        // raise the error
        *error = 1;
        return 0;
    }

    // if the value can be extracted directly (i.e. not hex conversion)
    else if ( atoi( s ) ||
              ( s[0] == '0' && strlen(s) == 1 ) ) // also have to check if it's ZERO
    {
        return atoi( s ); // use existing atoi(), that handles char->int conversion
    }

    // if the first character is not a number AND not ZERO
    else if ( !atoi( &s[0] ) && s[0] != '0' ) //atoi() returns TRUE for all numbers except ZERO, so must check for ZERO
    {
        // raise error
        *error = 1;
        return 0;
    }

    // at this stage, we have a char that (might be) a hex value
    else
    {
        // check for "0x" prefix, and for hex number straight afterwards
        if ( s[0] == '0' &&
             s[1] == 'x' &&
             ( s[2] == 'a' || s[2] == 'b' || s[2] == 'c' || // third character must be
               s[2] == 'd' || s[2] == 'e' || s[2] == 'f' || // equivalant to a hex value
               s[2] == '0' || atoi( &s[2] ) ) ) // ie. 0,1,2,3,4,5,6,7,8,9,a,b,c,d,e,f
        {
            float trailing = 0.0f; // this is counting any no hex values that trail the number
            int tmp = 0; // a temp variable for running total

            // we want 2 less interations than length of char (because of "0x" prefix)
            // used to index into char, but we index from right to left
            for ( unsigned i=0; i<strlen(s)-2; ++i )
            {
                //std::cout<<s[strlen(s)-i-1]<<" i = "<<i<<std::endl;

                // if the current char converts to int
                if ( atoi( &s[strlen(s)-i-1]) )
                {
                    // we do this because otherwise consecutive digits get counted more than once
                    // eg. s = "0x123", first 3 is considered, then 23, then 123
                    // this separates the digits
                    char ch = s[strlen(s)-i-1];
                    tmp += atoi( &ch )*pow( 16.0f, float(i) ); // convert the digit to hex
                    //std::cout<<atoi( &s[strlen(s)-i-1] )<<" tmp = "<<tmp<<std::endl;
                }

                // if current char is hex value a,b,c,d,e,f
                else if ( s[strlen(s)-i-1] == 'a' )
                {
                    tmp += 10*pow( 16.0f, float(i) );
                    //std::cout<<"tmp = "<<tmp<<std::endl;
                }
                else if ( s[strlen(s)-i-1] == 'b' )
                {
                    tmp += 11*pow( 16.0f, float(i) );
                    //std::cout<<"tmp = "<<tmp<<std::endl;
                }
                else if ( s[strlen(s)-i-1] == 'c' )
                {
                    tmp += 12*pow( 16.0f, float(i) );
                    //std::cout<<"tmp = "<<tmp<<std::endl;
                }
                else if ( s[strlen(s)-i-1] == 'd' )
                {
                    tmp += 13*pow( 16.0f, float(i) );
                    //std::cout<<"tmp = "<<tmp<<std::endl;
                }
                else if ( s[strlen(s)-i-1] == 'e' )
                {
                    tmp += 14*pow( 16.0f, float(i) );
                    //std::cout<<"tmp = "<<tmp<<std::endl;
                }
                else if ( s[strlen(s)-i-1] == 'f' )
                {
                    tmp += 15*pow( 16.0f, float(i) );
                    //std::cout<<"tmp = "<<tmp<<std::endl;
                }

                // because we index from right to left, trailing chars affect the hex value
                // eg. 100st looks like 10000 with the tens and units being "unknown"
                // but we want to get 100 and ignore the st bit
                // likewise, we want 10s0t to return 10
                else
                {
                    // a record is kept of the last trailing char found
                    // eg. 10s0t
                    //       ^
                    //    12(3)45
                    // so trailing would = 3
                    trailing = i+1;
                }
            }
            //std::cout<<"tmp = "<<tmp<<std::endl;

            // after going through all the chars
            // correct the tmp value before returning
            // eg. 100st, tmp = 10000, so we must divide by 100
            // 100 is 10 to the power of the number of trailing chars
            return tmp/(pow(16.0f, trailing));
        }

        // we catch any "fake" hex values like 0xghi
        else
        {
            // raise error
            *error = 1;
            return 0;
        }
    }
}

int main()
{
    const char *s;

    s = "0x1agagggg"; // should return a value of 26

    int error = 0;

    std::cout<<"atoi_ex( "<<s<<" ) = "<<atoi_ex( s, &error )<<std::endl;

    if ( error )
    {
        std::cout<<"There was an error."<<std::endl;
    }

    // if a full program I would use an assert to check the error (not an IF)
    //assert( !error )

    return 0;
}
