#include "../include/names.h"

int doComputation() {
    int c = max(3, 4);
    logDebug('d');
    return c;
}

void logDebug(char c) { // 1 duplicate symbol for architecture x86_64
    printf("gg_vp%c", c);
}
