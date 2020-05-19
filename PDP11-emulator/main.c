#include "main.h"
#include "test.h"



int main(int argc, char * argv[]){
	if(argc > 1){									//tests if path was written
		test_load(argv[1]);							//to command line(not correct)
	}
	else{
		assert(argc > 1);
	}
	testing();
	return 0;
}