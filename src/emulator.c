#include "emulator.h"

emulator *emulator_new(void)
{
    /* Allocate space for the emulator */
    emulator *e = (emulator *) malloc(sizeof(emulator));
    
    /* Allocate space for anything inside the emulator struct */
    e->memory = (word *) calloc(sizeof(word), MEMORY_WORD_COUNT);
    e->r0 = (word *) malloc(sizeof(word));
    e->r1 = (word *) malloc(sizeof(word));
    
    /* Set the values for anything inside the emulator struct */
    e->pc = 0;
    
    return e;
}

void emulator_close(emulator *e)
{
    /* Free everything inside the emulator struct */
    free(e->memory);
    free(e->r0);
    free(e->r1);
    
    /* Free the emulator struct */
    free(e);
}

void emulator_load(emulator *e, word w, int index)
{
    /*
     * Two hex characters are represented as a byte
     * Because C has no nibble type, we must split a byte into two nibbles
     * A byte looks like this: FF
     * A byte represented in binary looks like this: 0000 0000
     * To get the value of the first nibble, we shift left by 4
     * To get the value of the second nibble, we mask by 15
     */
    
    /* Load in the two nibbles */
    e->memory[index] = w >> 4;
    e->memory[index + 1] = w & 15;
}

void emulator_load_file(emulator *e, char *filename)
{
    int i = 0;
    char c = 0;
    
    /* Open the file */
    FILE *file = fopen(filename, "r");
    
    /* Check if the file exists */
    if (file == NULL)
    {
        fprintf(stderr, "File not found\n");
        exit(EXIT_FAILURE);
    }
    
    /* Load in the contents of the file */
    while (!feof(file) && (c = fgetc(file)) != -1)
    {
        /* Load in two nibbles */
        emulator_load(e, c, i);
        
        i += 2; /* += 2 because we load in two nibbles instead of one byte */
    }
    
    /* Close the file */
    fclose(file);
}

/* This macro gets the next word in memory and increments pc */
#define NEXT_WORD e->memory[(e->pc++) + 1]

void emulator_run(emulator *e)
{
    /* Set the initial value of pc */
    e->pc = 0;
    
    /* Run through the contents of memory */
    while ((e->pc) < MEMORY_WORD_COUNT)
    {
        /* Get the current instruction */
        word instruction = e->memory[e->pc];
        
        /* Execute the instruction */
        switch (instruction)
        {
            /* 1-byte Instructions */
            
            case OP_HALT:
            {
                /* Halt */
                printf("Program terminated\n");
                e->pc = MEMORY_WORD_COUNT; /* Set pc to the max memory */
                
                break;
            }
            
            case OP_ADD:
            {
                /* Add (R0 = R0 + R1) */
                *e->r0 = *e->r0 + *e->r1;
                
                break;
            }
                
            case OP_SUB:
            {
                /* Subtract (R0 = R0 - R1) */
                *e->r0 = *e->r0 - *e->r1;
                
                break;
            }
                
            case OP_INC0:
            {
                /* Increment R0 (R0 = R0 + 1) */
                *e->r0 = *e->r0 + 1;
                
                break;
            }
                
            case OP_INC1:
            {
                /* Increment R1 (R1 = R1 + 1) */
                *e->r1 = *e->r1 + 1;
                
                break;
            }
                
            case OP_DEC0:
            {
                /* Decrement R0 (R0 = R0 – 1) */
                *e->r0 = *e->r0 - 1;
                
                break;
            }
                
            case OP_DEC1:
            {
                /* Decrement R1 (R1 = R1 – 1) */
                *e->r1 = *e->r1 - 1;
                
                break;
            }
                
            case OP_BELL:
            {
                printf("Ring bell\n");
                
                break;
            }
            
            /* 2-byte Instructions, value of the second byte is called <data> */
            
            case OP_PRNT:
            {
                /* Print <data> (The numerical value of <data> is printed) */
                printf("%d\n", NEXT_WORD);
                
                break;
            }
            
            case OP_LOAD0:
            {
                /* Load value at address <data> into R0 */
                *e->r0 = e->memory[NEXT_WORD];
                
                break;
            }
            
            case OP_LOAD1:
            {
                /* Load value at address <data> into R1 */
                *e->r1 = e->memory[NEXT_WORD];
                
                break;
            }
            
            case OP_STORE0:
            {
                /* Store R0 into address <data> */
                e->memory[NEXT_WORD] = *e->r0;
                
                break;
            }
            
            case OP_STORE1:
            {
                /* Store R1 into address <data> */
                e->memory[NEXT_WORD] = *e->r1;
                
                break;
            }
                
            case OP_JMP:
            {
                /* Jump to address <data> */
                e->pc = e->memory[e->pc + 1]; /* -1 to counteract increment */
                
                break;
            }
                
            case OP_JMPIF:
            {
                /* Jump to address <data> if R0 == 0 */
                if (*e->r0 == 0)
                    e->pc = e->memory[e->pc + 1]; /* NEXT_WORD without ++ */
                
                break;
            }
                
            case OP_JMPIFN:
            {
                /* Jump to address <data> if R0 != 0*/
                if (*e->r0 != 0)
                {
                    e->pc = e->memory[e->pc + 1]; /* NEXT_WORD without ++ */
                }
                
                break;
            }
            
            default:
            {
                fprintf(stderr, "Unknown instruction '%#x'\n", instruction);
                exit(EXIT_FAILURE);
                
                break;
            }
        }
        
        e->pc++;
    }
}

void emulator_print_memory(emulator *e)
{
    int i;
    
    /* Print out the contents of memory */
    
    printf("\nMemory:\n");
    
    for (i = 0; i < MEMORY_WORD_COUNT; i++)
    {
        word *current = &e->memory[i]; /* Get the word from memory */
        printf("%d ", *current); /* Print it out in hex format */
    }
    
    printf("\n");
}

void emulator_print_registers(emulator *e)
{
    /* Print out the registers */
    
    printf("Registers:\n");
    printf("R0: %d\n", *e->r0);
    printf("R1: %d\n", *e->r1);
}