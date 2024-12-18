#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "building.h"

const char* developers[] = {"Skyline", "Horizon", "Pinnacle", "Nova", "Evergreen"};
const char* neighborhoods[] = {"Maplewood", "Cedar", "Bluewater", "Golden", "Silverstone"};
const char* types[] = {"Monolithic", "Brick", "Panel", "Frame", "Stone"};

int rand_int(int bot, int top) {
    return bot + rand() % (top - bot + 1);
}

float rand_float(float bot, float top) {
    return bot + (float)rand() / RAND_MAX * (top - bot + 1);
}

char* rand_string(const char* arr[], int len) {
    int i = rand_int(0, len - 1);
    return strdup(arr[i]);
}

void generate_building(building* b) {
    b->developer = rand_string(developers, 5);
    b->neighborhood = rand_string(neighborhoods, 5);
    b->type = rand_string(types, 5);
    b->year = rand_int(1900, 2024);
    b->has_lift = rand_int(0, 1);
    b->has_trash = rand_int(0, 1);
    b->apartaments_count = rand_int(10, 200);
    b->floors_count = rand_int(1, 15);
    b->avg_area = rand_float(20, 50);
}

const char* convert_bin(short h) {
    if (h == 1){
        return "YES";
    } else{
        return "NO";
    }
}

void parse_building(char* line, building* b) {
    void* fields[] ={
        &b->developer, &b->neighborhood, &b->type,
        &b->year, &b->has_lift, &b->has_trash, 
        &b->apartaments_count, &b->floors_count, 
        &b->avg_area 
    };
    
    size_t fields_count = sizeof(fields) / sizeof(fields[0]);

    char* token = strtok(line, ",");
    for (size_t i = 0; i < fields_count; i++){
        if (i < 3){
            *(char* *)fields[i] = strdup(token);
        } else if (i < 4){
            *(int *)fields[i] = atoi(token);
        } else if (i < 6) {

            if (strcmp("YES", token)) {
                *(int *)fields[i] = 1;
            } else if (strcmp("NO", token)){
                *(int *)fields[i] = 0;
            } else {
                *(int *)fields[i] = atoi(token);
            }

        }else if (i < 8){
            *(int *)fields[i] = atoi(token);
        }else {
            *(float *)fields[i] = atof(token);
        }

        token = strtok(NULL, ",");
    }
}