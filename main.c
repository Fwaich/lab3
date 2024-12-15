#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

const char* developers[] = {"Skyline", "Horizon", "Pinnacle", "Nova", "Evergreen"};
const char* neighborhoods[] = {"Maplewood", "Cedar", "Bluewater", "Golden", "Silverstone"};
const char* types[] = {"Monolithic", "Brick", "Panel", "Frame", "Stone"};

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

void swap_elements(vector* v, int ind1, int ind2) {
    building tmp = v->data[ind1];
    v->data[ind1] = v->data[ind2];
    v->data[ind2] = tmp;
}

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

void fill_vector(vector* v, int r){
    for (int i = 0; i < r; i++){
        building b;
        generate_building(&b);
        add_element(v, b);
    }
}

const char* convert_bin(short h) {
    if (h == 1) {
        return "YES";
    } else {
        return "NO";
    }
}

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

void parse_building(char* line, building* b){
    void* fields[] = {
        &b->developer, &b->neighborhood, &b->type,
        &b->year, &b->has_lift, &b->has_trash, 
        &b->apartaments_count, &b->floors_count, 
        &b->avg_area 
    };
    
    size_t fields_count = sizeof(fields) / sizeof(fields[0]);

    char* token = strtok(line, ",");
    for (size_t i = 0; i < fields_count; i++){
        if (i < 3) {
            *(char* *)fields[i] = strdup(token);
        } else if (i < 8) {
            *(int *)fields[i] = atoi(token);
        } else {
            *(float *)fields[i] = atof(token);
        }

        token = strtok(NULL, ",");
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
    char* line = NULL;
    size_t len = 0;
    while (getline(&line, &len, file) != -1) {
        building b;
        printf("%s\n", line);
        parse_building(line, &b);
        add_element(v, b);
    }
    free(line);
    fclose(file);
    printf("Data was succesfully taken from %s\n", file_name);
}

void save_to_file(char* file_name, vector v){
    FILE* file = fopen(file_name, "w");
    fprintf(file, "Developer,Neighborhood,Type,Year,Lift,Trash,Apartments,Floors,Avg_area\n\n" );

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

int cmp_argv(char* actual_arg, const char* arg_full, const char* arg_short){
    if (strcmp(actual_arg, arg_full) == 0 || strcmp(actual_arg, arg_short) == 0){
        return 1;
    } else {
        return 0;
    }
}

char* get_flag_value(char* actual_argv, const char* pref){
    if (strncmp(actual_argv, pref, strlen(pref)) == 0) {  // strncmp проверит равен ли кусок аргумента до len(pref) префиксу
        return actual_argv + strlen(pref); // вернем то что после префикса
    } else {
        return NULL;
    }
}

int main(int argc, char* argv[]){

    if (argc <= 1) {
        printf("No arguments\n");
        return 0;
    }
    int i = 1;
    vector vec;
    char* file_name = NULL;
    int out = 0;

    if (!(cmp_argv(argv[1], "--in=", "-i") || cmp_argv(argv[1],"--generate", "-g"))){
        printf("You didn't set input or generate flags. Enter data manully\n");
        init_vector(&vec);
        console_input(&vec);
    }

    while (i < argc) {

        file_name = get_flag_value(argv[i], "--in=");
        if (file_name) {
            init_vector(&vec);
            take_from_file(file_name, &vec);
            i++;
            continue;
        }

        if (cmp_argv(argv[i], "", "-i")) {
            if (i + 1 >= argc){
                printf("Missing output file after %s\n", argv[i]);
                return 1;
            }
            file_name = argv[i + 1];
            init_vector(&vec);
            take_from_file(file_name, &vec);
            i += 2;
            continue;
        }

        if (cmp_argv(argv[i], "--generate", "-g")) {
            if (i + 1 >= argc) {
                printf("Missing number of rows after %s\n", argv[i]);
                return 1;
            }
            int rows = atoi(argv[i + 1]);
            if (rows > 0) {
                init_vector(&vec);
                srand(time(NULL));
                fill_vector(&vec, rows);
                i += 2;
                print_building(vec);
                printf("Data was successfully generated\n");
                continue;
            } else {
                printf("Invalid number of rows\n");
                return 1;
            }
        }

        // printf("%d\n %s\n", i, argv[i]);
        if (cmp_argv(argv[i], "--sort", "-s")) {
            int type = -1;
            if (i + 1 < argc){
                char* sort_type = get_flag_value(argv[i + 1], "--type=");
                if (sort_type && cmp_argv(sort_type, "asc", "")){
                    i++;
                }
                
                if (sort_type && cmp_argv(sort_type, "desc", "")) {
                    type = 1;
                    i++;
                }
                printf("*%s* %d %s\n", sort_type, type, argv[i]);

                if (i + 2 < argc && cmp_argv(argv[i + 1], "", "-t")) {
                    if (cmp_argv(argv[i + 2], "", "D")) {
                        type = 1;
                    }

                    i += 2;
                }
            }
            buble_sort(&vec, cmp, type);
            i++;
            continue;
        }

        file_name = get_flag_value(argv[i], "--out=");
        if (file_name){
            save_to_file(file_name, vec);
            out = 1;
            i++;
            continue;
        }

        if (cmp_argv(argv[i], "", "-o")) {
            if (i + 1 >= argc){
                printf("Missing input file after %s\n", argv[i]);
                return 1;
            }
            file_name = argv[i + 1];
            save_to_file(file_name, vec);
            out = 1;
            i += 2;
            continue;
        }

        printf("Unknown argument %s\n", argv[i]);
        i++;

    }  
        if (out == 0) {
            printf("You didn't set out flags.Program will print data here:\n");
            print_building(vec);
        } 
        clear_vector(&vec);

    return 0;
}