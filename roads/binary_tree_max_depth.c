#include <stdio.h>

/**
 * Definition for a binary tree node.
 */
struct tree_node {
    int val;
    struct tree_node *left;
    struct tree_node *right;
}; 

#define max(a, b)       ((a) > (b) ? (a) : (b))
int answer;

/*
 * Solve Tree Problems Recursively
 * "Top-down" Solution
 *
 * When you meet a tree problem, ask yourself two questions:
 * Can you determine some parameters to help the node know its answer?
 * Can you use these parameters and the value of the node itself to determine
 *     what should be the parameters passed to its children?
 * If the answers are both yes, try to solve this problem using a "top-down" recursive solution.
 */
void max_depth_top_down(struct tree_node *root, int depth)
{
    if (root == NULL) {
        return;
    }

    if (root->left == NULL && root->right == NULL) {
        /* leaf node */
        answer = max(depth, answer);
    }

    max_depth_top_down(root->left, depth + 1);
    max_depth_top_down(root->right, depth + 1);
}

/*
 * Solve Tree Problems Recursively
 * "Bottom-up" Solution
 *
 * For a node in a tree, if you know the answer of its children,
 *     can you calculate the answer of that node?
 * If the answer is yes,
 *     solving the problem recursively using a bottom up approach might be a good idea.
 */
int max_depth_bottom_up(struct tree_node *root)
{
    if (root == NULL) {
        return 0;
    }

    int left_depth = max_depth_bottom_up(root->left);
    int right_depth = max_depth_bottom_up(root->right);

    return max(left_depth, right_depth) + 1;
}

/*
 * test entry
 */
int maxDepth(struct tree_node* root)
{
    answer = 0;

    max_depth_top_down(root, 1);
    //answer = max_depth_bottom_up(root);

    return answer;
}

/*
 * main test
 */
int main()
{
    int max_depth;

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
    max_depth = maxDepth(&binary_tree_root);

    /* output area */
    printf("%d\n", max_depth);

    return 0;
}

