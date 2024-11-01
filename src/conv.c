#include "conv.h"
#include "utils.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static const int ZERO = 0x30;
static const int A = 0x41;

char int2hex(int c) { return c + (c < 10 ? ZERO : A); }

int hex2int(char a, char b){

    a = (a <= '9') ? a - ZERO : (a & 0x7) + 9;
    b = (b <= '9') ? b - ZERO : (b & 0x7) + 9;

    return (a << 4) + b;
}

struct conv_files_t {
  bool ok;
  FILE* src;
  FILE* dst;
};

FILE* open_dest_file(const char *src_path, const char *dst_ext) {
  char *dst_path = concat(src_path, dst_ext);

  printf("Destination file name is [%s]\n", dst_path);

  FILE *dst_file = fopen(dst_path, "wb");

  free(dst_path);

  return dst_file;
}

struct conv_files_t open_files(const char *src_path, const char *dst_ext) {
  struct conv_files_t files = {false};

  files.src = fopen(src_path, "rb");

  if (files.src == NULL) {
    printf("Cant open source file [%s]\n", src_path);
    return files;
  }

  files.dst = open_dest_file(src_path, dst_ext);

  if (!files.dst)  {
    printf("Cant open dest file [%s]\n", src_path);
    fclose(files.src);
    return files;
  }

  files.ok = true;

  return files;
}

void close_files(struct conv_files_t *files) {
  if (files->src) {
    fclose(files->src);
  }
  if (files->dst) {
    fclose(files->dst);
  }
} 

int to_hex_converter(FILE* src, FILE* dst) {
  int x;
  while ((x = fgetc(src)) != EOF) {
    int p = x / 16;
    putc(int2hex(p), dst);
    putc(int2hex(x - p * 16), dst);
  }

  return 0;
}

int to_bin_converter(FILE* src, FILE* dst) {
  int8_t buf[2] = {0}; 

  while (fread(buf, 2, 1, src) == 1) {
    int x = hex2int(buf[0], buf[1]); 
    fputc(x, dst);
  }

  return 0;
}

int convert_file(const char *path, const char *dst_ext, converter_t converter) {  
  printf("Converting file [%s] to hex...\n", path);

  struct conv_files_t files = open_files(path, dst_ext);

  if(!files.ok) {
    printf("Cant open files\n");
    return -1;
  }

  converter(files.src, files.dst);

  close_files(&files);
  
  printf("Done\n");

  return 0;
}

int convert_file_to_hex(const char *src_path) {
  return convert_file(src_path, ".hex", to_hex_converter);
}

int convert_file_to_bin(const char *src_path) {
  return convert_file(src_path, ".bin", to_bin_converter);
}