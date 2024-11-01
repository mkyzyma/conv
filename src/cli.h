#pragma once

static const char *HELP_PARAM = "-h";

struct cmd_handler_t {
  const char *name;
  const char *descr;
  int (*apply)(const char *path);
};

int cli(int argc, char *argv[], const struct cmd_handler_t *handlers,
        int handlers_size);
