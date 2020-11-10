#include "../include/names.h"

int max(int a, int b) {
    logDebug('m');
    if (a < b)
        return b;
    return a;
}
