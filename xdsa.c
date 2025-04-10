/*
Module Name: xdsa.c

Description:
This is the implementataion C file for xdsa.

Author: Ragib Asif
Date: 2025-04-08
*/

#include "xdsa.h"
#include <stdio.h>
#define IMD_MEMORY_DEBUG /* turns on the memory debugging system */
// #define IMD_MEMORY_PRINT /* turns on the memory debugging system */
#include "imd.h"

/******************************************************************************/
/*                                                               STACK - LIFO */
/******************************************************************************/

/******************************************************************************/
/*                                            DYNAMIC ARRAY - RESIZABLE ARRAY */
/******************************************************************************/

struct xdsa_vector *xdsa_vector_create(size_t size) {
  struct xdsa_vector *vector = malloc(sizeof(*vector));
  vector->array = malloc(size * 2 * sizeof(vector->array));
  vector->size = size;
  vector->capacity = size * 2;
  return vector;
}

void xdsa_vector_destroy(struct xdsa_vector *vector) {
  vector->size = 0;
  vector->capacity = 0;
  free(vector->array);
  vector->array = NULL;
  free(vector);
  vector = NULL;
}

int xdsa_vector_size(struct xdsa_vector *vector) { return (int)vector->size; }

void xdsa_vector_clear(struct xdsa_vector *vector) {
  size_t i;
  for (i = 0; i < vector->size; i++) {
    vector->array[i] = 0;
  }
  vector->size = 0;
}

bool xdsa_vector_empty(struct xdsa_vector *vector) { return vector->size == 0; }

void xdsa_vector_print(struct xdsa_vector *vector) {
  size_t i;
  for (i = 0; i < vector->size; i++) {
    printf("%d\n", vector->array[i]);
  }
}

void xdsa_vector_push_back(struct xdsa_vector *vector, int data) {
  if (vector->size == vector->capacity) {
    vector->array =
        realloc(vector->array, vector->capacity * 2 * sizeof(*vector->array));
    vector->capacity *= 2;
    if (vector->array == NULL) {
      fprintf(stderr, "[ERROR] Failed to allocate memory\n");
      exit(EXIT_FAILURE);
    }
  }
  vector->array[vector->size++] = data;
}

int xdsa_vector_pop_back(struct xdsa_vector *vector) {
  if (!xdsa_vector_empty(vector)) {
    return vector->array[--vector->size];
  }
  return -1;
}

int xdsa_vector_back(struct xdsa_vector *vector) {
  return vector->array[vector->size - 1];
}

int xdsa_vector_front(struct xdsa_vector *vector) { return vector->array[0]; }

int xdsa_vector_at(struct xdsa_vector *vector, int index) {
  if (index < 0 || index >= (int)vector->size) {
    return -1;
  }
  return vector->array[index];
}

size_t xdsa_vector_capacity(struct xdsa_vector *vector) {
  return vector->capacity;
}

void xdsa_vector_reserve(struct xdsa_vector *vector, size_t capacity) {
  vector->array = realloc(vector->array, capacity * sizeof(*vector->array));
  if (vector->array == NULL) {
    fprintf(stderr, "[ERROR] Failed to allocate memory\n");
    exit(EXIT_FAILURE);
  }
}

/******************************************************************************/
/*                                               SINGLY LINKED LIST - ONE WAY */
/******************************************************************************/

struct xdsa_list_node *xdsa_list_node_create(int data) {
  struct xdsa_list_node *node = malloc(sizeof(*node));

  if (node == NULL) {
    fprintf(stderr, "[ERROR] Failed to allocate memory\n");
    exit(EXIT_FAILURE);
  }
  node->data = data;
  node->previous = NULL;
  node->next = NULL;
  return node;
}

void xdsa_list_node_destroy(struct xdsa_list_node *node) {
  node->data = 0;
  node->previous = NULL;
  node->next = NULL;
  free(node);
  node = NULL;
}

struct xdsa_sll *xdsa_sll_create(void) {
  struct xdsa_sll *sll = malloc(sizeof(*sll));
  if (sll == NULL) {
    fprintf(stderr, "[ERROR] Failed to allocate memory\n");
    exit(EXIT_FAILURE);
  }
  sll->size = 0;
  sll->head = NULL;
  sll->tail = NULL;
  return sll;
}

void xdsa_sll_destroy(struct xdsa_sll *sll) {
  while (sll->head != NULL) {
    struct xdsa_list_node *temp = sll->head->next;
    xdsa_list_node_destroy(sll->head);
    sll->head = temp;
  }
  sll->size = 0;
  free(sll);
  sll = NULL;
}

int xdsa_sll_size(struct xdsa_sll *sll) { return sll->size; }

void xdsa_sll_clear(struct xdsa_sll *sll) {
  while (sll->head != NULL) {
    sll->head->data = 0;
    sll->head = sll->head->next;
  }
  sll->size = 0;
}

bool xdsa_sll_empty(struct xdsa_sll *sll) { return sll->size == 0; }

void xdsa_sll_print(struct xdsa_list_node *head) {
  while (head != NULL) {
    printf("%d\n", head->data);
    head = head->next;
  }
}

void xdsa_sll_push_front(struct xdsa_sll *sll, int data) {
  struct xdsa_list_node *new_head = xdsa_list_node_create(data);
  new_head->next = sll->head;
  sll->head = new_head;
  sll->size++;
}

int xdsa_sll_pop_front(struct xdsa_sll *sll) {
  int data = sll->head->data;
  sll->size--;
  struct xdsa_list_node *temp = sll->head->next;
  xdsa_list_node_destroy(sll->head);
  sll->head = temp;
  return data;
}

void xdsa_sll_push_back(struct xdsa_sll *sll, int data) {
  sll->tail->next = xdsa_list_node_create(data);
  sll->tail = sll->tail->next;
  sll->size++;
}

// TODO: dont use previous since this is a sll
extern int xdsa_sll_pop_back(struct xdsa_sll *sll);

// TODO: test
int xdsa_sll_front(struct xdsa_sll *sll) { return sll->head->data; }

// TODO: test
int xdsa_sll_back(struct xdsa_sll *sll) { return sll->tail->data; }

void test(void) {
  struct xdsa_sll *sll = xdsa_sll_create();
  sll->head = sll->tail = xdsa_list_node_create(200);
  sll->tail->next = xdsa_list_node_create(2323);
  sll->tail = sll->tail->next;
  printf("%lu\n", sll->size);
  printf("%u\n", xdsa_sll_empty(sll));
  xdsa_sll_print(sll->head);
  xdsa_sll_push_front(sll, 4234234);
  xdsa_sll_push_front(sll, 434);
  xdsa_sll_print(sll->head);
  xdsa_sll_pop_front(sll);
  xdsa_sll_pop_front(sll);
  xdsa_sll_pop_front(sll);
  xdsa_sll_print(sll->head);
  xdsa_sll_push_back(sll, 434);
  xdsa_sll_push_back(sll, 434);
  xdsa_sll_push_back(sll, 434);
  xdsa_sll_print(sll->head);
  printf("%lu\n", sll->size);
  xdsa_sll_destroy(sll);
}

/******************************************************************************/
/*                                               DOUBLY LINKED LIST - TWO WAY */
/******************************************************************************/

/******************************************************************************/
/*                                              QUEUE - FIFO / CIRCULAR QUEUE */
/******************************************************************************/

/******************************************************************************/
/*                                                       DEQUE - DOUBLE ENDED */
/******************************************************************************/

/******************************************************************************/
/*                                                              HEAP - BINARY */
/******************************************************************************/

/******************************************************************************/
/*                                                PRIORITY QUEUE - HEAP BASED */
/******************************************************************************/

/******************************************************************************/
/*                                                   BINARY SEARCH TREE - BST */
/******************************************************************************/

/******************************************************************************/
/*                                                  AVL TREE - SELF BALANCING */
/******************************************************************************/

/******************************************************************************/
/*                                                 HASHING - HASH TABLE / MAP */
/******************************************************************************/

/******************************************************************************/
/*                                                         SORTING ALGORITHMS */
/******************************************************************************/

/******************************************************************************/
/*                                                       SEARCHING ALGORITHMS */
/******************************************************************************/

int xdsa_binary_search(const int *array, int length, int target) {
  int left = 0, right = length - 1;

  while (left <= right) {
    int middle = left + (right - left) / 2;
    // Avoid overflow: never use (left + right) / 2

    if (array[middle] == target)
      return middle;
    else if (array[middle] < target)
      left = middle + 1;
    else
      right = middle - 1;
  }

  return -1; // Target not found
}

/******************************************************************************/
/*                                                  GRAPH - ADJ LIST / MATRIX */
/******************************************************************************/

/******************************************************************************/
/*                                                         TRIE - PREFIX TREE */
/******************************************************************************/

/******************************************************************************/
/*                                            UNION FIND - DISJOINT SET UNION */
/******************************************************************************/

/******************************************************************************/
/*                                                   RECURSION & BACKTRACKING */
/******************************************************************************/

/******************************************************************************/
/*                                                   DYNAMIC PROGRAMMING (DP) */
/******************************************************************************/

/******************************************************************************/
/*                                                          GREEDY ALGORITHMS */
/******************************************************************************/

/******************************************************************************/
/*                                                         DIVIDE AND CONQUER */
/******************************************************************************/

/******************************************************************************/
/*                                                           BIT MANIPULATION */
/******************************************************************************/

/******************************************************************************/
/*                                                       MATH & NUMBER THEORY */
/******************************************************************************/

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  test();
  imd_debug_memory_init(NULL, NULL, NULL);
  imd_debug_memory_print(0);
  imd_debug_memory_reset();

  return 0;
}
