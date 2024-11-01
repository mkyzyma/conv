#include <string.h>

#include "utils.h"
const char *get_ext(const char *filename) {
  const char *dot = strchr(filename, '.');

  if (!dot || dot == filename) {
    return "";
  }

  return dot + 1;
}

void change_ext(char *filename, const char *new_ext) {
  char *dot = strchr(filename, '.');

  if (!dot || dot == filename) {
    return;
  }

  memcpy(dot + 1, new_ext, 4);
}
