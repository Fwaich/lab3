#include <stdio.h>
#include <stdlib.h>

const char* developers[] = {"СтройГрад", "ДомБуд", "МонолитПлюс"};
const char* neighborhoods[] = {"Северный район", "Центральный район", "Западный район"};
const char* types[] = {"панельный", "кирпичный", "монолитный"};

typedef struct{

    char developer[50];
    char neighborhood[50];
    char type[50];
    int year;
    int has_lift;
    int has_trash;
    int apartaments_count;
    int floors_count;
    float avg_area;

}building;

typedef struct{
    building* data; //это и есть массив
    int capacity;
    int size;
}vector;

void init_vector(vector* v){
    v->size = 0;
    v->capacity = 10;
    v->data = (building *)malloc(sizeof(building) * v->capacity);
}

void add_element(vector* v, building el){
    if (v->size == v->capacity) {
        v->capacity *= 2;
        v->data = (building *)realloc(v, sizeof(building) * v->capacity);
    }
    v->data[v->size++] = el;
}

void clear_vector(vector* v) {
    free(v->data);
    v->data = NULL;
    v->size = v->capacity = 0;
}

void swap_elements(vector* v, int ind1, int ind2) {
    building tmp = v->data[ind1];
    v->data[ind1] = v->data[ind2];
    v->data[ind2] = tmp;
}

void buble_sort(vector* v) {
    for (int i = 0; i < v->size - 1; i++){
        for (int j = 0; j < v->size - i - 1; j++) {       // возможно стоит i - 2 делать
            if (v->data[j].year > v->data[j + 1].year) {
                swap_elements(v, j, j + 1);
            }
        }
    }
}

int main(){
    printf("hi!\n");

    return 0;
}