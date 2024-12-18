#pragma once

int cmp_argv(char* actual_arg, const char* arg_full, const char* arg_short);

char* get_flag_value(char* actual_argv, const char* pref);