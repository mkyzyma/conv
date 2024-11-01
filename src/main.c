#include "cli.h"
#include <stdio.h>

int test(char *path) { printf("Apply: %s\n", path); }

int main(int argc, char *argv[]) {
  struct cmd_handler_t handlers[2] = {
      {"-a", "Convert binary file to text file (source_file_name.txt)", test},
      {"-b", "Convert text file to binary file (source_file_name.bin)", test}};
  cli(argc, argv, handlers, 2);
}
