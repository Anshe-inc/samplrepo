#include "main.h"


int main(){
	test_load();
	testing();
	return 0;
}

void b_write(Address addr, byte b) {				//writes b to addr address
	mem[addr] = b;
	return;
}
byte b_read(Address addr) {							//reads from addr address
	return *((byte*)(mem + addr));
}
word w_read(Address addr) {
	if(addr % 2 == 0)
		return *((word*)(mem + addr));
	else {
		assert(addr % 2 == 0);
	}
	return NULL;
}

void w_write(Address addr, word b) {
	if (addr % 2 == 0)
		*((word*)(mem + addr)) = b;
	else {
		assert(addr % 2 == 0);
	}
}


void load_file() {
	Address mem_addr = 0x0000;
	word N = 0x0000;

	byte inp = 0x00;
	word i;

	while (scanf("%4hx %4hx", &mem_addr, &N) > 1) {
		printf("%x = %d, %x = %d\n", mem_addr, mem_addr, N, N);
		for (i = 0x0000; i < N; i++) {
			printf("%x ", i);
			scanf("%2hhx", &inp);
			printf("%02hhx\n", inp);
			b_write(mem_addr + i, inp);
		}
	}
}
