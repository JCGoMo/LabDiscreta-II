#ifndef _GET_LINE
#define _GET_LINE
#include <stdbool.h>
#include <stdlib.h>
#include "EstructuraGrafo.h"
#include <string.h>
#include "get_line.h"


char* get_line(void);
void get_numbers(char*, u32, u32*, u32*);
bool checkline(char*, bool);

#endif