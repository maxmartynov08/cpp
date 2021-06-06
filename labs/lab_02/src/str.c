#include "str.h"

char* my_strcpy(char* restrict res, const char* restrict src) {
    char* initial_res = res;
    while (*src != '\0') 
        *res++ = *src++;
    return initial_res;
}

char* my_strcat(char* restrict dest, const char* restrict src) {
    char* initial_dest = dest; 
    while (*dest != '\0')
        dest++;
    while (*src != '\0')
        *dest++ = *src++;
    return initial_dest;
}

int my_strcmp(const char* str1, const char* str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        int elem1 = *str1++, elem2 = *str2++;
        if (elem1 < elem2)
            return -1;
        else if (elem1 > elem2)
            return 1;
    }
    if (*str1 == '\0')
        return *str2 == '\0' ? 0 : -1;
    return 1;
}

size_t my_strlen(const char* str) {
    const char* begin = str;
    while (*str != '\0')
        str++;
    return str - begin;
}