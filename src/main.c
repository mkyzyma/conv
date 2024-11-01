#include "cli.h"
#include "conv.h"
#include <stdio.h>

int test(const char *path) { printf("Apply: %s\n", path); }

int main(int argc, char *argv[]) {
  struct cmd_handler_t handlers[2] = {
      {"-a", "Convert binary file to text file (source_file_name.txt)",
       convert_file_to_hex},
      {"-b", "Convert text file to binary file (source_file_name.bin)",
       convert_file_to_bin}};
  cli(argc, argv, handlers, 2);
}
