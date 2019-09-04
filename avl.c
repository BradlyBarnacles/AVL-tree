#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
    struct node* children[2];
    int data;
    int hight;
};

struct node* init_node(int data){
    struct node* new_node = malloc(sizeof(struct node));
    new_node->data = data;
    new_node->children[0] = NULL;
    new_node->children[1] = NULL;
    new_node->hight = 1;
    return new_node;
}

int max(int a, int b){
    if(a>b){
        return a;
    }
    else{
        return b;
    }
}

int hight(struct node* node){
    if(node == NULL){
        return 0;
    }
    else{
        return node->hight;
    }
}

int Getbalance(struct node* node){
    if(node == NULL){
        return 0;
    }
    else{
        return hight(node->children[1]) - hight(node->children[0]);
    }
}


struct node* rotate(struct node* x, int side){
    struct node* y = x->children[side];
    struct node* m = y->children[!side];
    y->children[!side] = x;
    x->children[side] = m;
    x->hight = 1 + max(hight(x->children[0]), hight(x->children[1]));
    y->hight = 1 + max(hight(y->children[0]), hight(y->children[1]));
    printf("rotate %d, %d", side, x->data);
    return y;
};

struct node* add_item(struct node* tree, int data){
    int side;
    if(tree==NULL){
        return init_node(data);
    }

    if(tree->data == data){
        return tree;
    }
    else{
        side = (tree->data > data);
        tree->children[side] = add_item(tree->children[side], data);
    }

    tree->hight = 1 + max(hight(tree->children[0]), hight(tree->children[1]));

    int balance = Getbalance(tree);

    if(balance >= 2 || balance <= -2){
        side = (balance>0);
        if(balance * Getbalance(tree->children[side]) < 0){
            tree->children[side] = rotate(tree->children[side], !side);
        }
        tree = rotate(tree, side);
    }

    return tree;
}

void preorder(struct node* tree){
    if(tree != NULL){
        printf("[%d", tree->data);
        preorder(tree->children[0]);
        preorder(tree->children[1]);
        printf("]");
    }
}

int main(){
    struct node* tree = NULL;
    tree = add_item(tree, 20);
    tree = add_item(tree, 10);
    tree = add_item(tree, 25);
    tree = add_item(tree, 5);
    tree = add_item(tree, 3);
    tree = add_item(tree, 12);
    preorder(tree);
}
