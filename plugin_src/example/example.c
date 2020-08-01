#include <stdio.h>

#include "pc/plugins.h"

void loop_func()
{
	//printf("I get called every frame\n");
}

void init_func()
{
	printf("I get called when loaded\n");

	add_function(loop_func);
}

void deinit_func()
{
	printf("I get called when unloaded\n");
}