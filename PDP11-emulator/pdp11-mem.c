#include <stdio.h>
#include <assert.h>

typedef char byte;				//8-bit
typedef unsigned short word;	//16-bit
typedef word Address;			//16-bit

#define MEMSIZE (64*1024)

byte mem[MEMSIZE];

void b_write(Address addr, byte b);
byte b_read(Address addr);
void w_write(Address addr, word b);
word w_read(Address addr);

void testing() {
	byte b0 = 0xa0;									//b0 = decimal(160)
	b_write(2, b0);									//write to address 0x2

	byte b_res = b_read(2);							//read from address 0x2

	printf("%02hhx = %02hhx\n", b0, b_res);			//print the result and compare

	//tests for words
	Address a = 4;
	b0 = 0x0a;
	byte b1 = 0x0b;
	word b = 0x0b0a;
	b_write(a, b0);
	b_write(a + 1, b1);
	word w_res = w_read(a);
	printf("word/bytes \t %04hx = %02hhx%02hhx\n", w_res, b1, b0);
	assert(w_res == b);
}
int main(){
	testing();
	return 0;
}

void b_write(Address addr, byte b) {				//writes b to addr address
	mem[addr] = b;
	return;
}
byte b_read(Address addr) {							//reads from addr address
	return mem[addr];
}
word w_read(Address addr) {
	return *((word*)(mem + addr));
}
