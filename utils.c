#include <string.h>

#include "utils.h"
const char* get_ext(const char *filename) {
  const char *dot = strchr(filename, '.'); 

  if (!dot || dot == filename) {
    return "";
  }

  return dot + 1;
}
