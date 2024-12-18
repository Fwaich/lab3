#pragma once
#include "vector.h"
#include "building.h"

void buble_sort(vector* v,int (*comp)(building* b1, building* b2), int s);

int compare_string(char* st1, char* st2);

int cmp(building* b1, building* b2);