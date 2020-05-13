#include "pdp_run.h"
#define pc reg[7]


extern byte mem;
word reg[REGSIZE];

Arg ss, dd, nn, r, xx;

Command com[] = {									//contains all info about operators
	{ 0170000, 0010000, "mov", do_mov, HAS_SS | HAS_DD },
	{ 0170000, 0060000, "add", do_add, HAS_SS | HAS_DD },
	{ 0077000, 0050000, "clr", do_clr, HAS_DD },
	{ 0077000, 0077000, "sob", do_sob, HAS_R | HAS_NN },
	{ 0007700, 0005200, "inc", do_inc, HAS_SS },
	{ 0xffff, 0000000, "halt", do_halt, 0 }
};

void run(){											//test run(bad)
	pc = 01000;
	word w;
	word i, j;
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
				/*if(strcmp(com[i].opname, "mov") == 0){
					ss = get_mr(w >> 6);
					dd = get_mr(w);
				}
				if(strcmp(com[i].opname, "add") == 0){
					ss = get_mr(w >> 6);
					dd = get_mr(w);
				}*/
				if(com[i].params & HAS_SS){
					ss = get_mr(w >> 6);
				}
				if(com[i].params & HAS_DD){
					dd = get_mr(w);
				}
				if(com[i].params & HAS_R){
					r = get_r(w >> 6);
				}
				if(com[i].params & HAS_NN){
					nn = get_nn(w);
				}
				/*if(w & HAS_XX){
					xx = get_mr(w);
				}*/
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
	trace("\n---------------- halted ---------------\n");
	dump_reg();
	dump(0x0200, 0x0010);
	dump(0x0, 0x0008);
	exit(0);
}

// MOV
void do_mov(){
	reg[dd.addr] = ss.val;
	if(dd.mode == 0){							//checks b mode
		trace("\n%1d_write(%06o, %06o)\n",dd.mode, dd.addr, ss.val);
		w_write(dd.addr, ss.val);
	}
}

// ADD
void do_add(){
	reg[dd.addr] += ss.val;
}


void do_inc(){
	reg[dd.addr] += 2 - dd.mode;
}

void do_sob(){
	byte regist = r.val;
	if(reg[regist] != 0){
		reg[regist]--;
		pc = pc - 2*nn.val;
	}
	else
		return;
}

void do_clr(){
	reg[dd.addr] = 0;
	
}


void do_nothing(){
	trace("unknown");
}


Arg get_mr(word w){
	Arg res;
	byte regist = w & 0007;			// reg number
	byte mode = (w >> 3) & 7;		// mode number
	byte is_byte = (w >> 16) & 1;
	res.mode = is_byte;
	
	switch(mode){
		case 0:					// Rx
			res.mode = 1;
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
				trace(" #%o ", res.val);
			}
			else{
				trace(" (R%o)+ ", regist);
			}
			break;
		case 3:
			res.addr = reg[regist];
			res.addr = w_read(res.addr);
			res.val = w_read(res.addr);
			if(regist == 7){
				trace(" @#%o ", res.addr);
			}
			else{
				trace(" @(R%o)+ ", regist);
			}
			reg[regist] += 2;
			
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
			trace(" -(R%o) ", regist);
			break;
		default:
			fprintf(stderr, "MODE %o NOT IMPLEMENTED YET", regist);
			exit(1);
	}
	return res;
}

Arg get_nn(word w){
	Arg res;
	word num = w & 077;
	
	res.val = num;
	
	return  res;
	
}
Arg get_r(word w){
	Arg res;
	byte num = w & 07;
	
	res.val = num;
	
	return res;
	
}