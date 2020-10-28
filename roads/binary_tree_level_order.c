#include <stdio.h>
#include <string.h>

/**
 * Definition for a binary tree node.
 */
struct tree_node {
    int val;
    struct tree_node *left;
    struct tree_node *right;
}; 

/*
 * just include to use the queue
 */
typedef struct tree_node *    queue_elem_t;
#include "queue.c"

int levels_num, nodes_num;
int nodes_num_in_levels[1024];
/* really a big array, any other good way to hold it ? */
int nodes_val_in_levels[1024][2048];

/*
 * Level order to visti the tree, actually it's a BFS
 * Using a queue to help us to do the BFS
 */
void do_level_order(struct tree_node* root)
{
    struct tree_node *node;
    struct queue *q;
    int current_level_in_queue, next_level_in_queue;

    if (root == NULL)
        return;

    /* create a queue */
    q = queue_create(256);

    /* queue the start node */
    queue_push(q, root);
    current_level_in_queue = 1;
    next_level_in_queue = 0;
    /* save the output */
    nodes_num_in_levels[0] = 1;    /* level 0, nodes number 1 */
    nodes_val_in_levels[0][0] = root->val;

    levels_num = 1;
    nodes_num = 0;
    while (!queue_empty(q)) {
        node = queue_front(q);
        queue_pop(q);
        current_level_in_queue--;

        /* get the adjacent node, left */
        if (node->left != NULL) {
            queue_push(q, node->left);

            next_level_in_queue++;
           /* save the output */
            nodes_val_in_levels[levels_num][nodes_num] = node->left->val;
            nodes_num++;
        }

        /* get the adjacent node, right */
        if (node->right != NULL) {
            queue_push(q, node->right);

            next_level_in_queue++;
           /* save the output */
            nodes_val_in_levels[levels_num][nodes_num] = node->right->val;
            nodes_num++;
        }

        if (current_level_in_queue == 0) {
            /* current level end */
            current_level_in_queue = next_level_in_queue;
            next_level_in_queue = 0;

           /* save the output */
            nodes_num_in_levels[levels_num] = nodes_num;
            levels_num++;
            nodes_num = 0;
        }
    }

    queue_destroy(q);

}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrder(struct tree_node* root, int* returnSize, int** returnColumnSizes){
    int **ret;
    int *sub;

    levels_num = 1;
    nodes_num = 0;

    do_level_order(root);

    levels_num--;
    *returnSize = levels_num;
    if (levels_num > 0) {
        *returnColumnSizes = (int *)malloc(levels_num * sizeof(int));
        memcpy(*returnColumnSizes, nodes_num_in_levels, levels_num * sizeof(int));

        ret = (int **)malloc(levels_num * sizeof(int *));
        for (int i = 0; i < levels_num; i++) {
            sub = (int *)malloc(nodes_num_in_levels[i] * sizeof(int));
            memcpy(sub, nodes_val_in_levels[i], nodes_num_in_levels[i] * sizeof(int));

            ret[i] = sub;
        }
    }

    return ret;
}


int main()
{
    int return_size;
    int **output_array;
    int *return_column_sizes;

    /*
     * input area
     * Input: root = [3,9,20,null,null,15,7]
     *  3
     *  |   |
     *  9   20
     *      |   |
     *      15  7
     * Output:
     * 	[
     * 		[3],
     * 		[9,20],
     * 		[15,7]
     * 	]
     */
    struct tree_node binary_tree_15 = {
	    .val = 15
    };
    struct tree_node binary_tree_7 = {
	    .val = 7
    };
    struct tree_node binary_tree_9 = {
	    .val = 9
    };
    struct tree_node binary_tree_20 = {
	    .val = 20,
	    .left  = &binary_tree_15,
	    .right = &binary_tree_7
    };
    struct tree_node binary_tree_root = {
        .val = 3,
        .left  = &binary_tree_9,
        .right = &binary_tree_20
    };

    /* doing */
    output_array = levelOrder(&binary_tree_root, &return_size, &return_column_sizes);

    /* output area */
    printf("[\n");
    for (int i = 0; i < return_size; i++) {
        printf("\t[");
        for (int j = 0; j < return_column_sizes[i]; j++) {
            printf("%d,", output_array[i][j]);
        }
        free(output_array[i]);
        output_array[i] = NULL;
        printf("]\n");
    }

    if (return_size > 0) {
        free(return_column_sizes);
        return_column_sizes = NULL;
        free(output_array);
        output_array = NULL;
    }
    printf("]\n");

    return 0;
}
