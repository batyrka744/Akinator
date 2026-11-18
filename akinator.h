#pragma once
#include "tree.h"
#include <windows.h>
#include "stack.h"
#include "tree_dump.h"

enum modes {
    GUESS = 1, 
    SHOW = 2, 
    DEF = 3, 
    COMPARE = 4, 
    OUT_ = 5, 
    SAVE = 6
};

#define BUFFER_LENGTH 5000


char* SpaceTo_(const char* str);

void Guess(Tree* tree);

void Speak(const char* str);

void StartGame(Tree* tree, FILE* file);

void AddObject(Tree* tree, TreeNode_t* node);

TreeNode_t* FindNode(TreeNode_t* node, const char* name);

void Description(TreeNode_t* node);

void PushInfo(stack_t* stk, TreeNode_t* node);

void Compare(TreeNode_t* node1, TreeNode_t* node2);