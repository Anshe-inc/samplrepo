#include "test.h"


//this is for tests
void test_load(const char* filename) {			//tests loading file to memory
	load_file(filename);
	dump(0x0080, 0x000c);
	run();
}

void testing() {
	byte b0 = 0xa0;									//b0 = decimal(160)
	b_write(2, b0);									//write to address 0x2

	byte b_res = b_read(2);							//read from address 0x2
	assert(b0 == b_res);
	trace("%02hhx = %02hhx\n", b0, b_res);			//print the result and compare

	//tests for words
	Address a = 4;
	b0 = 0x0a;
	byte b1 = 0x0b;
	word b = 0x0b0a;
	b_write(a, b0);
	b_write(a + 1, b1);
	word w_res = w_read(a);
	trace("word/bytes \t %04hx = %02hhx%02hhx\n", w_res, b1, b0);
	assert(w_res == b);
}