#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pirate.h"

typedef struct _pirate_list{
    pirate** array;
    int length; 
    int capacity;
} pirate_list; 

static int INITIAL_CAPACITY = 25; 
int RESIZE_FACTOR = 2; 

pirate_list *list_create() {
    pirate_list *new_pirate_list;
    new_pirate_list =  malloc(sizeof(pirate_list));
    new_pirate_list->array = malloc(INITIAL_CAPACITY * sizeof(pirate));
    new_pirate_list->length = 0;
    new_pirate_list->capacity=INITIAL_CAPACITY; 
    return new_pirate_list;
}

size_t list_index_of(pirate_list *pirates, pirate *p) {
    for (size_t i=0; i < pirates->length; i++) {
        if (strcmp(pirates->array[i]->pirate_name, p->pirate_name) == 0){
            return i; 
        }
    }
return pirates->length; 
}

void list_expand_if_necessary(pirate_list* pirates){
    if (pirates->capacity == (pirates->length * sizeof(pirates->array)))
        {
            pirates = realloc(pirates, pirates->capacity * sizeof(pirates) * RESIZE_FACTOR); 
            int new_capacity = pirates->capacity;
            fprintf(stderr, "Expand to %zu\n", new_capacity);
        }
}

pirate *list_insert(pirate_list *pirates, pirate *p, size_t idx)
{
    if (list_index_of(pirates, p) == pirates->length)
    {
        if (pirates->capacity == (pirates->length * sizeof(pirates->array)))
        {
            pirates = realloc(pirates, pirates->capacity * sizeof(pirates) * RESIZE_FACTOR);
        }
        for (int i=pirates->length; i > idx; i--){
            pirates->array[i] = pirates->array[i+1]; 
        }
        pirates->array[idx] = p; 
        pirates->length++; 
    }
    if (list_index_of(pirates, p) < pirates->length){
        return p; 
    }
    else {
        return NULL; 
    }
}

void list_contract_if_necessary(pirate_list* pirates){
    if (pirates->length * 2 < pirates->capacity){
            pirates = realloc(pirates, pirates->capacity * sizeof(pirates) / RESIZE_FACTOR); 

            if (pirates->capacity < INITIAL_CAPACITY){
                pirates = realloc(pirates, INITIAL_CAPACITY); 
            }
            int new_capacity = pirates->capacity; 
            fprintf(stderr, Contract to %zu\n, new_capacity);
        }
}

pirate *list_remove(pirate_list *pirates, pirate *p){
    if (list_index_of(pirates, p) < pirates->length){
        size_t i; 
        for (i=(list_index_of(pirates, p)); i<pirates->length; i++){
            pirates->array[i]= pirates->array[i+1]; 
        }
        pirates->length--;
        list_contract_if_necessary(pirates); 
        return p; 
    }
    return NULL; 
}

pirate *list_access(pirate_list *pirates, size_t idx){
    if (idx > 0 && idx < pirates->length-1) {
        return pirates->array[idx]; 
    }
    else {
        return NULL; 
    }
}

void list_sort(pirate_list *pirates){
    for (int i= 1; i < pirates->length-1; i++) {
    int j = i - 1;

    while ((strcmp(pirates->array[i]->pirate_name, pirates->array[j]->pirate_name) > 0) && j >= 0) {
      pirates->array[j + 1] = pirates->array[j];
      --j;
    }
    pirates->array[j + 1] = pirates->array[i];
  }
}

size_t list_length(pirate_list *pirates){
    return pirates->length; 
}

void list_destroy(pirate_list *pirates){
    free(pirates->array); 
    free(pirates); 
}
