#include <stdio.h>
#include "debug.h"

#include "value.h"
#include "vm.h"

char* additionalMessage = NULL;

static int simpleInstruction(const char* name, int offset, char* message) {
  printf("\t%s\t\t%s", name, message);
  return offset + 1;
}

static int constantInstruction(const char* name, Chunk* chunk, int offset) {
  uint8_t constantIndex = chunk->code[offset + 1];
  printf("\t%-16s %4d '", name, constantIndex);
  printValue(chunk->constants.values[constantIndex]);
  printf("'");
  if (additionalMessage != NULL) {
    printf(" %s", additionalMessage);
    additionalMessage = NULL;
  }
  return offset + 2;
}

void disassembleChunk(Chunk* chunk, const char* name) {
  printf("== %s ==\n", name);
  
  for (int offset = 0; offset < chunk->count;) {
    offset = disassembleInstruction(chunk, offset);
  }
}

int disassembleInstruction(Chunk* chunk, int offset) {
  printf("%04d\t ", offset);
  if (offset > 0 && chunk->lines[offset] == chunk->lines[offset-1]) {
    printf("   | ");
  } else {
    printf("%4d ", chunk->lines[offset]);
  }
  printf("\t");
  uint8_t instruction = chunk->code[offset];
  
  int result = -1;
  
  switch (instruction)
  {
  case OP_CONSTANT:
    return constantInstruction("OP_CONSTANT", chunk, offset);
  case OP_RETURN:
    return simpleInstruction("OP_RETURN", offset, "");
  case OP_NEGATE:
    return simpleInstruction("OP_NEGATE", offset, "");
  case OP_ADD:
    return simpleInstruction("OP_ADD", offset, "\t");
  case OP_SUBTRACT:
    return simpleInstruction("OP_SUBTRACT", offset, "");
  case OP_MULTIPLY:
    return simpleInstruction("OP_MULTIPLY", offset, "");
  case OP_DIVIDE:
    return simpleInstruction("OP_DIVIDE", offset, "");
  default:
    printf("Unkown opcode %d\n", instruction);
    return offset+1;
  }
}