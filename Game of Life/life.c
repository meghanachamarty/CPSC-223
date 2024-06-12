#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "life.h"

bool isAlive(int array[], size_t index, size_t size) {
    if (array[index] == 1) {
        return true;
    } else {
        return false;
    }
    
}

bool shouldDie(int array[], size_t index, size_t size) {
    if (index == 0) {
        return false;
    }
    
    if (index == (size - 1)) {
        return false; 
    }

    if ((isAlive(array, index-1, size) == 1) && (isAlive(array, index+1, size) == 1)) {
        return true;
    }

        return false;
}

// bool isNumeric(char* str) {
//    for (int i = 0; i < str.length(); i++)
//       if (isdigit(str[i]) == false) {
//             return false; 
//       }
//    return true;
// }

