#pragma once

extern const char* developers[];
extern const char* neighborhoods[];
extern const char* types[];

typedef struct{

    char* developer;
    char* neighborhood;
    char* type;
    int year;
    short has_lift;
    short has_trash;
    int apartaments_count;
    int floors_count;
    float avg_area;

}building;

int rand_int(int bot, int top);

float rand_float(float bot, float top);

char* rand_string(const char* arr[], int len);

void generate_building(building* b);

const char* convert_bin(short h);

void parse_building(char* line, building* b);
