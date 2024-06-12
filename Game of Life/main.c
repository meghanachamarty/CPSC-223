#include "life.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char* argv[]) {

//defines args 
    if (argc < 4) {
        return 1;
    }


    int time_steps = atoi(argv[1]); 
    int game_size = atoi(argv[2]); 
    char* start = argv[3]; 


    if (time_steps < 0) {
        return 1; 
    }

    if (game_size <= 0) {
        return 1; 
    }

    int int_array[game_size]; 

    for (int i=0; i < game_size; i++) {
        if (start[i] == '0') {
            int_array[i]= 0; 
            } 
        else if (start[i]== '1') {
            int_array[i]= 1; 
            }
        else {
            return 1; 
        }
    }

// Prints initial value and initial char array
    printf("%-33s", "Initial values"); 
    printf("[");

    for (int i=0; i < game_size - 1; i++) {
        printf("%c, ", start[i]); 
    }

    printf("%c]\n", start[game_size-1]); 

// checks is alive, if alive checks should die and changes output accordingly. outputs next array. 
char buffer[34];
int int_array_new[game_size];

    for (int n=1; n<time_steps+1; n++) {
        
        sprintf(buffer, "Values after timestep %d", n);
        printf("%-33s", buffer); 
        printf("[");


        /* for (size_t i=0; i < game_size; i++) {
            if (isAlive(int_array, i, game_size)) {
                if (shouldDie(int_array, i, game_size)) {
                    int_array_new[i]=0; 
                }
                else {
                    if (i == 0){
                        int_array_new[i]=1; 
                        int_array_new[i+1]=1;
                    }
                    else if (i == game_size-1) {
                        if (shouldDie(int_array, i-1, game_size)) {
                            if (isAlive(int_array, i-1, game_size)) {
                                int_array_new[i-1]=0;
                                int_array_new[i]= 1; 
                            }
                            else {
                                int_array_new[i-1]=1;
                                int_array_new[i]= 1; 
                            } 
                        }                           
                        else {
                            int_array_new[i-1]= 1;
                            int_array_new[i]= 1;  
                        }
                    }
                    else if (isAlive(int_array, i-1, game_size)) {
                        int_array_new[i] = 1;
                        int_array_new[i+1]= 1;
                    }                    
                    else {
                        int_array_new[i-1]= 1;
                        int_array_new[i] = 1;
                        int_array_new[i+1]= 1;
                    }
                }
            }
            else {
                if (i==0) {
                    if (i+1 ==0) {

                    }
                }
                if (isAlive(int_array, i-1, game_size)) {
                    int_array_new[i]= 1;
                }
                else {
                    int_array_new[i]= 0;
                } 
            }
        } */
        for (size_t i = 0; i < game_size; i++)
            {
                int_array_new[i] = int_array[i];
            }
        for (size_t i=0; i < game_size; i++) {
            if (isAlive(int_array, i, game_size)) {
                if (i == 0) {
                    if(!isAlive(int_array, i+1, game_size)) {
                        int_array_new[i+1]= 1;
                    }
                }
                else if (i == game_size-1) {
                    if(!isAlive(int_array, i-1, game_size)) {
                        int_array_new[i-1]= 1;
                    }
                }
                else if (shouldDie(int_array, i, game_size)) {
                    int_array_new[i] = 0; 
                }
                else {
                    if(!isAlive(int_array, i-1, game_size)) {
                        int_array_new[i-1] =1; 
                    }
                    if(!isAlive(int_array, i+1, game_size)) {
                        int_array_new[i+1]=1; 
                    }
                }
            }
            // else {
            //     int_array_new[i]= 0; 
            // }
        }
        for (int i=0; i< game_size; i++) {
            int_array[i] = int_array_new[i];

            if (i==game_size-1) {
                printf("%d", int_array_new[i]); 
            }
            else {
                printf("%d, ", int_array_new[i]);
            } 
        }

        printf("]");
        printf("\n"); 
    }
}
