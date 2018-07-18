# learn_gbitx
Try it out right in your web browser via GDB Online C compiler! 
https://onlinegdb.com/SJNwq7amX 

Demo of GBITX macros from Plan9 Fcall. These macros allow for extraction of 
one , two, three, or four bytes from memory address in pointer p. The extracted 
data is interpreted as unsigned char, unsigned short, unsigned int, or unsigned long int, 
respectively. This functionality is implemented via compiler preprocessor macros and 
bit shifts for efficiency. 

Prototypes of the said macros are:
uchar      GBIT8(uchar*)
ushort     GBIT16(uchar*)
ulong      GBIT32(uchar*)
vlong      GBIT64(uchar*)

The definitions are:
#define	GBIT8(p) ((p)[0])
#define	GBIT16(p) ((p)[0]|((p)[1]<<8))
#define	GBIT32(p) ((u32int)((p)[0]|((p)[1]<<8)|((p)[2]<<16)|((p)[3]<<24)))
#define	GBIT64(p) ((u32int)((p)[0]|((p)[1]<<8)|((p)[2]<<16)|((p)[3]<<24)) |\
((vlong)((p)[4]|((p)[5]<<8)|((p)[6]<<16)|((p)[7]<<24)) << 32))

See also: // See also: https://9fans.github.io/plan9port/man/man3/fcall.html 

