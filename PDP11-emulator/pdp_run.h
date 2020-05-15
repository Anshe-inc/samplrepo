#include "main.h"


#define NO_PARAMS 0			//for 'byte params'
#define HAS_DD 1
#define HAS_SS 2
#define HAS_NN 4
#define HAS_R 8
#define HAS_XX 16




void do_mov();
void do_halt();
void do_add();
void do_inc();
void do_clr();
void do_sob();
void do_nothing();

typedef struct{
	word mask;
	word opcode;
	char *opname;
	void (*do_func)(void);
	unsigned char params;
} Command;

typedef struct{
	word addr;				//arg addr
	word val;				//arg value
	byte is_byte;			//byte or word
} Arg;

Arg get_mr(word w);
Arg get_nn(word w);
Arg get_r(word w);

void run();
