#ifndef _PC_SHAREDLIBS_H
#define _PC_SHAREDLIBS_H

#if defined(_WIN32)
# include <windows.h>
# define LIBEXT ".dll"
# define dlopen(lib, flag) LoadLibrary(TEXT(lib))
# define dlerror() ""
# define dlsym(handle, func) (void *)GetProcAddress(handle, func)
# define dlclose(handle) FreeLibrary(handle)
#elif defined(__APPLE__)
# include <dlfcn.h>
# define LIBEXT ".dylib"
#elif defined(__linux__) || defined(__FreeBSD__) // lets make the bold assumption for FreeBSD
# include <dlfcn.h>
# define LIBEXT ".so"
#else
# error Unknown System
#endif

#endif