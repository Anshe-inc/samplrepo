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
	byte b0 = 0xa0;									//b0 = decimal(160)
	b_write(2, b0);									//write to address 0x2

	byte b_res = b_read(2);							//read from address 0x2

	printf("%hhx = %hhx\n", b0, b_res);				//print the result and compare



	return 0;
}

void b_write(Address addr, byte b) {				//writes b to addr address
	mem[addr] = b;
	return;
}
byte b_read(Address addr) {							//reads from addr address
	return mem[addr];
}
