#include "conv.h"
#include "sys/stat.h"
#include "utils.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static const int ZERO = 48;
static const int A = 87;

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
  size_t len = strlen(src_path) + 1;
  char *dst_path = malloc(len);

  strcpy(dst_path, src_path);

  change_ext(dst_path, dst_ext);

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
    return files;
  }

  files.ok = true;

  return files;
}

void close_files(struct conv_files_t *files) {
  if (files->src != NULL) {
    fclose(files->src);
  }
  if (files->dst != NULL) {
    fclose(files->dst);
  }
} 


int convert_file_to_hex(const char *src_path) {  
  printf("Converting file [%s] to hex...\n", src_path);

  struct conv_files_t files = open_files(src_path, "hex");

  if(!files.ok) {
    printf("Cant open files\n");
    return -1;
  }

  int x;
  while ((x = fgetc(files.src)) != EOF) {
    int p = x / 16;
    putc(int2hex(p), files.dst);
    putc(int2hex(x - p * 16), files.dst);
  }

  close_files(&files);
  
  printf("Done\n");

  return 0;
}

int convert_file_to_bin(const char *src_path) {  
  printf("Converting file [%s] to bin...\n", src_path);

  struct conv_files_t files = open_files(src_path, "bin");

  if(!files.ok) {
    printf("Cant open files\n");
    return -1;
  }

  int8_t buf[2] = {0}; 

  while (fread(buf, 2, 1, files.src) == 1) {
    int x = hex2int(buf[0], buf[1]); 
    fputc(x, files.dst);
  }

  close_files(&files);
  
  printf("Done\n");

  return 0;
}