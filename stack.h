#pragma once

struct TreeNode_t;

typedef TreeNode_t* StackElem_t;
const StackElem_t canary = (StackElem_t)0xEBADA;

#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "enum.h"

#ifdef STACK_DEBUG
#define ON_DBG(...)  __VA_ARGS__
#else
#define ON_DBG(...)
#endif

#define POISON_DATA NULL
#define POISON_SIZE -1488

#define STACK_INIT(stk, capacity) StackInit(&(stk), (capacity) ON_DBG(, #stk, __FILE__, __LINE__))
#define STACK_DESTROY(stk) StackDestroy(&(stk))
#define ASSERT_OK(stk) do {\
    errors err = StackError(stk);\
    if (err != ERR_OK) {\
        StackDump(stk, err, __FILE__, __LINE__, __func__);\
        assert(0);}\
    } while(0)







struct stack_t
    {
    ON_DBG(StackElem_t canary_left = canary;)

    StackElem_t* real_data;
    StackElem_t* data;
    int size, capacity;
    ON_DBG(const char* name; const char* file; int line;)

    ON_DBG(StackElem_t canary_right = canary;)
    };

errors StackInit(stack_t* stk, int capacity ON_DBG(, const char* name, const char* file, int line));

errors StackDestroy(stack_t* stk);

errors StackPush(stack_t* stk, StackElem_t value);

StackElem_t StackPop(stack_t* stk, errors* err);

errors StackError(stack_t* stk);

void StackDump(const stack_t* stk,  errors err_code, const char* file, int line, const char* func);

errors StackResize(stack_t* stk, size_t new_capacity);


void PrintTop(const stack_t* stk, errors err_code, const char* file, int line, const char*func);

void PrintBottom(const stack_t* stk);

void PrintTop_file (FILE* log_file, const stack_t* stk, errors err_code, const char* file, int line, const char*func);

void PrintBottom_file(FILE* log_file, const stack_t* stk);

void StackDump_file(const stack_t* stk,  errors err_code, const char* file, int line, const char* func);