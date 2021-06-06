#include "mergesort.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

int char_comparator(const void* first, const void* second) {
    return *(char*)first - *(char*)second;
}

int int_comparator(const void* first, const void* second) {
    return *(int*)first - *(int*)second;
}

int str_comparator(const void* first, const void* second) {
    return strcmp(*(char**)first, *(char**)second);
}

int main(int argc, char** argv) {
    if (argc < 2)
        return 0;
    char* type = *(argv + 1);

    if(strcmp(type, "char") == 0) {
        char* array = (char*)malloc((argc - 2) * sizeof(char));
        assert(array);
        for (int i = 0; i < argc - 2; i++)
            array[i] = argv[i + 2][0];
        
        int correct = mergesort(array, argc - 2, sizeof(char), char_comparator);
        if (correct == -1) {
            printf("%s\n", "Error: memory allocation failed.");
            free(array);
            return 1;
        }
        
        for (int i = 0; i < argc - 2; i++) {
            if (i < argc - 3)
                printf("%c ", array[i]);
            else
                printf("%c\n", array[i]);
        }
        free(array);
    }
    
    if(strcmp(type, "int") == 0) {
        int* array = (int*)malloc((argc - 2) * sizeof(int));
        assert(array);
        for (int i = 0; i < argc - 2; i++)
            array[i] = atoi(argv[i + 2]); 
        
        int correct = mergesort(array, argc - 2, sizeof(int), int_comparator);
        if (correct == -1) {
            printf("%s\n", "Error: memory allocation failed.");
            free(array);
            return 1;
        }
        
        for (int i = 0; i < argc - 2; i++) {
            if (i < argc - 3)
                printf("%d ", array[i]);
            else
                printf("%d\n", array[i]);
        }
        free(array);
    }

    if (strcmp(type, "str") == 0) {
        char** array = (char**)malloc((argc - 2) * sizeof(char*));
        assert(array);
        for (int i = 0; i < argc - 2; i++)
            array[i] = argv[i + 2];

        int correct = mergesort(array, argc - 2, sizeof(char*), str_comparator);
        if (correct == -1) {
            printf("%s\n", "Error: memory allocation failed.");
            free(array);
            return 1;
        }

        for (int i = 0; i < argc - 2; i++) {
            if (i < argc - 3)
                printf("%s ", array[i]);
            else
                printf("%s\n", array[i]);
        }
        free(array);
    } 
}