#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "io.h"

void print_building(vector v) {
    printf("Developer,Neighborhood,Type,Year,Lift,Trash,Apartments,Floors,Avg_area\n\n");
    for (int i = 0; i < v.size; i++){
        printf("%s, %s, %s, %d, %s, %s, %d, %d, %.2f\n", 
        v.data[i].developer,
        v.data[i].neighborhood,
        v.data[i].type,
        v.data[i].year,
        convert_bin(v.data[i].has_lift),
        convert_bin(v.data[i].has_trash),
        v.data[i].apartaments_count,
        v.data[i].floors_count,
        v.data[i].avg_area
        );
    }
}

void console_input(vector* v){
    int qty;
    printf("Enter the number of buildings to fill: ");
    scanf("%d", &qty);
    printf("Enter building details:\n(format: developer,neighborhood,type,year,lift,trash,apartments,floors,avg_area)\n");
    while (getchar() != '\n');
    for (int i = 0; i < qty; i++){
        building b;
        char* line = NULL;
        size_t len = 0;
        getline(&line, &len, stdin);
        parse_building(line, &b);
        add_element(v, b);
        free(line);
    }
    printf("\n");
}

void take_from_file(char* file_name, vector* v){
    FILE* file = fopen(file_name, "r");
    if (!file) {
        printf("Program can't open input file\n");
        return;
    }
    char* line = NULL;
    size_t len = 0;
    while (getline(&line, &len, file) != -1) {
        building b;
        parse_building(line, &b);
        add_element(v, b);
    }
    free(line);
    fclose(file);
    printf("Data was succesfully taken from %s\n", file_name);
}

void save_to_file(char* file_name, vector v){
    FILE* file = fopen(file_name, "w");
    for (int i = 0; i < v.size; i++) {
        fprintf(file, "%s,%s,%s,%d,%s,%s,%d,%d,%.2f\n", 
        v.data[i].developer,
        v.data[i].neighborhood,
        v.data[i].type,
        v.data[i].year,
        convert_bin(v.data[i].has_lift),
        convert_bin(v.data[i].has_trash),
        v.data[i].apartaments_count,
        v.data[i].floors_count,
        v.data[i].avg_area
        );
    }

    fclose(file);
    printf("Data was succesfully saved in %s\n", file_name);
}
