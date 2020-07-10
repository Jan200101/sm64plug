#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <dlfcn.h>

#include "plugins.h"
#include "sharedlibs.h"
#include "configfile.h"

struct {
    size_t size;
    void **handles;
} plugins;

// struct containing a list of functions to run every frame
struct {
    size_t size;
    void (**list)()    
} functions;


void load_plugins() {
    DIR *dir;
    struct dirent *ent;
    plugins.size = 0;

    char path[PATH_MAX];
    void (*init_func)();

    functions.size = 0;
    functions.list = NULL;

    // looks for files in the plugin folder
    // then tries dynamically loading them and storing the handle
    if ((dir = opendir (configPluginDir)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if (ent->d_name[0] == '.') continue;

            if (!plugins.size)
                plugins.handles = malloc(sizeof(void*) * plugins.size+1);
            else
                realloc(plugins.handles, sizeof(void*) * plugins.size+1);
            plugins.handles[plugins.size] = malloc(sizeof(void));

            sprintf(path, "%s/%s", configPluginDir, ent->d_name);

            plugins.handles[plugins.size] = dlopen(path, RTLD_NOW);

            if (plugins.handles[plugins.size])
            {
                init_func = dlsym(plugins.handles[plugins.size], "init_func");

                if (init_func)
                {
                    printf("[plugins] loaded \"%s\"\n", ent->d_name);
                    init_func();
                }
                else
                {
                    printf("[plugins] plugin \"%s\" has no init function\n", ent->d_name);
                }
            }
            else
            {
                printf("[plugins] unable to load \"%s\": %s\n", ent->d_name, dlerror());
            }


            ++plugins.size;
        }
        closedir (dir);
    }
}

void unload_plugins() {
    void (*deinit_func)();

    for (size_t i = 0; i < plugins.size; ++i)
    {
        if (plugins.handles[i])
        {
            deinit_func = dlsym(plugins.handles[i], "deinit_func");
            if (deinit_func) deinit_func();
            dlclose(plugins.handles[i]);
        }
    }
}

void add_function(void (*func)())
{
    if (!functions.size)
        functions.list = malloc(sizeof(void (*)()) * functions.size+1);
    else
        realloc(functions.list, sizeof(void (*)()) * functions.size+1);

    functions.list[functions.size] = malloc(sizeof(void (*)()));

    functions.list[functions.size] = func;

    ++functions.size;
}

void run_functions()
{
    for (size_t i = 0; i < functions.size; ++i)
    {
        if(functions.list[i]) functions.list[i]();
    }
}