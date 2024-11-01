#include "cli.h"
#include <stdio.h>
#include <string.h>

void usage(const char *progname, const struct cmd_handler_t *handlers,
           int handlers_size) {
  printf("Usage: %s option source_file_name\n", progname);
  printf("Options:\n");

  for (int i = 0; i < handlers_size; ++i) {
    const struct cmd_handler_t *handler = &handlers[i];
    printf("  %s: %s\n", handler->name, handler->descr);
  }
}

int cli(int argc, char *argv[], const struct cmd_handler_t *handlers,
        int handlers_size) {
  char *progname = argv[0];

  if (argc == 2 && argv[1] == HELP_PARAM) {
    usage(progname, handlers, handlers_size);
    return 0;
  }

  if (argc < 3) {
    goto error;
  }

  for (int i = 0; i < handlers_size; ++i) {
    char *cmd = argv[1];

    const struct cmd_handler_t *handler = &handlers[i];

    if (!strcmp(cmd, handler->name)) {
      char *path = argv[2];
      return handler->apply(path);
    }
  }

error:
  printf("Invalid arguments\n");
  usage(progname, handlers, handlers_size);
  return 1;
}