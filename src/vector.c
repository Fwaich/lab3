#include <stdlib.h>
#include "../src_h/vector.h"

void init_vector(vector* v) {
    v->size = 0;
    v->capacity = 10;
    v->data = (building *)malloc(sizeof(building) * v->capacity);
}

void add_element(vector* v, building el) {
    if (v->size == v->capacity){
        v->capacity *= 2;
        v->data = (building *)realloc(v->data, sizeof(building) * v->capacity);
    }
    v->data[v->size++] = el;
}

void clear_vector(vector* v) {
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

void swap_elements(vector* v, int ind1, int ind2) {
    building tmp = v->data[ind1];
    v->data[ind1] = v->data[ind2];
    v->data[ind2] = tmp;
}

void fill_vector(vector* v, int r) {
    for (int i = 0; i < r; i++){
        building b;
        generate_building(&b);
        add_element(v, b);
    }
}