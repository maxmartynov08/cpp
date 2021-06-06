#include "mergesort.h"

void copy_element(char* dest, char* src, size_t element_size) {
    for (int i = 0; i < element_size; i++)
        dest[i] = src[i];
}

int real_mergesort(char* array, size_t element_size, 
                    int (*comparator)(const void*, const void*), 
                    int left, int right) {
    if (right - left <= 1)
        return 0;

    int mid = (left + right) / 2;
    int correct_l = real_mergesort(array, element_size, comparator, left, mid);
    int correct_r = real_mergesort(array, element_size, comparator, mid, right);

    if (correct_l == -1 || correct_r == -1)
        return -1;

    char* sorted_subarray = (char*)malloc((right - left) * element_size);
    if (sorted_subarray == NULL)
        return -1;
    
    int it1 = left, it2 = mid;
    while (it1 < mid || it2 < right) {
        char* dest = sorted_subarray + (it1 - left + it2 - mid) * element_size;
        char* elem1 = array + it1 * element_size;
        char* elem2 = array + it2 * element_size;
        if (it2 == right || 
                (it1 != mid && comparator((void*)elem1, (void*)elem2) <= 0)) {
            copy_element(dest, elem1, element_size);
            it1++;
        }
        else {
            copy_element(dest, elem2, element_size);   
            it2++;
        }
    }

    for (int i = left; i < right; i++)
        copy_element(array + i * element_size, sorted_subarray + (i - left) * element_size, element_size);
    
    free(sorted_subarray);
    return 0;
}

int mergesort(void* array, size_t elements, size_t element_size, int (*comparator)(const void*, const void*)) {
    return real_mergesort((char*)array, element_size, comparator, 0, elements);
}