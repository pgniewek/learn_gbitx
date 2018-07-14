#include <stdio.h>
#include <stdlib.h>



// A simple function printing Hex representation of unsigned int
void printHex (unsigned int num)
{
  #define nhex 8
  char buf[nhex];
  int i;
  unsigned long int current, rest;
  int hex_ind;
  char lookup[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
  
  rest = num;
  for (i = 0; i < nhex; i++)
    {
      current = ( rest >> ( (nhex - i -1)*4 ) );
      buf[i] = lookup[ current ];
      current = ( current << ( (nhex - i -1)*4 ) );
      rest = rest - current;
      if( i % 2 == 0 )  //  print additional space between bytes
        printf(" ");
      printf("%c", buf[i]);

    }
}

int num;

int main()
{

  for( int i =0; i < 20; i++)
  {
    num = i*i + 36 *i;
    printf(" %d  :  ", num);
    printHex( num );
    printf("  : %x \n", num);
  }
  

  return 0;
}
