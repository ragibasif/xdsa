/*
Module Name: xdsa.c

Description:
This is the implementataion C file for xdsa.

Author: Ragib Asif
Date: 2025-04-08
*/

#include "xdsa.h"
#include <stdio.h>

// TODO: redo
/**
 * @brief Searches for an element in a sorted array using binary search.
 *
 * @param arr Pointer to the sorted array.
 * @param size Number of elements in the array.
 * @param target The value to search for.
 * @return Index of the target if found; -1 otherwise.
 */
int binary_search(const int *arr, int size, int target) {
  int left = 0, right = size - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2;

    // Avoid overflow: never use (left + right) / 2
    if (arr[mid] == target)
      return mid;
    else if (arr[mid] < target)
      left = mid + 1;
    else
      right = mid - 1;
  }

  return -1; // Target not found
}

// https://en.wikipedia.org/wiki/Fast_inverse_square_root
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
struct xdsa_sll *xdsa_sll_create_node(int data, struct xdsa_sll *next) {
  struct xdsa_sll *node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "[ERROR] Failed to allocate %zu bytes in (%s %u %s).\n",
            sizeof(*node), __FILE__, __LINE__, __func__);
    exit(EXIT_FAILURE);
  }

  node->data = data;
  node->next = next;
  return node;
}

struct xdsa_sll *xdsa_sll_create_list(int *array, size_t length) {
  if (!array || length == 0) {
    return NULL;
  }

  struct xdsa_sll *head = xdsa_sll_create_node(array[0], NULL);
  struct xdsa_sll *tail = head;

  for (size_t i = 1; i < length; i++) {
    tail->next = xdsa_sll_create_node(array[i], NULL);
    tail = tail->next;
  }

  return head;
}

void xdsa_sll_destroy_node(struct xdsa_sll *node) {
  if (node != NULL) {
    node->data = 0;
    node->next = NULL;
    free(node);
    node = NULL;
  }
}

void xdsa_sll_destroy_list(struct xdsa_sll *node) {
  while (node != NULL) {
    struct xdsa_sll *temp = node->next;
    xdsa_sll_destroy_node(node);
    node = temp;
  }
}

void *xdsa_sll_insert_front(int data, struct xdsa_sll *head) {
  struct xdsa_sll *new_head = xdsa_sll_create_node(data, head);
  return new_head;
}

void xdsa_sll_insert_back(int data, struct xdsa_sll *head) {

  struct xdsa_sll *tail = xdsa_sll_create_node(data, NULL);

  while (head->next != NULL) {
    head = head->next;
  }
  head->next = tail;
}

void xdsa_sll_print(struct xdsa_sll *node) {
  puts("--------------------");
  printf("| Node: %p\n", (void *)node);
  printf("| Data: %d\n", node->data);
  printf("| Next: %p\n", (void *)node->next);
  puts("--------------------");
}

void xdsa_sll_iterative_print(struct xdsa_sll *head) {
  while (head != NULL) {
    xdsa_sll_print(head);
    head = head->next;
  }
}
void xdsa_sll_recursive_print(struct xdsa_sll *head) {
  if (head == NULL) {
    return;
  }

  xdsa_sll_print(head);
  xdsa_sll_recursive_print(head->next);
}

void xdsa_sll_recursive_reversed_print(struct xdsa_sll *head) {
  if (head == NULL) {
    return;
  }
  xdsa_sll_recursive_reversed_print(head->next);
  xdsa_sll_print(head);
}

struct xdsa_sll *xdsa_sll_find_node(struct xdsa_sll *node, int data) {
  while (node != NULL) {
    if (node->data == data)
      return node;
  }
  return NULL;
}
static void test_sll(void) {

  int array[] = {1, 3, 5, 5, 992, 4232, 123, 512, 11, -1342, 10342, -99};

  struct xdsa_sll *head =
      xdsa_sll_create_list(array, sizeof(array) / sizeof(array[0]));

  xdsa_sll_iterative_print(head);
  xdsa_sll_recursive_print(head);
  xdsa_sll_recursive_reversed_print(head);
  xdsa_sll_destroy_list(head);
}

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;
  printf("Hello, world!\n");
  return 0;
}
