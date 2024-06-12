// hookbook.c
// Meghana Chamarty
// mc3547
// CS223 HW#3
// 3/14/2023
// This file includes main.c and it takes takes an input file of names,
// sorts them, and outputs them. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pirate_list.h"
#include "pirate.h"

int main(int argc, char* argv[]) {
    
    if (argc < 2){
        exit(1); 
    }
// inputs file included as an argument and opens it. Exits if file is NULL. 
    FILE *infile;
    infile = fopen(argv[1], "r");

    if (infile == NULL) {
        exit(1);
    }
   
    char name[65];

    pirate_list *lst = list_create();

// reads names from file, stores them in character pointer, inserts pointer to pirate_list
     while (fgets(name, 65, infile) != NULL) {
     int len = strlen(name);

// adds \n to end of string if it does not end in \n.
     if (len > 0 && name[len-1] != '\n') {
            pirate *p;
            p = malloc(sizeof(pirate));
            p->pirate_name = malloc(65*sizeof(char));
            strcat(name, "\n");
            strcpy(p->pirate_name, name); 
            list_insert(lst, p, list_length(lst));
         }
         pirate *p;
         p = malloc(sizeof(pirate));
         p->pirate_name = malloc(65*sizeof(char));
         strcpy(p->pirate_name, name);
         list_insert(lst, p, list_length(lst));
 }
    list_sort(lst);

// prints pirate names in the list in sorted order. 
 for (int i = 0; i < list_length(lst); i++){
     pirate *x; 
     x = list_access(lst, i); 
     char* print_name; 
     print_name = x->pirate_name; 
     printf("%s", print_name); 
  }

// removes pirates from the list and then frees memory. 
    while (list_length(lst)>0){
        pirate* output = list_remove(lst, list_access(lst,0));
        free(output->pirate_name); 
        free(output); 
    }

    list_destroy(lst);
    fclose(infile);
    return 0;
}
