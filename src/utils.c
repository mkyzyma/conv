#include <string.h>

#include "utils.h"
#include <stdlib.h>
#include <string.h>
char *concat(const char* a, const char* b) {
    const size_t a_len = strlen(a);
    const size_t b_len = strlen(b);

    char* result = malloc(a_len + b_len);

    memcpy(result, a, a_len);
    memcpy(result + a_len, b, b_len + 1);

    return result;
}