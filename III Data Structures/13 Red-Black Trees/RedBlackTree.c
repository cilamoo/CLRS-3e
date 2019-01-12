#include <stdio.h> 
#include <stdlib.h> 

typedef struct node{
    int key;
    int color;
    struct node *p;
    struct node *left;
    struct node *right;
}node;

typedef struct tree {
    struct node *root;
    struct node *nil;
}tree;


node* rb_tree_search(tree *T, node *x, int k){
    if(x == T->nil  || k == x->key)
        return x;
    if(k < x->key)
        return rb_tree_search(T,x->left,k);
    else
        return rb_tree_search(T,x->right,k);
}

node* rb_iterative_tree_search(tree *T, node *x, int k){
    while(x != T->nil && k != x->key){
        if(k < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

node* rb_tree_minimum(tree *T, node *x){
    while(x->left != T->nil){
        x = x->left;
    }
    return x;
}

node* rb_tree_maximum(tree *T, node *x){
    while(x->right != T->nil){
        x = x->right; 
    }
    return x;
}

node* rb_tree_successor(tree *T, node *x){
    node *y;
    if(x->right != T->nil)
        return rb_tree_minimum(T, x->right);
    y = x->p;
    while(y != T->nil && x == y->right){
        x = y;
        y = y->p;
    }
    return y;
}

node* rb_tree_predecessor(tree *T, node *x){
    node *y;
    if(x->left != T->nil)
        return rb_tree_maximum(T,x->left);
    y = x->p;
    while(y != T->nil && x == y->left){
        x = y;
        y = y->p;
    }
    return y;
}

void left_rotate(tree *T, node *x){
    node *y = x->right;
    x->right = y->left;
    if(y->left != T->nil)
        y->left->p = x;
    y->p = x->p;
    if(x->p == T->nil)
        T->root = y;
    else if(x == x->p->left)
        x->p->left = y;
    else 
        x->p->right = y;
    y->left = x;
    x->p = y;
}

void right_rotate(tree *T, node *x){
    node *y = x->left;
    x->left = y->right;
    if(y->right != T->nil)
        y->right->p = x;
    y->p = x->p;
    if(x->p == T->nil)
        T->root = y;
    else if(x == x->p->left)
        x->p->left = y;
    else 
        x->p->right = y;
    y->right = x;
    x->p = y;
}

void rb_insert_fixup(tree *T, node *z){
    node *y;
    while(z->p->color == 0){ /* number 0 denotes RED */
        if(z->p == z->p->p->left){
            y = z->p->p->right;
            if(y->color == 0){
                z->p->color = 1;
                y->color = 1;
                z->p->p->color = 0;
                z = z->p->p;
            }
            else{
                if(z == z->p->right){
                    z = z->p;
                    left_rotate(T,z);
                }
                z->p->color = 1;
                z->p->p->color = 0;
                right_rotate(T,z->p->p);
            }
        }
        else{
            y = z->p->p->left;
            if(y->color == 0){
                z->p->color = 1;
                y->color = 1;
                z->p->p->color = 0;
                z = z->p->p;
            }
            else{
                if(z == z->p->left){
                    z = z->p;
                    right_rotate(T,z);
                }
                z->p->color = 1;
                z->p->p->color = 0;
                left_rotate(T,z->p->p);
            }
        }
    }
    T->root->color = 1;
}

void rb_insert(tree *T, node *z){
    node *y = T->nil;
    node *x = T->root;
    while(x != T->nil){
        y = x;
        if(z->key < x->key)
            x = x->left;
        else 
            x = x->right;
    }
    z->p = y; 
    if(y == T->nil)
        T->root = z;
    else if(z->key < y->key)
        y->left = z;
    else 
        y->right = z;
    z->left = T->nil;
    z->right = T->nil;
    z->color = 0;          /* RED */
    rb_insert_fixup(T,z);
}

void rb_transplant(tree *T, node *u, node *v){
    if(u->p == T->nil)
        T->root = v;
    else if(u == u->p->left)
        u->p->left = v;
    else
        u->p->right = v;
    v->p = u->p;
}

void rb_delete_fixup(tree *T, node *x){
    node *w;
    while(x != T->root && x->color == 1){
        if(x == x->p->left){
            w =  x->p->right;
            if(w->color == 0){
                w->color = 1;
                x->p->color = 0;
                left_rotate(T,x->p);
                w = x->p->right;
            }
            if(w->left->color == 1 && w->right->color == 1){
                w->color = 0;
                x = x->p;
            }
            else{
                if(w->right->color == 1){
                    w->color = 0;
                    w->left->color = 1;
                    right_rotate(T,w);
                    w = x->p->right;
                }
                w->color = x->p->color;
                x->p->color = 1;
                w->right->color = 1;
                left_rotate(T,x->p);
                x = T->root;
            }
        }
        else{
            w = x->p->left;
            if(w->color == 0){
                w->color = 1;
                x->p->color = 0;
                right_rotate(T,x->p);
                w = x->p->left;
            }
            if(w->right->color == 1 && w->left->color == 1){
                w->color = 0;
                x = x->p;
            }
            else{
                if(w->left->color == 1){
                    w->color = 0;
                    w->right->color = 1;
                    left_rotate(T,w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = 1;
                w->left->color = 1;
                right_rotate(T,x->p);
                x = T->root;
            }
        }
    }
    x->color = 1;
}

void rb_delete(tree *T, node *z){
    node *x;
    node *y = z;
    int y_original_color = y->color;

    if(z->left == T->nil){
        x = z->right;
        rb_transplant(T,z,z->right);
    }
    else if(z->right == T->nil){
        x = z->left;
        rb_transplant(T,z,z->left);
    }
    else{
        y = rb_tree_minimum(T,z->right);
        y_original_color = y->color;
        x = y->right;

        if(y->p == z){
            x->p = y;
        }
        else{
            rb_transplant(T,y,y->right);
            y->right = z->right;
            y->right->p = y;
        }
        rb_transplant(T,z,y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
    }

    if(y_original_color == 1)
        rb_delete_fixup(T,x);
    
}

void nil_init(node *nn){
    nn->key = 999;
    nn->color = 1;      /* BLACK */
    nn->p = NULL;
    nn->left = NULL;
    nn->right = NULL;
}

node* create_rb_tree(tree *T, int *a, int n){
    int i;
    node *pre_mem;
    if((pre_mem = malloc(n*sizeof(node))) == NULL){
        printf("malloc failed in function create_tree\n");
        exit(1);
    }

    for(i = 0; i < n; i++){
        pre_mem[i].key = a[i];
        pre_mem[i].p = T->nil;
        pre_mem[i].left = T->nil;
        pre_mem[i].right = T->nil;
        rb_insert(T,&pre_mem[i]);
    }
     return pre_mem;
}

void rb_free(node *node){
    free(node);
}

void inoder_rb_tree_walk(tree *T, node *x){
    if(x != T->nil){
        inoder_rb_tree_walk(T,x->left);
        printf("key:%d p:%d left:%d right:%d color:%s \n",\
            x->key,x->p->key,x->left->key,x->right->key,(x->color?"BLACK":"RED"));
        inoder_rb_tree_walk(T,x->right);
    }
}

int main(){
    tree T;
    node *rt,*tmp_node;
    node node_nil;
    nil_init(&node_nil);
    T.root = T.nil = &node_nil;
    
    int input_array[12] = {19,4,13,8,12,15,6,11,17,2,20,3};
    int n = 12;
    
    rt = create_rb_tree(&T,input_array,n);
    inoder_rb_tree_walk(&T,T.root);
    printf("Search key 6, the result is %d\n",rb_iterative_tree_search(&T,T.root,6)->key);
    printf("root——%d's successor is %d\n",T.root->key,rb_tree_successor(&T,T.root)->key);
    printf("root——%d's predecessor is %d\n",T.root->key,rb_tree_predecessor(&T,T.root)->key);
    printf("minimum is %d\n",rb_tree_minimum(&T,T.root)->key);
    printf("maximum is %d\n",rb_tree_maximum(&T,T.root)->key);
    /* Test 1
    printf("Deleting root——%d,after deleting,red black tree output is \n",T.root->key);
    rb_delete(&T,T.root);
    inoder_rb_tree_walk(&T,T.root);
    */
   
    /* Test 2 */ 
    tmp_node = rb_iterative_tree_search(&T,T.root,17);
    printf("Deleting node(17), key is %d\n",tmp_node->key);
    rb_delete(&T,tmp_node);
    inoder_rb_tree_walk(&T,T.root);
    
    rb_free(rt);
}
