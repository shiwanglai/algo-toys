#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Definition for a binary tree node.
 */
struct tree_node {
    int val;
    struct tree_node *left;
    struct tree_node *right;
}; 
int count;
int array[100];
void print_element(struct tree_node *tree)
{
    array[count] = tree->val;
    count++;
}

/*
 * binary tree preorder traversal
 */
void print_tree_preorder(struct tree_node *tree)
{
    if (tree != NULL) {
        print_element(tree);
        print_tree_preorder(tree->left);
        print_tree_preorder(tree->right);
    }
}

/*
 * binary tree inorder traversal
 */
void print_tree_inorder(struct tree_node *tree)
{
    if (tree != NULL) {
        print_tree_inorder(tree->left);
        print_element(tree);
        print_tree_inorder(tree->right);
    }
}

/*
 * binary tree postorder traversal
 */
void print_tree_postorder(struct tree_node *tree)
{
    if (tree != NULL) {
        print_tree_postorder(tree->left);
        print_tree_postorder(tree->right);
        print_element(tree);
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* postorder_traversal(struct tree_node* root, int* return_size)
{
    count = 0;
    
    //print_tree_preorder(root);
    //print_tree_inorder(root);
    print_tree_postorder(root);
    
    int *parray = NULL;
    if (count != 0) {
        parray = (int *)malloc(count * sizeof(int));
        memcpy(parray, array, count * sizeof(int));
    }
    *return_size = count;
    
    return parray;
}

int main()
{
    /*
     * input area
     * Input: root = [1,null,2,3]
     * Output: [3,2,1]
     */
    int return_size;
    int *output_array;
    struct tree_node binary_tree_3 = {
	    .val = 3
    };
    struct tree_node binary_tree_2 = {
	    .val = 2,
	    .left = &binary_tree_3
    };
    struct tree_node binary_tree_root = {
        .val = 1,
        .right = &binary_tree_2
    };

    /* doing */
    output_array = postorder_traversal(&binary_tree_root, &return_size);

    /* output area */
    printf("[");
    for (int i = 0; i < return_size - 1; i++) {
        printf("%d,", output_array[i]);
    }

    if (return_size > 0) {
        printf("%d", output_array[return_size - 1]);

        free(output_array);
        output_array = NULL;
    }
    printf("]\n");

    return 0;
}
