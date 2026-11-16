#include "tree_dump.h"

void TreeDumpGraph(const Tree* tree, const char* reason) {
    my_assert(tree != NULL,);
    my_assert(reason != NULL,);

    FILE* file = fopen("dump.dot", "w");
    my_assert(file != NULL,);

    fprintf(file, "digraph Tree {\n");

    fprintf(file, "\tcharset=\"UTF-8\";\n");

    fprintf(file, "\trankdir=TB;\n");
    fprintf(file, "\tnode [style=filled, fillcolor=\"#00FFFF\", fontname=\"Arial\"];\n\n");

    fprintf(file, "\tedge [fontname=\"Arial\"];\n\n");

    fprintf(file, "\tlabelloc=\"t\";\n");
    fprintf(file, "\tlabeljust=\"l\";\n");

    fprintf(file, "\tfontname=\"Arial\";\n");

    fprintf(file, "\tlabel=\"Dump: %s \npointer to tree_struct: %p | pointer to root: %p | num_of_nodes: %zu\";\n",
            reason, tree, tree->root, tree->num_of_nodes);
    fprintf(file, "\tfontsize=16;\n\n");
    

    RecOutput(tree->root, file, 0);
    

    fprintf(file, "}\n");
    fclose(file);


    system("dot -Tpng dump.dot -o dump.png");
}


void RecOutput(TreeNode_t* node, FILE* file, size_t depth) {
    my_assert(node != NULL,);
    my_assert(file != NULL,);

    if (node->parent == NULL)
        fprintf(file, "\tnode%p [label=\" %s?\", fillcolor = \"#FF00FF\"];\n", node, node->data);
    else if (node->left != NULL || node->right != NULL)
        fprintf(file, "\tnode%p [label=\" %s?\"];\n", node, node->data);
    else
        fprintf(file, "\tnode%p [label=\" %s\"];\n", node, node->data);

    if (node->left != NULL) {
        fprintf(file, "\tnode%p -> node%p [color=\"#B22222\", label=\"Нет\"];\n", node, node->left);
        RecOutput(node->left, file, depth + 1);
    }     
    if (node->right != NULL) {
        fprintf(file, "\tnode%p -> node%p [color=\"#2E8B57\", label=\"Да\"];\n", node, node->right);
        RecOutput(node->right, file, depth + 1);
    }
}



void TreeDump_file(const Tree* tree, const TreeNode_t* node, errors err_code, const char* file, int line, const char* func) {
    FILE* log_file = fopen(LOG_FILE, "w"); 
    my_assert_tell(log_file != NULL, "Open-file err",);

    fprintf(log_file, "<pre>\n");
    fprintf(log_file, "========================================\n");
    fprintf(log_file, "TREE DUMP\n");
    fprintf(log_file, "Error code: %d (%s)\n", err_code, ErrCode(err_code));
    fprintf(log_file, "Called from: %s() at %s:%d\n\n", func, file, line);

    if (tree != NULL) {
        fprintf(log_file, "Tree address: [%p]\n", (void*)tree);
        fprintf(log_file, "Tree size:    %zu\n", tree->num_of_nodes);
        fprintf(log_file, "Root node:    [%p]\n", (void*)tree->root);

    } else {
        fprintf(log_file, "Tree address: NULL (Tree pointer is invalid!)\n");
    }

    fprintf(log_file, "\nCurrent node: [%p]\n", (void*)node);
    fprintf(log_file, "========================================\n");
    fprintf(log_file, "</pre>\n");

    TreeDumpGraph(tree, "In TreeDump_file");
    fprintf(log_file, "<img src=\"dump.png\">\n<hr>\n");

    fclose(log_file);
}

void TreeDump(Tree* tree, const TreeNode_t* node,  errors err_code, const char* file, int line, const char* func) {

    if (node == NULL) {
        fprintf(stdout, "node [NULL pointer]\n");
        my_assert(0,);
    }

    TreeDump_file(tree, node, err_code, file, line, func);

}

const char* ErrCode(errors err) {

    switch(err) {
        case ERR_OK:
            return "ERR_OK";
        case ERR_NULL_PTR:
            return "ERR_NULL_PTR";
        case ERR_NULL_DATA:
            return "ERR_NULL_DATA";
        case ERR_WRONG_CAPACITY:
            return "ERR_WRONG_CAPACITY";
        case ERR_WRONG_SIZE:
            return "ERR_WRONG_SIZE";
        case ERR_OVERFLOW:
            return "ERR_OVER_FLOW";
        case ERR_NO_MEMORY:
            return "ERR_NO_MEMORY";
        case ERR_ARR_CANARY:
            return "ERR_ARR_CANARY";
        case ERR_NO_PARENT:
            return "ERR_NO_PARENT";
        default:
            printf("No such error in switch-case\n");
    }

    return "ERR_OK";
}
