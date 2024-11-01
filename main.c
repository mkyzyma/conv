#include <stdio.h>
#include <string.h>

#include "utils.h"

static const char *HELP_PARAM = "-h";

struct cmd_handler_t {
  char* name;
  char* descr;
  int (*apply)(char* path);
};

int test(char *path) {
  printf("Apply: %s\n", path);
}

void usage(const char* progname, struct cmd_handler_t *handlers, int handlers_size) {
  printf("Usage: %s option source_file_name\n", progname);
  printf("Options:\n");

  for (int i = 0; i < handlers_size; ++i) {
    struct cmd_handler_t *handler = &handlers[i];
    printf("  %s: %s\n", handler->name, handler->descr);
  }

}

void cli(int argc, char *argv[], struct cmd_handler_t *handlers, int handlers_size) {
  char *progname = argv[0];

  if (argc < 3 || argv[1] == HELP_PARAM)
  {
    usage(progname, handlers, handlers_size);
    return;
  }

  for(int i = 0; i < handlers_size; ++i) {
    char *cmd = argv[1];
    
    struct cmd_handler_t *handler = &handlers[i];  

    if (!strcmp(cmd, handler->name)) {
      char *path = argv[2];
      handler->apply(path);
      return;
    }
  }

  usage(progname, handlers, handlers_size);
}
int main(int argc, char *argv[]) {
  struct cmd_handler_t handlers[2] = {
    {"-a", "Convert binary file to text file (source_file_name.txt)", test},
    {"-b", "Convert text file to binary file (source_file_name.bin)", test}
  };
  cli(argc, argv, handlers, 2);
}
