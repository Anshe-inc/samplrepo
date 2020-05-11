#include "logging.h"


extern word reg[];

void info(const char* txt, ...){			//just for compiler
	printf(txt);
}
void error(const char* txt, ...){			//just for compiler
	printf(txt);
}

void trace(const char * format, ...){		//here's a trace func
	va_list ap;
	
	va_start(ap, format);
	
	vfprintf(stderr,format, ap);
	
	va_end(ap);
}


void debug(const char* txt, ...){			//just for compiler
	printf(txt);
}

void dump(Address add, word N){			//dumps certain amount of data
	word i;
	trace("\nDumping data from 0x%04hx(%d) with 0x%04hx(%d) bytes\n", add, add, N, N);
	for (i = 0; i < N; i++) {
		trace("%02hhx\t", b_read(add + i));
	}
	trace("\n");
}

void dump_reg(){
	byte i;
	for(i = 0; i < REGSIZE; i+=2){
		if(i == 6){
			trace("sp=%06o\n", reg[i]);
			i = -1;
		}
		else if(i == 7){
			trace("pc=%06o\n", reg[i]);
		}
		else{
			trace("r%o=%06o\t", i, reg[i]);
		}
	}
}

void logging(const char* txt, ...){			//just for compiler
	printf(txt);
}