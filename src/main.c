#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "emulator.h"

void usage(char *programName);

int main(int argsNum, char *args[])
{
    int i;
    int debugMode = 0;
    char *filename = NULL;
    emulator *e;
    
    /* Handle arguments */
    for (i = 0; i < argsNum; i++)
    {
        char *arg = args[i];
        
        if (strcmp(arg, "-d") == 0)
            debugMode = 1;
        else
            filename = arg;
    }
    
    /* Check if we have the right arguments */
    if (argsNum < 2 || filename == NULL)
        usage(args[0]);
    
    /* Create an emulator, load in the file, and run the contents of memory */
    e = emulator_new();
    emulator_load_file(e, filename);
    emulator_run(e);
    
    /* Print out register and memory info if debug mode is enabled */
    if (debugMode)
    {
        emulator_print_memory(e);
        emulator_print_registers(e);
    }
    
    /* Close the emulator */
    emulator_close(e);
    
    return EXIT_SUCCESS;
}

void usage(char *programName)
{
    printf("usage: %s <options> <input file>\n", programName);
    printf("Options:\n");
    printf("-d\tDebug mode\n");
    printf("\nMade by AndyRoth\n");
    
    exit(EXIT_SUCCESS);
}