#include "pdp_run.h"
#define pc reg[7]


extern byte mem;
word reg[REGSIZE];

Arg ss, dd;

Command com[] = {
	{ 0170000, 0010000, "mov", do_mov },
	{ 0170000, 0060000, "add", do_add },
	{ 0007700, 0005200, "inc", do_inc },
	{ 0xffff, 0000000, "halt", do_halt }
};

void run(){	
	pc = 01000;
	word w;
	word i;
	word len_com = sizeof(com)/ sizeof(com[0]);
	while(1){
		w = w_read(pc);
		trace("%06o %06o:", pc, w);
		pc += 2;
		if(w == 0){
			do_halt();
		}
		
		for(i = 0; i < len_com; i++){
			if((w & com[i].mask) == com[i].opcode){
				trace(com[i].opname);
				if(strcmp(com[i].opname, "mov") == 0){
					ss = get_mr(w >> 6);
					dd = get_mr(w);
				}
				if(strcmp(com[i].opname, "add") == 0){
					ss = get_mr(w >> 6);
					dd = get_mr(w);
				}
				com[i].do_func();
				break;
				
			}
			if(i == len_com - 1){
				do_nothing();
				break;
			}
		}
		trace("\n");
		
	}
}

void do_halt(){
	trace("halt");
	byte i;
	trace("\n---------------- halted ---------------\n");
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
	//dump(0x0,0xc);
	exit(0);
}


void do_mov(){
	reg[dd.addr] = ss.val;
	w_write(dd.addr, ss.val);	
}


void do_add(){
	reg[dd.addr] += ss.val;
}


void do_inc(){
	trace("inc");
}


void do_nothing(){
	trace("unknown");
}


Arg get_mr(word w){
	Arg res;
	byte regist = w & 0007;			// reg number
	byte mode = (w >> 3) & 7;		// mode number
	byte is_byte = (w >> 16) & 1;
	
	
	switch(mode){
		case 0:					// Rx
			res.addr = regist;
			res.val = reg[regist];
			trace(" R%o ", regist);
			break;
		case 1:					//(Rx)
			res.addr = reg[regist];
			if(is_byte)
				res.val = b_read(res.addr);
			else
				res.val = w_read(res.addr);
			trace(" (R%o) ", regist);
			break;
		case 2:					//(Rx)+
			res.addr = reg[regist];
			
			if(is_byte){			//byte or word + sp & pc
				res.val = b_read(reg[regist]);
				reg[regist] += 1 + (regist > 5); //sum 2 if sp & pc
			}
			else{
				res.val = w_read(reg[regist]);
				reg[regist] += 2;
			}
			
			if(regist == 7){
				trace(" #%o,", res.val);
			}
			else{
				trace(" (R%o)+ ", regist);
			}
			break;
		case 4:					//-(Rx)
			if(is_byte){
				reg[regist] -= 1 + (regist > 5); // subst 2 if sp & pc
				res.addr = reg[regist];
				res.val = b_read(reg[regist]);
			}
			else{
				reg[regist] -= 2;
				res.addr = reg[regist];
				res.val = w_read(reg[regist]);
			}
			trace(" -(R%o)", regist);
			break;
		default:
			fprintf(stderr, "MODE %o NOT IMPLEMENTED YET", regist);
			exit(1);
	}
	return res;
}