#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 256
#define NUM_REGISTERS 4

typedef struct{
    int registers[NUM_REGISTERS];
    unsigned char memory[MEMORY_SIZE];
    int pc;
}CPU;

void initialize_cpu(CPU *cpu){
    for(int i = 0; i < NUM_REGISTERS; i++) cpu->registers[i] = 0;
    for(int i = 0; i < MEMORY_SIZE; i++) cpu->memory[i] = 0;
    cpu->pc = 0;
}

void execute_instruction(CPU *cpu){
    unsigned char opcode = cpu->memory[cpu->pc];
    switch (opcode)
    {
    case 0x01: // MOV R0, #value
        cpu->registers[0] = cpu->memory[cpu->pc + 1];
        cpu->pc += 2; // Move to next instruction, move past opcode (1) and value (2)
        break;
    case 0x02: // MOV R1, #value
        cpu->registers[1] = cpu->memory[cpu->pc + 1];
        cpu->pc += 2;
        break;
    case 0x03: // MOV R2, #value
        cpu->registers[2] = cpu->memory[cpu->pc + 1];
        cpu->pc += 2;
        break;
    case 0x04: // MOV R3, #value
        cpu->registers[3] = cpu->memory[cpu->pc + 1];
        cpu->pc += 2;
        break;
    case 0x05: // ADD R0, R1
        cpu->registers[0] += cpu->registers[1];
        cpu->pc += 1;
        break;
    case 0x06: // SUB R0, R1
        cpu->registers[0] -= cpu->registers[1];
        cpu->pc += 1;
        break;
    case 0xFE: // PRINT R0
        printf("R0 -> %d\n", cpu->registers[0]);
        cpu->pc += 1;
        break;
    case 0xFF: // HLT
        printf("CPU Hulted\n");
        exit(0);
    default:
        printf("Unknown opcode: %x\n", opcode);
        exit(1);
    }
}

void load_program(CPU *cpu){
    unsigned char program[] = {
        0x01, 0x05, // MOV R0, #5
        0x02, 0x05, // MOV R1, #5
        0x05, // ADD R0, R1
        0xFE, // PRINT R0
        0xFF // HLT
    };
    for (int i = 0; i < sizeof(program); i++){
        cpu->memory[i] = program[i];
    }
}

int main(){
    CPU cpu;
    initialize_cpu(&cpu);
    load_program(&cpu);

    while(1){
        execute_instruction(&cpu);
    }

    return 0;
}