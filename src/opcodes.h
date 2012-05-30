#ifndef OPCODES_H
#define OPCODES_H

/* One byte instructions */
#define OP_HALT    0x00
#define OP_ADD     0x01
#define OP_SUB     0x02
#define OP_INC0    0x03
#define OP_INC1    0x04
#define OP_DEC0    0x05
#define OP_DEC1    0x06
#define OP_BELL    0x07

/* Two byte instructions */

#define OP_PRNT    0x08
#define OP_LOAD0   0x09
#define OP_LOAD1   0x0A
#define OP_STORE0  0x0B
#define OP_STORE1  0x0C
#define OP_JMP     0x0D
#define OP_JMPIF   0x0E
#define OP_JMPIFN  0x0F

#endif