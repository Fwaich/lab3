#pragma once
#include "building.h"

typedef struct{
    building* data;
    int capacity;
    int size;
}vector;

void init_vector(vector* v);

void add_element(vector* v, building el);

void clear_vector(vector* v);

void swap_elements(vector* v, int ind1, int ind2);

void fill_vector(vector* v, int r);