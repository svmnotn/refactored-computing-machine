#define NOB_IMPLEMENTATION
#include "./src/nob.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    NOB_GO_REBUILD_URSELF(argc, argv);

    if (!nob_mkdir_if_not_exists("build")) return 1;

    Nob_Cmd cmd = {0};
    nob_cmd_append(&cmd, "clang");
    nob_cmd_append(&cmd, "-xc", "-std=c2x");
    nob_cmd_append(&cmd, "-Wall", "-Wextra", "-ggdb", "-pedantic");
    nob_cmd_append(&cmd, "-I./src/nob.h");
    nob_cmd_append(&cmd, "./src/lang.c");
#ifdef _WIN32
    nob_cmd_append(&cmd, "-o", "./build/lang.exe");
#else
    nob_cmd_append(&cmd, "-o", "./build/lang");
#endif
    if (!nob_cmd_run_sync(cmd)) return 1;

    return 0;
}
