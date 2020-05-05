#include "main.h"
#include "test.h"


int main(int argc, char * argv[]){
	if(argc > 1){									//tests if path was written
		test_load(argv[1]);							//in command line(not correct)
	}
	else{
		assert(argc > 1);
	}
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
	return -1;
}

void w_write(Address addr, word b) {
	if (addr % 2 == 0)
		(*((word*)(mem + addr))) = b;
	else {
		assert(addr % 2 == 0);
	}
}


void load_file(const char* filename) {
	Address mem_addr = 0x0000;
	word N = 0x0000;

	byte inp = 0x00;
	word i;
	
	FILE* fin = fopen(filename, "r");
	
	while (fscanf(fin ,"%4hx %4hx", &mem_addr, &N) > 1) {
		for (i = 0x0000; i < N; i++) {
			fscanf(fin ,"%2hhx", &inp);
			b_write(mem_addr + i, inp);
		}
	}
	fclose(fin);
}
