#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "conv.h"

char int2hex(int c) { return c + (c < 10 ? '0' : 'A'); }

int hex2int(char c){
    return (c <= '9') ? c - '0' : (c & 0x7) + 9;
}

int to_hex_converter(FILE* src, FILE* dst) {
  int x;
  while ((x = fgetc(src)) != EOF) {
    int p = x / 16;
    fputc(int2hex(p), dst);
    fputc(int2hex(x - p * 16), dst);
  }

  return 0;
}

int to_bin_converter(FILE* src, FILE* dst) {
  int c;
  while ((c = fgetc(src)) != EOF) {
    if (!isxdigit(c)) {
      return -1;
    }

    int a = hex2int(c);

    c = fgetc(src);    

    if (c == EOF) {
      fputc(a, dst);
      break;
    }

    if (!isxdigit(c)) {
      return -1;
    }

    int b = hex2int(c);

    fputc((a << 4) + b, dst);
  }    

  return 0;
}

int convert_file_to_hex(const char *src_path) {
  return convert_file(src_path, ".hex", to_hex_converter);
}

int convert_file_to_bin(const char *src_path) {
  return convert_file(src_path, ".bin", to_bin_converter);
}