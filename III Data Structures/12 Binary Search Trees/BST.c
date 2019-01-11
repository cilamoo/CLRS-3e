#include <stdlib.h> 
#include <stdio.h> 

typedef struct node{
    int key;
    struct node *p;
    struct node *left;
    struct node *right;
}node;

typedef struct tree{
    struct node *root;
}tree;

node* tree_search(node *x, int k){
    if(x == NULL || k == x->key)
        return x;
    if(k < x->key)
        return tree_search(x->left,k);
    else
        return tree_search(x->right,k);
}

node* iterative_tree_search(node *x, int k){
    while(x != NULL && k != x->key){
        if(k < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

node* tree_minimum(node *x){
    while(x->left != NULL){
        x = x -> left;
    }
    return x;
}

node* tree_maximum(node *x){
    while(x->right != NULL){
        x = x->right; 
    }
    return x;
}

node* tree_successor(node *x){
    node *y;
    if(x->right != NULL)
        return tree_minimum(x->right);
    y = x->p;
    while(y != NULL && x == y->right){
        x = y;
        y = y->p;
    }
    return y;
}

node* tree_predecessor(node *x){
    node *y;
    if(x->left != NULL)
        return tree_maximum(x->left);
    y = x->p;
    while(y!=NULL && x == y->left){
        x = y;
        y = y->p;
    }
    return y;
}

void tree_insert(tree *t, node *z){
    node *y = NULL;
    node *x = t->root;
    while(x != NULL){
        y = x;
        if(z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    
    z->p = y;
    if(y == NULL)
        t->root = z;
    else if(z->key < y->key)
        y->left = z;
    else 
        y->right = z;
}

void transplant(tree *t, node *u, node *v){
    if(u->p == NULL)
        t->root = v;
    else if(u == u->p->left)
        u->p->left = v;
    else 
        u->p->right = v;
    
    if(v != NULL)
        v->p = u->p;
}

void tree_delete(tree *t, node *z){
    node *y;
    if(z->left == NULL)
        transplant(t,z,z->right);
    else if(z->right == NULL)
        transplant(t,z,z->left);
    else{
        y = tree_minimum(z->right);
        if(y->p != z){
            transplant(t,y,y->right);
            y->right = z->right;
            z->right->p = y;
        }
        transplant(t,z,y);
        y->left = z->left;
        z->left->p = y;
    }
}

node* create_tree(tree *t, int *a, size_t n){
    int i;
    node *pre_mem;
    if((pre_mem= malloc(n*sizeof(node))) == NULL){
        printf("malloc failed in function create_tree\n");
        exit(1);
    }

    for(i = 0; i < n; i++){
        pre_mem[i].key = a[i];
        pre_mem[i].p = NULL;
        pre_mem[i].left = NULL;
        pre_mem[i].right = NULL;
        tree_insert(t,&pre_mem[i]);
    }
    return pre_mem;
}

void tree_free(node *node){
    free(node);
}

void inoder_tree_walk(node *x){
    if(x != NULL){
        inoder_tree_walk(x->left);
        printf(" %d ", x->key);
        inoder_tree_walk(x->right);
    }
}

int main(){
    node *tmp,*rt,*val;
    tree t;
    t.root = NULL;

    int a[8] = {12, 5, 18, 2, 9, 15, 19, 17};
    size_t n = 8;

    tmp = create_tree(&t, a, n);
    printf("After inserting:");
    inoder_tree_walk(t.root);
    printf("\nminimum: %d",tree_minimum(t.root)->key);
    printf("\nmaximum: %d",tree_maximum(t.root)->key);
    
    rt = tree_search(t.root,9);
    printf("\n%d's successor is %d",9,tree_successor(rt)->key);
    printf("\n%d's predecessor is %d",9,tree_predecessor(rt)->key);
    
    printf("\nAfter deleting 9:");
    tree_delete(&t,rt);
    inoder_tree_walk(t.root);
    printf("\n");
    tree_free(tmp);

    return 0;
}
