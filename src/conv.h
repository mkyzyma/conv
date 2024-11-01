#pragma once

#include <stdio.h>
typedef int (*converter_t)(FILE* src, FILE* dst);

int convert_file(const char *path, const char *dst_ext, converter_t converter);

int convert_file_to_bin(const char *path);
int convert_file_to_hex(const char *path);
