#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ras/headers/ras.h"
#include "../librvm/headers/vm.h"

const char* helpBasic = "Usage: rvm <command> [arguments]\n\n"
                        "Commands:\n"
                        "  run   <file> [arguments]                 Run a rvm binary or rvm assembly.\n"
                        "  assemble <file> [argument]               Translates an assembly (.ras) to binary (.rvm)."
                        "  build <file> <file> ... [arguments]      Combines multiple binaries together.\n"
                        "  check <file>                             Check a assembly or binary for errors.\n"
                        "  help  <command>                          Display help for a command\n";

const char* helpRun = "Usage: rvm run <file> [arguments]\n\n"
                      "Arguments:\n"
                      "  --output <file>        Write all stdout to the given file (still outputs to stdout)."
                      "  --silent               Any writes to stdout are not shown.";

const char* helpBuild = "Usage: rvm build <file1> <file2> ... [output]\n\n";
const char* helpCheck = "Usage: rvm check <file>\n\n";
const char* helpHelp = "Usage: rvm help <command>\nReplace <command> with run, build, check, or help.\n";

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Not enough arguments\n\n");
        printf("%s", helpBasic);
        return 1;
    }
    if (strcmp(argv[1], "run") == 0) {
        if (argc < 3) {
            printf("Not enough arguments.\n\n");
            printf("%s", helpRun);
            return 1;
        }
        printf("Reading file \"%s\".\n", argv[2]);

    } else if (strcmp(argv[1], "build") == 0) {
        if (argc < 4) {
            printf("Building requires at least 2 arguments (rvm files).\n\n");
            printf("%s", helpBuild);
            return 1;
        }
        printf("Building \"%s\".\n", argv[2]);
    } else if (strcmp(argv[1], "check") == 0) {
        if (argc < 3) {
            printf("Checking requires at least 1 argument.\n\n");
            printf("%s", helpCheck);
            return 1;
        }
        printf("Checking \"%s\" for errors.\n", argv[2]);
    } else if (strcmp(argv[1], "help") == 0 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        if (argc < 3) {
            printf("%s", helpBasic);
            return 1;
        }
        if (strcmp(argv[2], "run") == 0) {
            printf("%s%s", helpRun, arguments);
        } else if (strcmp(argv[2], "build") == 0) {
            printf("%s%s", helpBuild, arguments);
        } else if (strcmp(argv[2], "check") == 0) {
            printf("%s%s", helpCheck, arguments);
        } else if (strcmp(argv[2], "help") == 0) {
            printf("%s%s", helpHelp, arguments);
        } else {
            printf("Invalid command \"%s\".\n", argv[2]);
            printf("Usage: rvm help <command>\nReplace <command> with run, build, check, or help.\n");
            return 1;
        }
    } else {
        printf("Invalid command \"%s\".\n\n", argv[1]);
        printf("%s", helpBasic);
        return 1;
    }

    return 0;
}
