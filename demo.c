/******************************************************************************
 *                                                                            *
 *        DEMO of GBIT8(p), GBIT16(p), ... macros from Plan9 Fcall()          *
 *        http://github.com/pgniewek/learn_gbitx                              *
 *                                                                            *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

// color codes for terminal output
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"

// Macros from Plan9 Fcall()
#define    GBIT8(p) ((p)[0])
#define    GBIT16(p) ((p)[0]|((p)[1]<<8))
#define    GBIT32(p) ((unsigned int)((p)[0]|((p)[1]<<8)|((p)[2]<<16)|((p)[3]<<24)))
#define    GBIT64(p) ((unsigned int)((p)[0]|((p)[1]<<8)|((p)[2]<<16)|((p)[3]<<24)) |\
                      ((long unsigned int)((p)[4]|((p)[5]<<8)|((p)[6]<<16)|((p)[7]<<24)) << 32))

// See also: https://9fans.github.io/plan9port/man/man3/fcall.html
//    /* these are implemented as macros */
//   uchar      GBIT8(uchar*)
//   ushort     GBIT16(uchar*)
//   ulong      GBIT32(uchar*)
//   vlong      GBIT64(uchar*)

// So p is assumed to be an array of unsigned chars.
// Remember that in C arrays are pointers, so p is in fact a pointer
// to a series of unsigned chars in the memory.

// GBIT8(p) just takes the first unsigned char (first 8 bits) from
// the address given by the pointer p.
// (p)[0] is the byte at the memory address given by p.

// GBIT16(p) returns the sort int given by the first 16 bits
// from the memory cell p.

// Similarly for GBIT32, GBIT64.
// Some details and comments are given below. 


// A simple function printing bits of a char variable
void printBits (unsigned long int num, int nbits)
{
  #define buf_len 32
  int buf[buf_len];
  unsigned long int bitmask;
  int i;
  bitmask = 1;
  for (i = 0; i < nbits; i++)
    {
      buf[nbits-i-1] = !!(num & bitmask);
      bitmask = bitmask * 2;
    }
  for (i = 0; i < nbits; i++)
    {
      if( i % 8 == 0 )
        // print additional space between bytes
        printf(" ");
      if(buf[i]==1)
        // print "1 " in green
        printf ("%s1%s", KGRN, KNRM);
      if(buf[i]==0)
        // print "0 " in red
        printf ("%s0%s", KRED, KNRM);
    }
}

void print_spaces( int n )
{
  int i;
  for( i=0; i < n; i++)
    printf(" ");
}



unsigned char pp[8];
int i; // loop index

// Variables for input of data from keyboard
char getline_info; // status of getline call (success / failure)
char *buffer = NULL;
size_t len = 0;

int main ()
{
  printf("GBITX macro demonstration. \n");
  printf("(1) At first the program will now ask for 8 integers pp[i] \n");
  printf("    such that 0 <= pp[i] <= 255. \n");
  printf("(2) Then it will demonstrate the bitwise OR and \n");
  printf("    AND operations. \n");
  printf("(3) Afterwards the bit shift operation will be demonstarted. \n");
  printf("(4) Then the BGITX macros will be analysed. \n");
  printf("(5) Finally a short remark on endianness will be given. \n\n");

  // - - - (1) - - -
  
  printf("(1) Input of 8 numbers pp[i], such that 0 <= pp[i] <= 255. \n\n"); 

  for (i = 0; i < 8; i++)
    {
      printf("Please type pp[%d] and hit return: ", i);
      getline_info = getline(&buffer, &len, stdin);
      if( getline_info == -1 )
        {
          printf("\nError reading input.");
          return -1;
        }
      pp[i] = atoi(buffer);
    }

  printf("Array pp = { ");
  for( i=0; i < 8; i++ )
  {
    printf("%d", pp[i]);
    if( i != 7 ) printf(",");
    printf(" ");
  }
  printf("}. \n\n");
  
  // - - - (2) - - -
  
  printf("\n(2) Demonstration of bitwise AND, OR operations. \n\n");
  
  printf("A reminder: \n");
  printf("  & = bitwise AND:    | = bitwise OR: \n"); 
  printf("    p    q   p & q       p    q   p | q  \n");
  printf("  %s  0  %s  0  %s   0       %s  0  %s  0   %s  0  \n", KRED, KRED, KRED,  KRED, KRED, KRED);
  printf("  %s  0  %s  1  %s   0       %s  0  %s  1   %s  1  \n", KRED, KGRN, KRED,  KRED, KGRN, KGRN);
  printf("  %s  1  %s  0  %s   0       %s  1  %s  0   %s  1  \n", KGRN, KRED, KRED,  KGRN, KRED, KGRN);
  printf("  %s  1  %s  1  %s   1       %s  1  %s  1   %s  1  \n", KGRN, KGRN, KGRN,  KGRN, KGRN, KGRN);
  printf("%s\n", KNRM);
  
  printf ("\n    BR(x) is the binary representation of x. \n");

  printf("\n BR( pp[0] )         = ");
  printBits( pp[0] , 8);
  printf("\n BR( pp[1] )         = ");
  printBits( pp[1] , 8);
  printf("\n BR( pp[0] | pp[1] ) = ");
  printBits( pp[0] | pp[1] , 8);
  printf("\n BR( pp[0] & pp[1] ) = ");
  printBits( pp[0] & pp[1] , 8);
  printf("\n\n");

  printf("\nPress any key to continue to the next part of the demo...\n");
  getline_info = getline(&buffer, &len, stdin);
  
  // - - - (3) - - -
  
  printf("\n(3) Demonstration bit shift left operation, <<. \n\n");
    
  for( i=0; i < 4; i++)
  {
     printf("BR( pp[%d] )       = ", i);
     print_spaces(27);
     printBits( pp[i] ,8);
     printf ("\n");

     printf("BR( pp[%d] << 8  ) = ", i);
     print_spaces(18);
     printBits( pp[i] << 8 ,16);
     printf ("\n");

     printf("BR( pp[%d] << 16 ) = ", i);
     print_spaces(9);
     printBits( pp[i] << 16 ,24);
     printf ("\n");
     
     printf("BR( pp[%d] << 24 ) = ", i);
     printBits( pp[i] << 24 ,32);
     printf ("\n");

     printf("\n");
  }

  printf("\nPress any key to continue to the next part of the demo...\n");
  getline_info = getline(&buffer, &len, stdin);

  // - - - (4) - - -
  
  // - - - GBIT16(p) - - - 

  printf("Example illustrating the GBIT16 macro: \n\n");
  
  printf("BR( pp[0] )                  = ");
  printBits( pp[0] ,16);
  printf ("\n");
  
  printf("BR( pp[1] )                  = ");
  printBits( pp[1] ,16);
  printf ("\n");
  
  printf("BR( pp[1] << 8 )             = ");
  printBits( pp[1] << 8 ,16);
  printf ("\n");

  printf("BR( (pp[0]) | (pp[1] << 8) ) = ");
  printBits( (pp[0]) | (pp[1] << 8) ,16);
  printf ("\n");

  printf("BR( GBIT16(pp) )             = ");
  printBits( GBIT16(pp) ,16);
  printf ("\n");

  // - - - GBIT32(p) - - - 

  printf("\nExample illustrating the GBIT32 macro: \n\n");
  
  printf("BR( pp[0] )        = ");
  printBits( pp[0] ,32);
  printf ("\n");

  printf("BR( pp[1] << 8 )   = ");
  printBits( pp[1] << 8 ,32);
  printf ("\n");

  printf("BR( pp[2] << 16 )  = ");
  printBits( pp[2] << 16 ,32);
  printf ("\n");

  printf("BR( pp[3] << 24 )  = ");
  printBits( pp[3] << 24 ,32);
  printf ("\n");

  printf("BR( GBIT32(pp) )   = ");
  printBits( GBIT32(pp) ,32);
  printf ("\n");


  printf("\nPress any key to continue to the next part of the demo...\n");
  getline_info = getline(&buffer, &len, stdin);
  
  // - - - (5) - - -

  
  printf("\n");

  printf("Note that macros GBIT16, GBIT32, GBIT64, correspond to \n");
  printf("LITTLE ENDIAN encoding: the LEAST significant BYTE of \n");
  printf("a multi-byte variable is stored FIRST. \n\n");
  
  #ifdef __GNUC__

  printf("Detection of endianness of this machine using GCC macros: \n\n");
  printf("__BYTE_ORDER__          = %d \n", __BYTE_ORDER__);
  printf("__ORDER_LITTLE_ENDIAN__ = %d \n", __ORDER_LITTLE_ENDIAN__);
  printf("__ORDER_BIG_ENDIAN__    = %d \n\n", __ORDER_BIG_ENDIAN__);
  
  if( __BYTE_ORDER__ ==  __ORDER_LITTLE_ENDIAN__ )
    printf("This machine is using LITTLE ENDIAN encoding of integers. \n\n");
  if( __BYTE_ORDER__ ==  __ORDER_BIG_ENDIAN__ )
    printf("This machine is using BIG ENDIAN encoding of integers. \n\n");
  
  #endif
  
  printf("Let val be the value of { pp[0], pp[1], pp[2], pp[3] } \n");
  printf("converted to unsigned int through pointer casting: \n\n");
  
  printf("  unsigned int * pint;         \n");
  printf("  unsigned int val;            \n");
  printf("  pint = (unsigned int*) pp;   \n");
  printf("  val = *pint;                 \n\n");
  
  // pointer to unsgn. int
  unsigned int * pint;
  unsigned int val;
  pint = (unsigned int*) pp;
  val = *pint;

  printf("val        = %10d (hex: %x) \n", val, val);
  printf("GBIT32(pp) = %10d (hex: %x) \n", GBIT32(pp),GBIT32(pp));

  if( val == GBIT32(pp) )
  {
    printf("\nNumbers val and GBIT32(pp) are equal. This means that \n");
    printf("GBIT32 macro is compatible with the internal representation \n");
    printf("of integers on this machine.  \n");
  }
  
  printf("\n END OF DEMONSTRATION. \n");
  
  return 0;
}
