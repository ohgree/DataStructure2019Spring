#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM 100
#define RANGE 1000

typedef struct node {
    int val;
    struct node* left;
    struct node* right;
    struct node* parent;
} node;

typedef struct queue {
    struct queue* next;
    node* element;
} queue;

//a factory to create a node
node* get_a_node(int x, node* parent) {
    node* nd = malloc(sizeof(node));
    nd->val = x;
    nd->left = NULL;
    nd->right = NULL;
    nd->parent = parent;
    return nd;
}

//a factory to create a queue element
queue* get_a_queue(node* element) {
    queue* q = malloc(sizeof(queue));
    q->next = NULL;
    q->element = element;
    return q;
}

//function to free queue's memory
void free_queue(queue** q) {
    queue* current_q = *q;
    while(current_q != NULL) {
        *q = current_q->next;
        free(current_q);
        current_q = *q;
    }
}

//put nodes into q
void queue_put(node* n, queue** last) {
    if(n->left != NULL) {
        (*last)->next = get_a_queue(n->left);
        (*last) = (*last)->next;
    }
    if(n->right != NULL) {
        (*last)->next = get_a_queue(n->right);
        (*last) = (*last)->next;
    }
}

//insert a node into a heap
void heap_insert(node** root, int x) {
    //insert new node if the heap is empty
    if(*root == NULL) {
        *root = get_a_node(x, NULL);
    }
    //serach for a proper insert point
    else {
        queue* q = get_a_queue(*root);
        queue* current_q = q;
        queue* last_q = q;
        node* current_node;

        while(current_q != NULL) {
            //get one node out of queue
            current_node = current_q->element;

            if(current_node->left == NULL) {
                current_node->left = get_a_node(x, current_node);
                current_node = current_node->left;
            }
            else if(current_node->right == NULL) {
                current_node->right = get_a_node(x, current_node);
                current_node = current_node->right;
            }
            else {
                queue_put(current_node, &last_q);
                    //increment the current pointer
                current_q = current_q->next;
                continue;
            }

                //put the node to proper point
            while(current_node->parent != NULL && current_node->parent->val < current_node->val) {
                    //swap the value
                int temp = current_node->parent->val;
                current_node->parent->val = current_node->val;
                current_node->val = temp;
                current_node = current_node->parent;
            }
            break;

        }

        free_queue(&q);
    }
    return;
}

void heap_remove(node** root) {
    if(*root != NULL) {
        queue* q = get_a_queue(*root);
        queue* current_q = q;
        queue* last_q = q;
        queue* previous_q;
        node* current_node;

        //find the last node
        while(current_q != NULL) {
            current_node = current_q->element;

            queue_put(current_node, &last_q);

            previous_q = current_q;
            current_q = current_q->next;
        }
        current_node = previous_q->element;
        free_queue(&q);

        //remove last node and get the value to root
        if(current_node->parent == NULL) {
            free(current_node);
            *root = NULL;
        }
        else {
            (*root)->val = current_node->val;
            current_node = current_node->parent;
            if(current_node->right != NULL) {
                free(current_node->right);
                current_node->right = NULL;
            }
            else {
                free(current_node->left);
                current_node->left = NULL;
            }
            //move down the value
            int a, b, c;
            current_node = *root;
            while(1) {
                if(current_node->left == NULL) {
                    //implies current->right == NULL is true
                    break;
                }
                else if(current_node->right == NULL) {
                    a = current_node->val;
                    b = current_node->left->val;
                    if(a < b) {
                        current_node->val = b;
                        current_node->left->val = a;
                        current_node = current_node->left;
                    }
                    else {
                        break;
                    }
                }
                else {
                    a = current_node->val;
                    b = current_node->left->val;
                    c = current_node->right->val;
                    //a is the largest, do nothing
                    if(a >= b && a >= c) {
                        break;
                    }
                    //b is the largest, swap a and b
                    else if(b > a && b >= c) {
                        current_node->left->val = a;
                        current_node->val = b;
                        current_node = current_node->left;
                    }
                    //c is the largest, swap a and c
                    else {
                        current_node->right->val = a;
                        current_node->val = c;
                        current_node = current_node->right;
                    }
                }
            }
        }
    }
}

void print_heap(node** root) {
    if(*root != NULL) {
        queue* q = get_a_queue(*root);
        queue* current_q = q;
        queue* last_q = q;
        node* test;
        while(current_q != NULL) {
            test = current_q->element;
            queue_put(test, &last_q);
            printf("%d ", test->val);
            current_q = current_q->next;
        }
        free_queue(&q);
        printf("\n");
    }
}

//linear search for max of the array
int max(int* a, int length, int* index) {
    int i, max = a[0];
    *index = 0;
    for(i = 0; i < length; i++) {
        if(a[i] > max) {
            max = a[i];
            *index = i;
        }
    }
    return max;
}

int main () {
    node *root = NULL;
    int i, r, m;
    int verifier[NUM];

    //srand(time(NULL));

    heap_insert(&root, 4);
    print_heap(&root);
    heap_insert(&root, 5);
    print_heap(&root);
    heap_insert(&root, 6);
    print_heap(&root);
    heap_insert(&root, 7);
    print_heap(&root);
    heap_insert(&root, 8);
    print_heap(&root);
    heap_remove(&root);
    print_heap(&root);
    heap_remove(&root);
    print_heap(&root);
    heap_remove(&root);
    print_heap(&root);
    /*
    for(i = 0; i < NUM; i++) {
        r = rand()%RANGE;
        heap_insert(&root, r);
        verifier[i] = r;
    }

    while(1) {
        r = rand()%RANGE;

        m = max(verifier, NUM, &i);
        if(verifier[i] != root->val) {
            printf("Wrong!!\n");
            exit(1);
        }

        heap_remove(&root);
        heap_insert(&root, r);
        verifier[i] = r;
    }*/

    return 0;
}
