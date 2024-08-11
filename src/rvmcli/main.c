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
        InstructionBuffer *buffer = buffer_init(10);
        buffer_add(buffer, NOOP, 0, NULL);
        buffer_add(buffer, NOOP, 0, NULL);
        buffer_add(buffer, HALT, 0, NULL);

        VM *rvm = vm_init(256, 512);
        vm_mount(rvm, buffer);
        vm_run(rvm);

        Instruction i = parse_instruction("\0\0\0", 3);
        printf("Opcode: %d", i.opcode);

        vm_free(rvm);
        buffer_free(buffer);
    }
    return 0;
}
