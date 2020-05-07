#include "logging.h"


extern word reg[];

void info(const char* txt, ...){
	printf(txt);
}
void error(const char* txt, ...){
	printf(txt);
}

void trace(const char * format, ...){
	va_list ap;
	
	va_start(ap, format);
	
	vfprintf(stderr,format, ap);
	
	va_end(ap);
}


void debug(const char* txt, ...){
	printf(txt);
}

void logging(const char* txt, ...){
	printf(txt);
}