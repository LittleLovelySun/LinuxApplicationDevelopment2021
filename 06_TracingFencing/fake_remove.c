#define _GNU_SOURCE
#include <dlfcn.h>
#include "stdio.h"
#include "string.h"
#include "unistd.h"
 
typedef int (*orig_unlink_f_type)(const char*);
 

int unlink(const char* file_name) {
    orig_unlink_f_type orig_unlink = (orig_unlink_f_type)dlsym(RTLD_NEXT, "unlink");

    if (strstr(file_name, "PROTECT") != NULL)
        return 0;
    
    return orig_unlink(file_name);
}