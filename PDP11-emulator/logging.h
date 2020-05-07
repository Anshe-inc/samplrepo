#include "main.h"
#include <stdarg.h>


#define ERROR 0
#define INFO 1
#define TRACE 2
#define DEBUG 3


void info(const char* txt, ...);
void error(const char* txt, ...);
void trace(const char* txt, ...);
void debug(const char* txt, ...);

void logging(const char* txt, ...);