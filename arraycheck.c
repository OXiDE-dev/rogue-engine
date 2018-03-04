#include "arraycheck.h"

int isInArr(int val, int *arr, int size){
    int i;
    for (i=0; i < size; i++) {
        if (arr[i] == val)
            return i;
    }
    return 2147483647;
}
