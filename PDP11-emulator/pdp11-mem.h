#include "main.h"
#include "logging.h"
#include "test.h"


void b_write(Address addr, byte b);
byte b_read(Address addr);
void w_write(Address addr, word b);
word w_read(Address addr);

void load_file();