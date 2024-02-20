#ifndef tree_h
#define tree_h


#define TREE struct tree
#define MAX_LEN 128


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct tree {
    int val;
    int height;
    TREE* left;
    TREE* right;
};


TREE* init(int val) {
    TREE* unit = (TREE*)malloc(sizeof(TREE));
    unit->val = val;
    unit->height = 1;
    unit->right = NULL;
    unit->left = NULL;
    
    return unit;
}


int get_hght(TREE* unit) {
    if (unit)
        return unit->height;
    
    return 0;
}


void def_hght(TREE* unit) {
    unit->height = get_hght(unit->left);
    
    if (unit->height < get_hght(unit->right))
        unit->height = get_hght(unit->right);
    unit->height++;
}


TREE* l_rotation(TREE* unit) {
    TREE* tmp = unit->right; // 4
    unit->right = tmp->left;
    tmp->left = unit;
    def_hght(unit);
    def_hght(tmp);
    
    return tmp;
}


TREE* r_rotation(TREE* unit) {
    TREE* tmp = unit->left;
    unit->left = tmp->right;
    tmp->right = unit;
    def_hght(unit);
    def_hght(tmp);
    
    return tmp;
}


TREE* balance(TREE* unit) {
    int right = get_hght(unit->right);
    int left = get_hght(unit->left);
    TREE* root = unit;
    
    if (abs(right - left) < 2)
        def_hght(unit);
    
    else if (right - left == 2) {
        if (get_hght(unit->right->right) >= get_hght(unit->right->left))
//            small left rotation
            root = l_rotation(unit);
        else {
//            big left rotation
            unit->right = r_rotation(unit->right);
            root = l_rotation(unit);
        }
    }
    
    else {
        if (get_hght(unit->left->left) >= get_hght(unit->left->right))
//            small right rotation
            root = r_rotation(unit);
        else {
//            big right rotation
            unit->left = l_rotation(unit->left);
            root = r_rotation(unit);
        }
    }
      
    return root;
}


TREE* add(TREE* unit, int val) {
    if (val < unit->val) {
        if (unit->left)
            unit->left = add(unit->left, val);
        else
            unit->left = init(val);
    }
    else {
        if (unit->right)
            unit->right = add(unit->right, val);
        else
            unit->right = init(val);
    }
    
    unit = balance(unit);
    return unit;
}


void ordered_print(TREE* unit) {
    if (unit->left)
        ordered_print(unit->left);
    
    printf("%d ", unit->val);
    
    if (unit->right)
        ordered_print(unit->right);
}


void search(int elem, TREE* unit) {
    if (unit->val == elem)
        printf("Element %d found, height: %d\n", elem, unit->height);

    else if (elem < unit->val && unit->left)
        search(elem, unit->left);
    
    else if (elem > unit->val && unit->right)
        search(elem, unit->right);
    
    else
        printf("Element %d not found\n", elem);
    
}


void del(TREE* unit) {
    if (unit->left)
        del(unit->left);
    
    if (unit->right)
        del(unit->right);
    
    free(unit);
}

#endif /* tree_h */

