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
  putchar('[');
  for (i = 0; i < vector->size - 1; i++) {
    printf("%d, ", vector->array[i]);
  }
  printf("%d]\n", vector->array[i]);
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

static void test_vector(void) {
  size_t n = 20;
  struct xdsa_vector *v = xdsa_vector_create(n);
  size_t i;
  for (i = 0; i < n; i++) {
    v->array[i] = (int)i + 1;
  }
  int a;
  xdsa_vector_print(v);
  a = xdsa_vector_pop_back(v);
  printf("%d\n", a);
  a = xdsa_vector_pop_back(v);
  printf("%d\n", a);
  a = xdsa_vector_pop_back(v);
  printf("%d\n", a);
  xdsa_vector_push_back(v, a);
  xdsa_vector_push_back(v, a);
  xdsa_vector_print(v);
  putchar('\n');

  xdsa_vector_destroy(v);
}

/******************************************************************************/
/*                                               SINGLY LINKED LIST - ONE WAY */
/******************************************************************************/

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

// Copy and pasted from: https://en.wikipedia.org/wiki/Fast_inverse_square_root
// TODO: create my own version
float Q_rsqrt(float number) {
  long i;
  float x2, y;
  const float threehalfs = 1.5F;

  x2 = number * 0.5F;
  y = number;
  i = *(long *)&y;           // evil floating point bit level hacking
  i = 0x5f3759df - (i >> 1); // what the fuck?
  y = *(float *)&i;
  y = y * (threehalfs - (x2 * y * y)); // 1st iteration
  //	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can
  // be removed

  return y;
}

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  test_vector();

  imd_debug_memory_init(NULL, NULL, NULL);
  imd_debug_memory_print(0);
  imd_debug_memory_reset();

  return 0;
}
