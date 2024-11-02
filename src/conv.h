#pragma once

#include <stdio.h>

typedef int (*converter_t)(FILE* src, FILE* dst);

int convert_file(const char *path, const char *dst_ext, converter_t converter);

