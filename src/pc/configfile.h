#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#ifndef PATH_MAX
# if defined(_WIN32)
#  include <windows.h>
#  ifndef PATH_MAX
#   define PATH_MAX MAX_PATH
#  endif
# elif defined(__APPLE__)
#  include <sys/syslimits.h>
# elif defined(__linux__)
#  include <linux/limits.h>
# elif defined(__FreeBSD__)
#  include <limits.h>
# endif
#endif

#ifndef PATH_MAX
# define PATH_MAX 4096
#endif

enum ConfigOptionType {
    CONFIG_TYPE_BOOL,
    CONFIG_TYPE_UINT,
    CONFIG_TYPE_FLOAT,
    CONFIG_TYPE_STRING,
};

struct ConfigOption {
    const char *name;
    enum ConfigOptionType type;
    union {
        bool *boolValue;
        unsigned int *uintValue;
        float *floatValue;
        char *stringValue;
    };
};


extern bool         configFullscreen;
extern char         configPluginDir[PATH_MAX];
extern unsigned int configKeyA;
extern unsigned int configKeyB;
extern unsigned int configKeyStart;
extern unsigned int configKeyR;
extern unsigned int configKeyZ;
extern unsigned int configKeyCUp;
extern unsigned int configKeyCDown;
extern unsigned int configKeyCLeft;
extern unsigned int configKeyCRight;
extern unsigned int configKeyStickUp;
extern unsigned int configKeyStickDown;
extern unsigned int configKeyStickLeft;
extern unsigned int configKeyStickRight;

void init_options();
void uninit_options();
void configfile_load(const char *filename);
void configfile_save(const char *filename);

#endif
