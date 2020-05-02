#include "test.h"


//this is for tests
void test_load() {
	load_file();
	for (int i = 0; i < 100; i++) {
		printf("%02hhx\t", b_read(0x0200 + i));
		if (i % 100 == 0)
			printf("\n\n");
		if (i % 1000 == 0)
			printf("\n");
	}
}
void testing() {
	byte b0 = 0xa0;									//b0 = decimal(160)
	b_write(2, b0);									//write to address 0x2

	byte b_res = b_read(2);							//read from address 0x2
	assert(b0 == b_res);
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