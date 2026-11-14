#include "akinator.h"




void Guess(Tree* tree) {
    my_assert(tree != NULL,);

    char buffer[LEN] = "";
    TreeNode_t* current_node = tree->root;

    while (current_node->right != NULL || current_node->left != NULL) {
        printf("%s\n", current_node->data);
        scanf("%s", buffer);

        if (strcmp(buffer, "y") == 0) {
            current_node = current_node->right;
        } else {
            current_node = current_node->left;
        }
    }


    strcpy(buffer, "Is it ");
    printf("Is it %s?\n", current_node->data);

    char answer[LEN] = "";
    scanf("%s", answer);
    
    if (strcmp(answer, "y") == 0) {
        printf("Great!\n");
    } else {
        char not_guessed[LEN] = "";
        printf("Please enter name of person that you thinked about\n");
        scanf("%s", not_guessed);

        char question[LEN] = "";
        printf("Please enter a question that yes for your person and no for my guess\n");
        scanf("%s", question);

        //need func
    }
}

void StartGame() {
    printf("Добро пожаловать в акинатор! Выберите режим:\n");
    printf("1. Угадать персонажа\n");
    printf("2. Показать дерево персонажей\n");
    printf("3. Добавить персонажа и его разделяющее свойство\n");
    printf("4. Выдать определение указанного объекта\n");
    printf("5. Сравнить персонажей\n");
    printf("6. Выйти без сохранения\n");
    printf("7. Выйти с сохранением\n");

    int mode = 0;
    scanf("%d", &mode);

    enum modes {GUESS = 1, SHOW = 2, ADD = 3, DEF = 4, COMPARE = 5, OUT = 6, SAVE = 7};

    switch(mode) {

        case GUESS:
            
            break;

        case SHOW:

            break;

        case ADD:

            break;

        case DEF:

            break;

        case COMPARE:

            break;

        case OUT:

            break;

        case SAVE:

            break;
    }
}