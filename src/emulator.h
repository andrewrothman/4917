#ifndef EMULATOR_H
#define EMULATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "opcodes.h"

/* The size of memory. Also the filesize limit in bytes. */
#define MEMORY_WORD_COUNT 16

typedef uint8_t word; /* A word is defined as 8 bits, or two nibbles */

/* The emulator struct */
typedef struct
{
    word *memory; /* RAM */
    word *r0;     /* Register 0 */
    word *r1;     /* Register 1 */
    word pc;      /* Program counter */
} emulator;

emulator *emulator_new(void); /* Create a new emulator */
void emulator_close(emulator *e); /* Close the emulator */

void emulator_load(emulator *e, word w, int index); /* Load in two nibbles */
void emulator_load_file(emulator *e, char *filename); /* Load file contents */

void emulator_run(emulator *e); /* Execute the contents of memory */

void emulator_print_memory(emulator *e); /* Print out register contents */
void emulator_print_registers(emulator *e); /* Print out memory contents */

#endif