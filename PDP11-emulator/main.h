#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>
#include "test.h"

typedef char byte;				//8-bit
typedef unsigned short word;	//16-bit
typedef word Address;			//16-bit

#define MEMSIZE (64*1024)		//memor size 64kB

byte mem[MEMSIZE];

void b_write(Address addr, byte b);
byte b_read(Address addr);
void w_write(Address addr, word b);
word w_read(Address addr);

void load_file();
