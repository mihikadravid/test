#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>

typedef struct node
{   char* name;
    int data;
    struct node *left, *right, *parent;
}node;
typedef struct stack
{
    int size;
    int top;
    struct node** array;
}stack;
typedef struct node* bst;
#define MAX_SIZE 100
void initBST(struct node** node);
struct node* newNode(int data,char* Name);
struct node* remove_Node(struct node* root, int data);
struct node* insertNode(struct node* root, int data,char* Name);
void postorder(struct node* root);
void Display_Level(struct node* root, int level);
void destroyTree(struct node* root);
bool search_BST(struct node* root, int key);


//STACK FUNCTIONS FOR POSTORDER

struct stack* createstack(int size);
int isEmpty(struct stack* stack);
void push(struct stack* stack, struct stack* node);
struct node* pop(struct stack* stack);
int isFull(struct stack* stack);
struct node* Max_Left(struct node* root);





void initBST(struct node** node){
    *node = NULL;
    return;
}

struct node* newNode(int data,char* Name){
    struct node* temp = malloc(sizeof(struct node));
    temp->name= strdup(Name);
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = NULL;
    return temp;
}



struct node* insertNode(struct node* root, int data, char* Name){
    if(root == NULL)
        return newNode(data,Name);

    if(data < root->data){
        struct node* l = insertNode(root->left, data,Name);
        root->left = l;
        l->parent = root;
    }
    else if(data > root->data){
        struct node* r = insertNode(root->right, data,Name);
        root->right = r;
        r->parent = root;
    }

    return root;
}

struct node* remove_Node(struct node* root, int data){
    if(root == NULL)
        return root;

    if(data < root->data)
        root->left = remove_Node(root->left, data);
    else if(data > root->data)
        root->right = remove_Node(root->right, data);
    else{
        if(root->left == NULL){
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL){
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        struct node* temp = Max_Left(root->left);

        root->data = temp->data;

        root->left = remove_Node(root->left, temp->data);
    }
    return root;
}

bool search_BST(struct node* root, int key){
    if(root == NULL)
        return false;

    struct node* curr;
     curr= root;
    while(curr){
        if(curr->data == key)
            return true;
        if(curr->data > key)
            curr = curr->left;
        else
            curr = curr->right;
    }
    return false;
}


void postorder(struct node* root){
    if(root == NULL)
        return;
    struct stack* s1 = createstack(MAX_SIZE);
    struct stack* s2 = createstack(MAX_SIZE);

    push(s1, root);
    struct node* node;

    while(!isEmpty(s1)){
        node = pop(s1);
        push(s2, node);

        if(node->left)
            push(s1, node->left);
        if(node->right)
            push(s1,node->right);
    }
    while(!isEmpty(s2))
    {
        node = pop(s2);
        printf("%d %s ", node->data, node->name);
    }
}





void Display_Level(struct node* root, int level){
    if(root == NULL)
        return;
    if(level == 1)
    {   printf("%d ", root->data);
        printf("%s",root->name);}
    else if(level > 1){
        Display_Level(root->left,level - 1);
        Display_Level(root->right, level - 1);
    }
}


void destroyTree(struct node* root){
    if (root == NULL) return;

    destroyTree(root->left);
    destroyTree(root->right);

    printf("\n Deleting node: %i", root->data);
    free(root);
}




struct stack* createstack(int size){
    struct stack* Stack = malloc(sizeof(struct stack));
    Stack->size = size;
    Stack->top = -1;
    Stack->array = (struct stack*)malloc(Stack->size * sizeof(struct node));
    return Stack;
}


struct node* Max_Left(struct node* root){
    struct node* current = root;

    while(current != NULL && current->right != NULL)
        current = current->right;

    return current;
}

int isFull(struct stack* stack){
    return stack->top == stack->size - 1;
}


int isEmpty(struct stack* stack){
    return stack->top == -1;
}


void push(struct stack* stack, struct stack* node){
    if(isFull(stack))
        return;
    stack->array[++stack->top] = node;
}


struct node* pop(struct stack* stack){
    if(isEmpty(stack))
        return NULL;
    return stack->array[stack->top--];
}
int main()
{   char fname[20];
    int option, no, no1, no2, no3;
    struct node* root;
    initBST(&root);
    int ext = 1;
    while(ext == 1){
        printf("Choose from the following options - (1 - Insert Node, 2 - Remove Node,3 - Search Node \n4 - Postorder Traversal,5 - Display Level , 6 - Destroy Tree)\n");
        scanf("%d", &option);
        switch(option){
            case 1:
                printf("Enter Value of Node to Insert : ");
                scanf("%d",&no);
                while ((getchar()) != '\n');
                printf("Enter Name of Node to Insert : ");
                gets(fname);
                root = insertNode(root, no, fname);
                break;
            case 2:
                printf("Enter Value of Node to Remove : ");
                scanf("%d",&no3);
                root = remove_Node(root, no3);

                break;
            case 3:
                printf("Enter Value of Node to Search : ");
                scanf("%d",&no1);
                if(search_BST(root, no1) == true)
                    printf("%i is present in the BST.", no1);
                else
                    printf("%i is not present in the BST.", no1);
                break;
            case 4:
                postorder(root);
                break;
            case 5:
            printf("Enter Level to Display : ");
            scanf("%d",&no2);
            Display_Level(root, no2);
                break;
            case 6:
                destroyTree(root);
                break;
            default:
                printf("Enter From The Given Options Only");
        }
        printf("\nDo you want to continue? 1-yes,0-no ");
        scanf("%d", &ext);
    }

    return 0;
}

