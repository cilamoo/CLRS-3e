#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <stdio.h>

/*
  Algorithm     Average	     Worst case
Space		O(n)     	O(nlog n)
Search		O(log n)	O(n)
Insert		O(log n)	O(n)
Delete		O(log n)	O(n)
*/

/* In this file, not check return value of malloc's call */

#define MaxLevel 16

typedef struct skiplist_node{
    int key;
    int value;
    struct skiplist_node **forward;
}skiplist_node;

typedef struct skiplist{
    int level;
    skiplist_node *header;
}skiplist;

static skiplist_node NIL_node = {INT_MAX,0,NULL}; 

skiplist* skiplist_init(){
    int i;
    skiplist *sl = malloc(sizeof(skiplist));
    sl->level = 1;
    sl->header = malloc(sizeof(skiplist_node));
    sl->header->key = 0;
    sl->header->value = 0;
    sl->header->forward = (skiplist_node **)malloc(MaxLevel*sizeof(skiplist_node*));
    for(i = 0; i < MaxLevel; i++){
        sl->header->forward[i] = &NIL_node;
    }

    return sl;
}

int search(skiplist *list, int search_key){
    int i;
    skiplist_node *x;

    x = list->header;

    for(i = list->level; i >= 1; i--){
        while(x->forward[i-1]->key < search_key){
            x = x->forward[i-1];
        }
    }

    x = x->forward[0];
    if(x->key == search_key)
        return x->value;
    else 
        return -1; /*Maybe x->value also equals -1*/
}

int random_level(){
    int new_level = 1;
    
    while(rand() < RAND_MAX/2){
        new_level += 1;
    }
    return (new_level > MaxLevel) ? MaxLevel : new_level;
}

skiplist_node* make_node(int new_level, int search_key, int value){
    skiplist_node *node;
    
    node = (skiplist_node *)malloc(sizeof(skiplist_node) + new_level*sizeof(skiplist_node*));
    node->key = search_key;
    node->value = value;
    node->forward = (skiplist_node**)(node+1);
    
    return node;
}

void release_node(skiplist_node *x){
    free(x);
}

void insert(skiplist *list, int search_key, int new_value){
    skiplist_node *update[MaxLevel];
    skiplist_node *x;
    int i,new_level;

    x = list->header;
    for(i = list->level; i >= 1; i--){
        while(x->forward[i-1]->key < search_key){
            x = x->forward[i-1];
        }
        update[i-1] = x;
    }
    x = x->forward[0];

    if(x->key == search_key){
        x->value = new_value;
    }
    else{
        new_level = random_level();
        printf("Insert search_key = %d, value = %d, new_level = %d\n", search_key, new_value, new_level);
        if(new_level > list->level){
            for(i = list->level + 1; i <= new_level; i++){
                update[i-1] = list->header; 
            }
        }
        x = make_node(new_level, search_key, new_value);
        for(i = 1; i <= new_level; i++){
            x->forward[i-1] = update[i-1]->forward[i-1];
            update[i-1]->forward[i-1] = x;
        }
    }
    
}

void delete(skiplist *list, int search_key){
    skiplist_node *update[MaxLevel];
    skiplist_node *x;
    int i;

    x = list->header;
    for(i = list->level; i >= 1; i--){
        while(x->forward[i-1]->key < search_key){
            x = x->forward[i-1];
        }
        update[i-1] = x;
    }
    x = x->forward[0];
    if(x->key == search_key){
        for(i = 0; i < list->level; i++){
            if(update[i]->forward[i] != x){
                break;
            }
            update[i]->forward[i] = x->forward[i];
        }
        release_node(x);
    }
    while(list->level > 1 && list->header->forward[list->level-1] == &NIL_node){
        list->level -= 1;
    }

}

void release_skiplist(skiplist *list){
    skiplist_node *x;
    x = list->header->forward[0];
    while(x != &NIL_node){
        free(x);
        x = x->forward[0];
    }
    free(list->header->forward);
    free(list->header);
    free(list);
}

void print_skiplist(skiplist *list){
    skiplist_node *x;
    x = list->header->forward[0];
    while(x != &NIL_node){
        printf("key = %d value = %d\n", x->key, x->value);
        x = x->forward[0];
    }
}

int main(){
    skiplist *list;
    int sc;
    list = skiplist_init();

    srand((int)time(0));
    insert(list, 3, 100);
    insert(list, 7, 101);
    insert(list, 12, 102);
    insert(list, 27, 103);
    insert(list, 21, 104);
    insert(list, 26, 105);
    
    sc = search(list,12);
    printf("search result is %d, should == 102 \n", sc);

    print_skiplist(list);
    
    printf("delete node , value = 27\n");
    delete(list,27);
    print_skiplist(list);

    release_skiplist(list);
    return 0;
}
