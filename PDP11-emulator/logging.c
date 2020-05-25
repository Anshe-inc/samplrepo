#include "logging.h"
#include "pdp11-mem.h"


extern word reg[];
extern byte is_traced;


void info(const char* format, ...){			//just for compiler
	va_list ap;
	
	va_start(ap, format);
	
	vfprintf(stdout,format, ap);
	
	va_end(ap);
}
void error(const char* format, ...){			//just for compiler
	va_list ap;
	
	va_start(ap, format);
	
	vfprintf(stderr,format, ap);
	
	va_end(ap);
}

void trace(const char * format, ...){		//here's a trace func
	if(is_traced){
		va_list ap;
	
		va_start(ap, format);
	
		vfprintf(stderr,format, ap);
	
		va_end(ap);
	}
	return;
}


void debug(const char* format, ...){			//just for compiler
	va_list ap;
	
	va_start(ap, format);
	
	vfprintf(stderr,format, ap);
	
	va_end(ap);
}

void dump(Address add, word N){			//dumps certain amount of data
	int i;
	trace("\nDumping data from 0x%04hx(%d) with 0x%04hx(%d) bytes\n", add, add, N, N);
	for (i = 0; i < N; i++) {
		trace("%02hhx\t", b_read(add + i));
	}
	trace("\n");
}

void dump_reg(){
	int i;
	for(i = 0; i < REGSIZE; i+=2){
		if(i == 6){
			info("sp=%06o\n", reg[i]);
			i = -1;
		}
		else if(i == 7){
			info("pc=%06o\n", reg[i]);
		}
		else{
			info("r%o=%06o\t", i, reg[i]);
		}
	}
}

void logging(const char* format, ...){			//just for compiler
	va_list ap;
	
	va_start(ap, format);
	
	vfprintf(stderr,format, ap);
	
	va_end(ap);
}