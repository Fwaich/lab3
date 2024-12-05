#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// int rand_int(int bot, int top);
// float rand_float(float bot, float top);
// const char* rand_string(const char* arr[], int len);

const char* developers[] = {"СтройГрад", "ДомБуд", "МонолитПлюс"};
const char* neighborhoods[] = {"Северный район", "Центральный район", "Западный район"};
const char* types[] = {"панельный", "кирпичный", "монолитный"};

typedef struct{

    const char* developer;
    const char* neighborhood;
    const char* type;
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
    v->size = 0;
    v->capacity = 0;
}

int cmp(vector* v, int ind1, int ind2){
    int n = 0;
    if (v->data[ind1].year > v->data[ind2].year){
        n = 1;
    } else if (v->data[ind1].year < v->data[ind2].year) {
        n = -1;
    } else  if (v->data[ind1].has_lift > v->data[ind2].has_lift){
        n = 1;
    } else if (v->data[ind1].has_lift < v->data[ind2].has_lift) {
        n = -1;
    } else if (v->data[ind1].has_trash > v->data[ind2].has_trash){
        n = 1;
    } else if (v->data[ind1].has_trash < v->data[ind2].has_trash) {
        n = -1;
    } else if (v->data[ind1].apartaments_count > v->data[ind2].apartaments_count){
        n = 1;
    } else if (v->data[ind1].apartaments_count < v->data[ind2].apartaments_count) {
        n = -1;
    } else if (v->data[ind1].floors_count > v->data[ind2].floors_count){
        n = 1;
    } else if (v->data[ind1].floors_count < v->data[ind2].floors_count) {
        n = -1;
    } else if (v->data[ind1].avg_area > v->data[ind2].avg_area){
        n = 1;
    } else if (v->data[ind1].avg_area < v->data[ind2].avg_area) {
        n = -1;
    }
    return n;
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

int rand_int(int bot, int top) {
    return bot + rand() % (top - bot + 1);
}

float rand_float(float bot, float top) {
    return bot + (float)rand() / RAND_MAX * (top - bot + 1);
}

const char* rand_string(const char* arr[], int len) { //важно после arr чтоб было []
    int i = rand_int(0, len - 1);
    return arr[i];
}

void generate_building(building* b) {
    b->developer = rand_string(developers, 3);
    b->neighborhood = rand_string(neighborhoods, 3);
    b->type = rand_string(types, 3);
    b->year = rand_int(1900, 2024);
    b->has_lift = rand_int(0, 1);
    b->has_trash = rand_int(0, 1);
    b->apartaments_count = rand_int(10, 200);
    b->floors_count = rand_int(1, 15);
    b->avg_area = rand_float(10, 50);
}

int main(){
    srand(time(NULL));
    // printf("hi!\n");
    // for (int i = 0; i < 100; i++) {
    //     float num = rand_float(10, 50);
    //     printf("%f\n", num);
    // }
    // int len = sizeof(developers) / sizeof(developers[0]);
    // const char* word = rand_string(developers, len);
    vector v;
    init_vector(&v);
    for (int i = 0; i < 11; i++){
        building b;
        generate_building(&b);
        add_element(&v, b); //проблема в увеличении памяти для вектора
    }

    for (int i =0; i < 11; i++){
        printf("%d\n", v.data[i].year);
    }
    return 0;
}