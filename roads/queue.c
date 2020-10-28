#include <stdlib.h>

/*
 * struct queue
 *
 * typedef could be used to define queue_elem_t
 * for example in binary_tree_level_order.c
 *     typedef struct tree_node *    queue_elem_t;
 */

struct queue {
    int front;
    int rear;
    int size;
    int capacity;

    /* data */
    queue_elem_t *elems;
};

/*
 * queue functions
 * all the function names are refered to C++
 * and using the array to hold the data, not linked list
 */
struct queue *queue_create(int capacity)
{
    struct queue *q = (struct queue *)malloc(sizeof(struct queue));
    q->front = 0;
    q->rear = 0;
    q->capacity = capacity;

    q->elems = (queue_elem_t *)malloc(capacity * sizeof(queue_elem_t));

    return q;
}

void queue_push(struct queue *q, queue_elem_t elem)
{
    q->elems[q->rear] = elem;
    q->rear = (q->rear + 1) % q->capacity;
}

void queue_pop(struct queue *q)
{
    q->front = (q->front + 1) % q->capacity;
}

queue_elem_t queue_front(struct queue *q)
{
    return q->elems[q->front];
}

queue_elem_t queue_back(struct queue *q)
{
    return q->elems[q->rear - 1];
}

int queue_empty(struct queue *q)
{
    return q->front == q->rear;
}

int queue_full(struct queue *q)
{
    return q->front == (q->rear + 1) % q->capacity;
}

int queue_size(struct queue *q)
{
    return (q->rear - q->front + q->capacity) % q->capacity;
}

void queue_destroy(struct queue *q)
{
    free(q->elems);
    free(q);
}


