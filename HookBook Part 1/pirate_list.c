// pirate_list.c
// Meghana Chamarty
// mc3547
// CS223 HW#3
// 3/14/2023
// This file defines the functions declared 
// in pirate_list.h and utlized in hookbook.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pirate.h"
#include "pirate_list.h"

struct implementation {
    pirate** array;
    size_t length; 
    size_t capacity;
}; 

size_t INITIAL_CAPACITY = 25; 
int RESIZE_FACTOR = 2; 

// Allocates memory for a new pirate_list and return a pointer to it.
pirate_list *list_create() {
    pirate_list *new_pirate_list;
    new_pirate_list = malloc(sizeof(pirate_list));
    new_pirate_list->array = malloc(INITIAL_CAPACITY * sizeof(pirate));
    new_pirate_list->length = 0;
    new_pirate_list->capacity = INITIAL_CAPACITY; 
    return new_pirate_list;
}

// Returns a pointer to the pirate pointed to by index in the list, 
// or NULL if is not a valid index. 
pirate *list_access(pirate_list *pirates, size_t idx){
    if (idx < pirates->length) {
        return pirates->array[idx]; 
    }
    else {
        return NULL; 
    }
}

// Returns the index of the pirate with the same name as p. 
// if there is no pirate in the list with a matching name, 
// a value equal to the length of the list is returned 

size_t list_index_of(pirate_list *pirates, pirate *p) {
    for (size_t i = 0; i < pirates->length; i++) {
        if (strcmp(pirates->array[i]->pirate_name, p->pirate_name) == 0) {
            return i; 
        }
    }
    return pirates->length; 
}

// reallocates memory if the length of the pirate list
// is equal to or exceeds the capacity
void list_expand_if_necessary(pirate_list* pirates) {
    if (pirates->length >= pirates->capacity) {
        pirates->array = 
        realloc(pirates->array, pirates->capacity * RESIZE_FACTOR * sizeof(pirate));
        pirates->capacity *= RESIZE_FACTOR;
        fprintf(stderr, "Expand to %zu\n", pirates->capacity);
    }
}

// If there is no pirate in the list with the same name, 
// a pirate is inserted into the list at index
// If there is a pirate in the list with the same name
// a pointer to the pirate that was not inserted is returned
// If the pirate was inserted into the list,  NULL is returned
pirate *list_insert(pirate_list *pirates, pirate *p, size_t idx) {
    if (list_index_of(pirates, p) == pirates->length) {
        list_expand_if_necessary(pirates);
        for (int i = pirates->length - 1; i >= (int)idx; i--) {
            pirates->array[i + 1] = pirates->array[i];
        }
        pirates->array[idx] = p;
        pirates->length++;
        return NULL;
    } else {
        return p;
    }
}

// reallocates memory if the length of the pirate list is 
// less than half the capacity or equal to the INITIAL_CAPACITY
void list_contract_if_necessary(pirate_list* pirates) {
    if (pirates->capacity > 2 * pirates->length * sizeof(pirate)
     && (pirates->capacity != INITIAL_CAPACITY)) {
        pirates->array = 
        realloc(pirates->array, pirates->capacity / RESIZE_FACTOR * sizeof(pirate));
        pirates->capacity /= RESIZE_FACTOR;
        fprintf(stderr, "Contract to %zu\n", pirates->capacity);
    }
}

// Removes the pirate from the list with the same name and return a pointer to it.
// If there is no pirate in the list with the same name, NULL is returned. 
pirate *list_remove(pirate_list *pirates, pirate *p){
    size_t idx = list_index_of(pirates, p);
    if (idx < pirates->length){
        for (size_t i = idx; i < pirates->length - 1; i++){
            pirates->array[i] = pirates->array[i + 1]; 
        }
        pirates->length--;
        list_contract_if_necessary(pirates); 
        return p; 
    }
    return NULL; 
}

// Sort the list of pirates in alphabetical order by name. 
void list_sort(pirate_list *pirates) {
    pirate* current_pirate;
    pirate* prev_pirate; 
    char *current_pirate_name; 
    char *prev_pirate_name;

    for (int i = 1; i < pirates->length; i++) {
        int j = i - 1;

        current_pirate = list_access(pirates, i);
        prev_pirate = list_access(pirates, j);

        current_pirate_name = malloc(strlen(current_pirate->pirate_name) + 1);
        strcpy(current_pirate_name, current_pirate->pirate_name);

        prev_pirate_name = malloc(strlen(prev_pirate->pirate_name) + 1);
        strcpy(prev_pirate_name, prev_pirate->pirate_name);

        while ((j >= 0) && 
        (prev_pirate_name != NULL) && 
        (strcmp(prev_pirate_name, current_pirate_name) > 0)) {
            pirates->array[j + 1] = pirates->array[j];
            j--;
            if (j >= 0) {
                prev_pirate = list_access(pirates, j);
                prev_pirate_name = prev_pirate->pirate_name;
            }
        }
        pirates->array[j + 1] = current_pirate;
    }
}

// Returns the number of pirates in the list.
size_t list_length(pirate_list *pirates){
    return pirates->length; 
}

// Frees all memory associated with the pirate_list
void list_destroy(pirate_list *pirates){
    free(pirates->array); 
    free(pirates); 
}
