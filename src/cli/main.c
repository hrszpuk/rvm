#include <stdio.h>
#include <strings.h>

const char* helpBasic = "Usage: rvm <command> [arguments]\n\n"
                        "Commands:\n"
                        "  run   <file> [arguments]  Run a rvm file\n"
                        "  build <file> [output]     Build a rvm file\n"
                        "  check <file>              Check a rvm file for errors\n"
                        "  help  <command>           Display help for a command\n";

const char* arguments = "Arguments:\n"
                        "  -h, --help                Display this help menu\n"
                        "  -v, --version             Display the version of rvm\n"
                        "  -d, --debug               Run in debug mode\n"
                        "  -l, --log                 Log the output to a file\n"
                        "  -o, --output <file>       Output to a file\n"
                        "  -i, --input <file>        Input from a file\n"
                        "  -s, --stdin               Input from stdin\n"
                        "  -a, --args <args>         Set the arguments\n";

const char* helpRun = "Usage: rvm run <file> [arguments]\n\n";
const char* helpBuild = "Usage: rvm build <file1> <file2> ... [output]\n\n";
const char* helpCheck = "Usage: rvm check <file>\n\n";
const char* helpHelp = "Usage: rvm help <command>\nReplace <command> with run, build, check, or help.\n";

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Not enough arguments\n\n");
        printf(helpBasic);
        return 1;
    }

    if (strcasecmp(argv[1], "run") == 0) {
        if (argc < 3) {
            printf("Not enough arguments.\n\n");
            printf(helpRun);
            return 1;
        }
        printf("Attempting to run \"%s\".\n", argv[2]);
    } else if (strcasecmp(argv[1], "build") == 0) {
        if (argc < 4) {
            printf("Building requires at least 2 arguments (rvm files).\n\n");
            printf(helpBuild);
            return 1;
        }
        printf("Building \"%s\".\n", argv[2]);
    } else if (strcasecmp(argv[1], "check") == 0) {
        if (argc < 3) {
            printf("Checking requires at least 1 argument.\n\n");
            printf(helpCheck);
            return 1;
        }
        printf("Checking \"%s\" for errors.\n", argv[2]);
    } else if (strcasecmp(argv[1], "help") == 0 || strcasecmp(argv[1], "-h") == 0 || strcasecmp(argv[1], "--help") == 0) {
        if (argc < 3) {
            printf(helpBasic);
            return 1;
        }
        if (strcasecmp(argv[2], "run") == 0) {
            printf(helpRun, arguments);
        } else if (strcasecmp(argv[2], "build") == 0) {
            printf(helpBuild, arguments);
        } else if (strcasecmp(argv[2], "check") == 0) {
            printf(helpCheck, arguments);
        } else if (strcasecmp(argv[2], "help") == 0) {
            printf(helpHelp, arguments);
        } else {
            printf("Invalid command \"%s\".\n", argv[2]);
            printf("Usage: rvm help <command>\nReplace <command> with run, build, check, or help.\n");
            return 1;
        }
    } else {
        printf("Invalid command \"%s\".\n\n", argv[1]);
        printf(helpBasic);
        return 1;
    }

    return 0;
}
