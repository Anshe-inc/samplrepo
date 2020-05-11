#include "main.h"
#include <stdarg.h>


#define ERROR 0
#define INFO 1
#define TRACE 2
#define DEBUG 3

void dump(Address add, word N);
void dump_reg();
void info(const char* txt, ...);
void error(const char* txt, ...);
void trace(const char* txt, ...);		//traces info(work like printf, but to stderr)
void debug(const char* txt, ...);

void logging(const char* txt, ...);