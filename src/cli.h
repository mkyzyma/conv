#ifndef CLI
#define CLI

static const char *HELP_PARAM = "-h";

struct cmd_handler_t {
  char *name;
  char *descr;
  int (*apply)(char *path);
};

int cli(int argc, char *argv[], struct cmd_handler_t *handlers,
        int handlers_size);

#endif /* CLI */
