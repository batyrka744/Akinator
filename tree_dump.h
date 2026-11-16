#pragma once
#include "tree.h"



void TreeDumpGraph(const Tree* tree, const char* reason);

void RecOutput(TreeNode_t* node, FILE* file, size_t depth);

void TreeDump(Tree* tree, const TreeNode_t* node,  errors err_code, const char* file, int line, const char* func);

void TreeDump_file(const Tree* tree, const TreeNode_t* node, errors err_code, const char* file, int line, const char* func);