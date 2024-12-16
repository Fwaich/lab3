#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../src_h/building.h"
#include "../src_h/vector.h"
#include "../src_h/sort.h"
#include "../src_h/args.h"
#include "../src_h/io.h"

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