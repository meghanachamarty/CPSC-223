#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pirate_list.h"

const int INITIAL_CAPACITY = 5; 

int main(int argc, char* argv[]) {
    if (argc < 3){
        exit(1); 
    }

    FILE *infile;
    infile = fopen(argv[1], "r");

    if (infile == NULL) {
        exit(1);
    }

    pirate_list *lst = list_create();

    int i;
    i=0;  

    char label[65];
    char value[65];
    char labelname[5]= "name"; 
    //char labelcaptain[8]= "captain";
    char labeltitle[6]= "title";
    char labelvessel[7]= "vessel";
    char labelport[5]= "port";
    char labeltreasure[9]= "treasure";
    char labelskill[6]="skill";

    pirate *p;

    while (fscanf(infile, "%99[^:]: %99[^\n]\n", label, value) == 2){
       
        if (strcmp(labelname, label) == 0){
            p = malloc(sizeof(pirate)*1); 
            p->pirate_name = malloc (sizeof(char)*64); 
            strcpy(p->pirate_name, value); 
            list_insert(lst, p, i);
            i++; 
        }

        if (strcmp(labeltitle, label) == 0){
            p->title = malloc (sizeof(char)*64);
            strcpy(p->title, value); 
        }

        if (strcmp(labelvessel, label) == 0){
            p->vessel = malloc (sizeof(char)*64);
            strcpy(p->vessel, value);
        }

        if (strcmp(labelport, label) == 0){
            p->port = malloc (sizeof(char)*64);
            strcpy(p->port, value);
        }

        if (strcmp(labeltreasure, label) == 0){
            p->treasure = atoi(value);
        }

        if (strcmp(labelskill, label) == 0){
            if (p->skill_capacity ==0){
                p->skill_list = malloc (sizeof(skill)* INITIAL_CAPACITY);
                p->skill_capacity = INITIAL_CAPACITY; 
                p->skill_length = 0; 
                p->skill_list->skillcount = 0; 
            }

            int found_flag; 
            for (i=found_flag=0; i < p->skill_length; i++){
                if (strcmp(value, p->skill_list[i].skill)==0){
                    p->skill_list->skillcount++;
                    found_flag=1;
                    break;
                }
            }

            if (!found_flag){
                if (p->skill_capacity == p->skill_length){
                    p->skill_capacity = p->skill_capacity + INITIAL_CAPACITY;
                    p->skill_list = realloc(p->skill_list, p->skill_capacity); 
                }
                strcpy(p->skill_list[p->skill_length].skill, value); 
                    p->skill_length++; 
            }
        }

    }
    fclose(infile);

    for (int i = 0; i < list_length(lst); i++){
        pirate *x; 
        x = list_access(lst, i); 
        char* print_name= x->pirate_name; 
        printf("%s\n", print_name);
        free(x); 
    }
    list_destroy(lst);
    return 0;
}
