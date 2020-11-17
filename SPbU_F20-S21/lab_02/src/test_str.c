#include "test_str.h"
#include "str.h"

void test_my_strcmp() {
    char a[4] = "abc\0";
    char b_1[3] = "ba\0";
    assert(my_strcmp(a, b_1) < 0);
    char b_2[4] = "abc\0";
    assert(my_strcmp(a, b_2) == 0);
    char b_3[3] = "ab\0";
    assert(my_strcmp(a, b_3) > 0);
}

void test_my_strcpy() {
    char a[6];
    char b[6] = "abcde\0";
    my_strcpy(a, b);
    assert(my_strcmp(a, b) == 0);
}

void test_my_strcat() {
    char a[9] = "abc\0";
    char b[6] = "defgh\0";
    my_strcat(a, b);
    char res[9] = "abcdefgh\0";
    assert(my_strcmp(a, res) == 0);
}

void test_my_strlen() {
    assert(my_strlen("abcde") == 5);
    assert(my_strlen("") == 0);
}