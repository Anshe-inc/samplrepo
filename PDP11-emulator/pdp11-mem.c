#include <stdio.h>

typedef char byte;				//8-bit
typedef unsigned short word;	//16-bit
typedef word Address;			//16-bit

#define MEMSIZE (64*1024)

byte mem[MEMSIZE];

void b_write(Address addr, byte b);
byte b_read(Address addr);
void w_write(Address addr, byte b);
word w_write(Address addr);

int main() {
	return 0;
}
