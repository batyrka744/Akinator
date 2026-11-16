#include "akinator.h"


int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    FILE* file_tree_write = fopen(TREE_FILE_WRITE, "r");
    FILE* file_tree_read = fopen(TREE_FILE_READ, "r");
    Tree tree = {0};

    StartGame(&tree, file_tree_read, file_tree_write);

    DestroyBranch(&tree, tree.root);
    fclose(file_tree_read);
    fclose(file_tree_write);
    return 0;
}

void Guess(Tree* tree) {
    my_assert(tree != NULL,);

    char buffer[LEN] = "";
    TreeNode_t* current_node = tree->root;

    while (current_node->right != NULL || current_node->left != NULL) {
        printf("%s?\n", current_node->data);
        fflush(stdin);
        scanf("%s", buffer);

        if (strcmp(buffer, "д") == 0 || strcmp(buffer, "y") == 0) {
            current_node = current_node->right;
        } else {
            current_node = current_node->left;
        }
    }

    printf("Это %s?\n", current_node->data);

    char answer[LEN] = "";
    scanf("%s", answer);
    
    if (strcmp(buffer, "д") == 0 || strcmp(buffer, "y") == 0) {
        printf("Очевидно\n");
    } else {
        AddObject(tree, current_node);
    }
}

void AddObject(Tree* tree, TreeNode_t* node) {
    my_assert(tree,);
    my_assert(node,);

    TreeElem_t expected = node->data;

    char not_guessed[LEN] = "";
    printf("Введите имя загаданного персонажа\n");
    scanf(" %[^\n]", not_guessed);

    char question[LEN] = "";
    printf("Введите вопрос, который верен для вашего персонажа, но не верен для моей догадки\n");
    scanf(" %[^\n]", question);

    TreeNode_t* ans_yes = CreatNode(tree, not_guessed);
    TreeNode_t* ans_no = CreatNode(tree, expected);

    LinkLeft(node, ans_no);
    LinkRight(node, ans_yes);


    strcpy((char*)node->data, question);
}



void StartGame(Tree* tree, FILE* file_r, FILE* file_w) {
    my_assert(tree,);
    my_assert(file_r,);
    my_assert(file_w,);

    tree->root = ReadNode(tree, file_w);
    int exit_flag = 0;

    while(exit_flag == 0) {

        printf("Добро пожаловать в акинатор! Выберите режим:\n"
        "1. Угадать персонажа\n"
        "2. Показать дерево персонажей\n"
        "3. Выдать определение указанного объекта\n"
        "4. Сравнить персонажей\n"
        "5. Выйти без сохранения\n"
        "6. Выйти с сохранением\n"
        "Введите номер режима\n");

        int mode = 0;
        scanf("%d", &mode);


        switch(mode) {

            case GUESS:
                Guess(tree);
                break;

            case SHOW:
                TreeDumpGraph(tree, "Просьба пользователя");
                system("start dump.png");
                break;

            case DEF: {
                printf("Введите имя вашего персонажа\n");
                char str[LEN] = "";
                fflush(stdin);
                scanf(" %[^\n]", str);
                Description(FindNode(tree->root, str));
                break;
            }
                
            case COMPARE: {
                printf("Введите имя первого персонажа\n");
                char str1[LEN] = "";
                fflush(stdin);
                scanf(" %[^\n]", str1);
                TreeNode_t* node1 = FindNode(tree->root, str1);

                printf("Введите имя второго персонажа\n");
                char str2[LEN] = "";
                fflush(stdin);
                scanf(" %[^\n]", str2);
                TreeNode_t* node2 = FindNode(tree->root, str2);
                
                Compare(node1, node2);
                break;
            }

            case OUT_:
                exit_flag++;
                break;

            case SAVE:
                fclose(file_w);
                FILE* file_new_tree = fopen(TREE_FILE_WRITE, "w");
                PrintStrTree(tree->root, PREORDER, file_new_tree);
                fclose(file_new_tree);
                exit_flag++;
                break;
        }
    }
    fflush(stdin);
}


TreeNode_t* FindNode(TreeNode_t* node, const char* name) {
    if (node == NULL) return NULL;

    if (strcmp(node->data, name) == 0) 
        return node;
    

    TreeNode_t* found_left = FindNode(node->left, name);
    if (found_left != NULL)
        return found_left;

    TreeNode_t* found_right = FindNode(node->right, name);
    if (found_right != NULL)
        return found_right;

    return NULL;
}

void Description(TreeNode_t* node) {
    my_assert_tell(node, "Такого персонажа не существует",);

    stack_t stk = {0};
    STACK_INIT(stk, 10);

    PushInfo(&stk, node);

    errors err = ERR_OK;

    while (stk.size > 0) {
        TreeNode_t* popped = StackPop(&stk, &err);
        if (popped->parent->left == popped) printf("не ");
        printf("%s -> ", popped->parent->data);
    }
    printf("%s\n\n", node->data);
    STACK_DESTROY(stk);
}




void Compare(TreeNode_t* node1, TreeNode_t* node2) {
    my_assert_tell(node1, "Такого персонажа не существует",);
    my_assert_tell(node2, "Такого персонажа не существует",);

    stack_t stk1 = {0};
    STACK_INIT(stk1, 10);

    stack_t stk2 = {0};
    STACK_INIT(stk2, 10);

    PushInfo(&stk1, node1);
    PushInfo(&stk2, node2);

    errors err = ERR_OK;

    TreeNode_t* popped_node1 = StackPop(&stk1, &err);
    TreeNode_t* popped_node2 = StackPop(&stk2, &err);

    int no_flag = 0;

    if (popped_node1 == popped_node2) {
        printf("И %s, и %s:\n", node1->data, node2->data);
        no_flag = 1;
    }

    for (size_t i = 1; popped_node1 == popped_node2 && popped_node1 != NULL; i++) {
        printf("%zu) ", i);

        if (popped_node1->parent->left == popped_node1) printf("не ");
        printf("%s\n", popped_node1->parent->data);

        popped_node1 = (stk1.size > 0) ? StackPop(&stk1, &err) : NULL;
        popped_node2 = (stk2.size > 0) ? StackPop(&stk2, &err) : NULL;
    }
        
    if (popped_node1 != NULL || popped_node2 != NULL) {

        if (no_flag) printf("Но %s:\n", node1->data);
        else printf("%s:\n", node1->data);
        for (size_t i = 1; popped_node1 != NULL; i++) {
            printf("%zu) ", i);
            if (popped_node1->parent->left == popped_node1) printf("не ");
            printf("%s\n", popped_node1->parent->data);

            popped_node1 = (stk1.size > 0) ? StackPop(&stk1, &err) : NULL;
        }

        if (popped_node2 != NULL) printf("А %s:\n", node2->data);
        for (size_t i = 1; popped_node2 != NULL; i++) {
            printf("%zu) ", i);
            if (popped_node2->parent->left == popped_node2) printf("не ");
            printf("%s\n", popped_node2->parent->data);

            popped_node2 = (stk2.size > 0) ? StackPop(&stk2, &err) : NULL;
        }
    }
    printf("\n");
    
    STACK_DESTROY(stk1);
    STACK_DESTROY(stk2);
}

/**
 * @brief pushs description into the stack
 * 
 * @param[in, out] stk stack
 * @param[in] node remember to free node->data
 */
void PushInfo(stack_t* stk, TreeNode_t* node) {
    my_assert(stk,);
    my_assert(node,);

    TreeNode_t* current_node = node;
    
    while (current_node->parent) {
        StackPush(stk, current_node);
        current_node = current_node->parent;
    }
}