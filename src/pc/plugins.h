#ifndef _PC_PLUGINS_H
#define _PC_PLUGINS_H

void load_plugins();
void unload_plugins();

void run_functions();
void add_function(void (*func)());

#endif
