#include "main.h"


#define NO_PARAMS 0
#define HAS_DD 1
#define HaS_SS 2



void do_mov();
void do_halt();
void do_add();
void do_inc();
void do_nothing();

typedef struct{
	word mask;
	word opcode;
	char *opname;
	void (*do_func)(void);
	byte params;
} Command;

typedef struct{
	word addr;				//arg addr
	word val;				//arg value
} Arg;

Arg get_mr(word w);

void run();
