#include <string.h>
#include "../src_h/args.h"

int cmp_argv(char* actual_arg, const char* arg_full, const char* arg_short){
    if (strcmp(actual_arg, arg_full) == 0 || strcmp(actual_arg, arg_short) == 0){
        return 1;
    } else {
        return 0;
    }
}

char* get_flag_value(char* actual_argv, const char* pref){
    if (strncmp(actual_argv, pref, strlen(pref)) == 0) {  // strncmp проверит равен ли кусок аргумента до len(pref) префиксу
        return actual_argv + strlen(pref); // вернем то что после префикса
    } else {
        return NULL;
    }
}