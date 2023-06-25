#ifndef dust_vm_h
#define dust_vm_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

typedef struct {
  Chunk* chunk;
  uint8_t* ip;
  Value stack[STACK_MAX];
  Value* stackTop;
} VM;

typedef enum {
  OK,
  COMPILE_ERROR,
  RUNTIME_ERROR,
} InterpretResult;

void initVM();
void freeVM();

void push(Value value);
Value pop();

InterpretResult interpret(const char* source, Chunk* chunk);

#endif