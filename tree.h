#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#include "my_assert.h"
#include "enum.h"

#define TREE_FILE_WRITE "tree_file_w.txt"
#define TREE_FILE_READ "tree_file_r.txt"

typedef const char* TreeElem_t;

#define LEFT -1
#define RIGHT 1
#define ROOT 0
#define NO_DAUGHTER NULL
#define LEN 256

#define PREORDER -1
#define INORDER 1

#define POISON ""

#define LOG_FILE "log.html"

#define BLACK "\x1b[30m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"
#define RESET "\x1b[0m"

#ifdef STACK_DEBUG
#define ON_DBG(...)  __VA_ARGS__
#else
#define ON_DBG(...)
#endif

#define ASSERT_OKAY(tree, node) do {\
    errors err = TreeError(tree, node);\
    if (err != ERR_OK) {\
        TreeDump(tree, node, err, __FILE__, __LINE__, __func__);\
        free(node);\
        assert(0);}\
    } while(0)


struct TreeNode_t {
    TreeElem_t data;

    TreeNode_t* left;
    TreeNode_t* right;
    TreeNode_t* parent;

    int side;
    int deepth;
};

struct Tree {
     TreeNode_t* root;
     size_t num_of_nodes;
};

TreeNode_t* CreatNode(Tree* tree, TreeElem_t elem);

void DeleteNode(Tree* tree, TreeNode_t* node);

void LinkRight(TreeNode_t* mother, TreeNode_t* daughter);

void LinkLeft(TreeNode_t* mother, TreeNode_t* daughter);

void PrintStrTree(const TreeNode_t* node, int order, FILE* file);

errors TreeError(Tree* tree, TreeNode_t* node);

void TreeDump_file(const Tree* tree, const TreeNode_t* node, errors err_code, const char* file, int line, const char* func);

void TreeDump(Tree* tree, const TreeNode_t* node,  errors err_code, const char* file, int line, const char* func);

void clean_file(const char* name);

void DestroyBranch(Tree* tree, TreeNode_t* node);

TreeNode_t* ReadNode(Tree* tree, FILE* file);

void AddNode(Tree* tree, TreeNode_t* node, TreeElem_t value);