/******************************************************************************
Prac 2 - AVR ASM OpCode Decoder
*******************************************************************************/

#include <stdio.h>
#include <inttypes.h>

const uint8_t flash_mem[] ={ 0x80, 0xE0, 0x83, 0x95, 0x8A, 0x30, 0x11, 0xF0, 0x82, 0xB9, 
                            0xFB, 0xCF, 0x8A, 0x95, 0x80, 0x30, 0xC1, 0xF3, 0x82, 0xB9, 0x00, 0x00};
const uint16_t inst16_table[] = {
  {0x0}, //NOP  
};

enum{
    e_NOP,
};


// Op Code struct
typedef union {
    uint16_t op16; // e.g.: watchdog
    struct{
        uint16_t op4:4;
        uint16_t d5:5;
        uint16_t op7:7;
    }type1; // e.g: LSR
    struct{
        uint16_t r4:4;
        uint16_t d5:5;
        uint16_t r1:1;
        uint16_t op6:6;
    }type2; // e.g.: MOV,MUL,ADC,ADD,AND,
    // TO-DO: Add more types as needed
} Op_Code_t;


int main()
{
    Op_Code_t *instruction;
    printf("- Practica 2: AVR OpCode -\n");
    // Decode the instructions by cycling through the array
    for (uint8_t idx = 0; idx < sizeof(flash_mem); idx+=2)
    {
        instruction = (Op_Code_t*) &flash_mem[idx];
        if (instruction->op16 == inst16_table[e_NOP])
        {
            printf("NOP\n");
        }
        else
        {
            printf("unknown\n");
        }
    }
    return 0;
}