
#include "tree_dump.h"


TreeNode_t* ReadNode(Tree* tree, FILE* file) {
    my_assert(file != NULL, NULL);

    int ch = 0;

    while (isspace(ch = fgetc(file)));
    
    if (ch == EOF) return NULL;


    if (ch == '{') {
        char buffer[LEN] = "";
    
        fscanf(file, " \"%255[^\"]\"", buffer);

        TreeNode_t* node = CreatNode(tree, buffer);
    
        TreeNode_t* left_egg = ReadNode(tree, file);
        if (left_egg != NULL) 
            LinkLeft(node, left_egg); 
        
        TreeNode_t* right_egg = ReadNode(tree, file);
        if (right_egg != NULL) 
            LinkRight(node, right_egg); 
        
        while (isspace(ch = fgetc(file)));


        if (ch == '}')
            return node;
        else 
            my_assert_tell(0, "read-error", NULL);
    
    } else if (ch == 'n') {
        
        fgetc(file); 
        fgetc(file); 
        return NULL;
    }

    return NULL;
}


void AddNode(Tree* tree, TreeNode_t* node, TreeElem_t value) {
    my_assert(tree != NULL,);

    if (node == NULL)
        tree->root = CreatNode(tree, value);

    else if (value < node->data) {
        if (node->left == NULL) {
            TreeNode_t* new_node = CreatNode(tree, value);
            LinkLeft(node, new_node);
        } else {
            AddNode(tree, node->left, value);
        }

    } else if (value >= node->data) {
        if (node->right == NULL) {
            TreeNode_t* new_node = CreatNode(tree, value);
            LinkRight(node, new_node);
        } else {
            AddNode(tree, node->right, value);
        }
    }
}

TreeNode_t* CreatNode(Tree* tree, TreeElem_t elem) {
    my_assert(elem != NULL, NULL);

    TreeNode_t* node = (TreeNode_t*)calloc(1, sizeof(TreeNode_t));
    my_assert_tell(node != NULL, "NO_MEMORY", NULL);

    node->data = strdup(elem);
    node->left = NO_DAUGHTER;
    node->right = NO_DAUGHTER;

    tree->num_of_nodes++;
    ASSERT_OKAY(tree, node);

    return node;
}

void DeleteNode(Tree* tree, TreeNode_t* node) {
    ASSERT_OKAY(tree, node);

    if (node->parent != NULL) {
        if (node->parent->left == node) node->parent->left = NULL;
        if (node->parent->right == node) node->parent->right = NULL;
    } else {
        tree->root = NULL;
    }
        
    if (node->left != NULL) 
        node->left->parent = NULL;
    
    if (node->right != NULL) 
        node->right->parent = NULL;


    node->data = POISON;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;

    tree->num_of_nodes--;
    free(node);
}

void DestroyBranch(Tree* tree, TreeNode_t* node) {
    my_assert(tree != NULL,);

    if (node->left != NULL)
        DestroyBranch(tree, node->left);
    if (node->right != NULL)
        DestroyBranch(tree, node->right);

    DeleteNode(tree, node);
}


void LinkRight(TreeNode_t* mother, TreeNode_t* daughter) {
    my_assert(mother != NULL,);

    my_assert_tell(mother->right == NO_DAUGHTER, RED "You've just tried to kill daughter...\n" RESET,);
    mother->right = daughter;
    my_assert_tell(daughter->parent == NULL, RED "You've just tried to kill mother...\n" RESET,);
    daughter->parent = mother;
}

void LinkLeft(TreeNode_t* mother, TreeNode_t* daughter) {
    my_assert(mother != NULL,);

    my_assert_tell(mother->left == NO_DAUGHTER, RED "You've just tried to kill daughter...\n" RESET,);
    mother->left = daughter;
    my_assert_tell(daughter->parent == NULL, RED "You've just tried to kill mother...\n" RESET,);
    daughter->parent = mother;
}

void PrintStrTree(const TreeNode_t* node, int order, FILE* file) {
    my_assert(node != NULL,);

    fprintf(file, "{");
    
    switch (order) {

        case PREORDER:

            fprintf(file, "\"%s\"", node->data);

            if (node->left)
                PrintStrTree(node->left, order, file);
            else
                fprintf(file, "nil ");

            if (node->right) 
                PrintStrTree(node->right, order, file);
            else
                fprintf(file, "nil ");

            break;


        case INORDER:

            if (node->left)
                PrintStrTree(node->left, order, file);
            else 
                fprintf(file, "nil ");

            fprintf(file, "\"%s\"", node->data);

            if (node->right) 
                PrintStrTree(node->right, order, file);
            else
                fprintf(file, "nil ");

            break;
    }
    

    

    fprintf(file, "} ");
}


/**
 * @brief checks error stack structure
 * 
 * @param[in] node structure with the node and its parameters
 * @return errors error code
 */
errors TreeError(Tree* tree, TreeNode_t* node) {

    if (node == NULL) {
        return ERR_NULL_PTR;
    }
    if (node->data == NULL) {
        return ERR_NULL_DATA;
    }
    if (node->parent == NULL && node->side != 0) {
        return ERR_NO_PARENT;
    }

    return ERR_OK;
}

void clean_file(const char* name) {
    my_assert(name != NULL,);
    fclose(fopen(name, "w"));
}



