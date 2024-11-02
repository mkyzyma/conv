#include "conv.h"
#include "utils.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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



int convert_file(const char *path, const char *dst_ext, converter_t converter) {  
  printf("Converting file [%s] to [%s]...\n", path, dst_ext + 1);

  struct conv_files_t files = open_files(path, dst_ext);

  if(!files.ok) {
    printf("Cant open files\n");
    return -1;
  }

  if(converter(files.src, files.dst)) {
    printf("Bad file format\n");
    return -1;
  }

  close_files(&files);
  
  printf("Done\n");

  return 0;
}

