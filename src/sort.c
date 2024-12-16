#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include "../src_h/sort.h"

void buble_sort(vector* v,int (*comp)(building* b1, building* b2), int s) {
    for (int i = 0; i < v->size - 1; i++){
        for (int j = 0; j < v->size - i - 1; j++) {
            if (comp(&v->data[j], &v->data[j + 1]) == s) {
                swap_elements(v, j, j + 1);
            }
        }
    }
    printf("Data was succesfully sorted\n");
}

int compare_string(char* st1, char* st2) {
    if (st1 == st2){
        return 0;
    }
    char sym1;
    char sym2;
    char* abt = "abcdefghijklmnopqrstuvwxyz"; 
    for (int i = 0; st1[i] != '\0'; i++) { 
        if  (st2[i] == '\0') {
            return 1;
        }
        sym1 = tolower(st1[i]);
        sym2 = tolower(st2[i]);
        if (sym1 != sym2) {
            break;
        }
    }

    for (int i = 0; abt[i] != '\0'; i++) {
        if (sym1 == abt[i]){
            return 1;
        }
        if (sym2 == abt[i]) {
            return -1;
        }
    }
}

int cmp(building* b1, building* b2){
    int n = 0;
    n = compare_string(b1->developer, b2->developer);
    if (n != 0) {
        return n;
    }
    n = compare_string(b1->neighborhood, b2->neighborhood);
    if (n != 0) {
        return n;
    }
    n = compare_string(b1->type, b2->type);
    if (n != 0) {
        return n;
    }
    if (b1->year > b2->year){
        n = 1;
    } else if (b1->year < b2->year) {
        n = -1;
    } else  if (b1->has_lift > b2->has_lift){
        n = 1;
    } else if (b1->has_lift < b2->has_lift) {
        n = -1;
    } else if (b1->has_trash > b2->has_trash){
        n = 1;
    } else if (b1->has_trash < b2->has_trash) {
        n = -1;
    } else if (b1->apartaments_count > b2->apartaments_count){
        n = 1;
    } else if (b1->apartaments_count < b2->apartaments_count) {
        n = -1;
    } else if (b1->floors_count > b2->floors_count){
        n = 1;
    } else if (b1->floors_count < b2->floors_count) {
        n = -1;
    } else if (b1->avg_area > b2->avg_area){
        n = 1;
    } else if (b1->avg_area < b2->avg_area) {
        n = -1;
    }
    return n;
}

