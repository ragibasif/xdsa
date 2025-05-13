// xdsa.h

#ifndef __XDSA_H__
#define __XDSA_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// TODO: Add benchmarkings
// TODO: Add documentation and examples

#include <assert.h> //assert
#include <ctype.h>  //size_t
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h> //true, false, bool
#include <stdio.h> //Includes the standard I/O library for functions like `printf`.
#include <stdlib.h> //Includes the standard library for functions like `malloc`, `free`, and `realloc`.
#include <string.h> //Includes the string manipulation library for functions like `memcpy`.
#include <time.h> //time

// FIX: REFACTOR
extern struct xdsa_vector *xdsa_vector_create(size_t size);
extern void xdsa_vector_destroy(struct xdsa_vector *vector);
extern int xdsa_vector_size(struct xdsa_vector *vector);
extern void xdsa_vector_clear(struct xdsa_vector *vector);
extern bool xdsa_vector_empty(struct xdsa_vector *vector);
extern void xdsa_vector_print(struct xdsa_vector *vector);
extern void xdsa_vector_push_back(struct xdsa_vector *vector, int data);
extern int xdsa_vector_pop_back(struct xdsa_vector *vector);
extern int xdsa_vector_back(struct xdsa_vector *vector);
extern int xdsa_vector_front(struct xdsa_vector *vector);
extern int xdsa_vector_at(struct xdsa_vector *vector, int index);
extern size_t xdsa_vector_capacity(struct xdsa_vector *vector);
extern void xdsa_vector_reserve(struct xdsa_vector *vector, size_t capacity);

// FIX: REFACTOR
extern struct xdsa_list_node *xdsa_list_node_create(int data);
extern void xdsa_list_node_destroy(struct xdsa_list_node *node);

// FIX: REFACTOR
extern struct xdsa_linked_list *xdsa_sll_create(void);
extern void xdsa_sll_destroy(struct xdsa_linked_list *sll);
extern int xdsa_sll_size(struct xdsa_linked_list *sll);
extern void xdsa_sll_clear(struct xdsa_linked_list *sll);
extern bool xdsa_sll_empty(struct xdsa_linked_list *sll);
extern void xdsa_sll_print(struct xdsa_list_node *head);
extern void xdsa_sll_push_front(struct xdsa_linked_list *sll, int data);
extern int xdsa_sll_pop_front(struct xdsa_linked_list *sll);
extern void xdsa_sll_push_back(struct xdsa_linked_list *sll, int data);
extern int xdsa_sll_front(struct xdsa_linked_list *sll);
extern int xdsa_sll_back(struct xdsa_linked_list *sll);

// FIX: REFACTOR
extern void xdsa_insertion_sort(int *array, size_t length);

// FIX: REFACTOR
extern int xdsa_binary_search(const int *array, int length, int target);

// FIX: REFACTOR
extern unsigned long long int
xdsa_top_down_fibonacci(unsigned long long int number);

// FIX: REFACTOR
extern unsigned long long int
xdsa_bottom_up_fibonacci(unsigned long long int number);

// FIX: REFACTOR
extern void xdsa_integer_to_binary(signed long long int number, size_t size);

// FIX: REFACTOR
extern int xdsa_mod(long long int a, long long int b);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // __XDSA_H__
