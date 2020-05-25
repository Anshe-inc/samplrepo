#include "main.h"
#include "test.h"

byte is_traced = 0;



int main(int argc, char * argv[]){
	if(argc > 1){									//tests if path was written
		if(strstr("-t", argv[1]) != NULL){
			is_traced = 1;
		}
		test_load(argv[argc - 1]);							//to command line(not correct)
	}
	else{
		assert(argc > 1);
	}
	testing();
	return 0;
}