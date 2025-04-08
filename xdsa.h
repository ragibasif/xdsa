#ifndef __XDSA_H__
#define __XDSA_H__

/*
Module Name: xdsa.h

Description:
This is a C header file for xdsa.

Author: Ragib Asif
Date: 2025-04-08
*/

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <ctype.h> /* size_t*/
#include <stdarg.h>
#include <stdbool.h> /* true, false, bool */
#include <stdio.h> /*Includes the standard I/O library for functions like `printf`.*/
#include <stdlib.h> /*Includes the standard library for functions like `malloc`, `free`, and `realloc`.*/
#include <string.h> /*Includes the string manipulation library for functions like `memcpy`.*/
#include <time.h> /*time*/

// TODO: refactor macros
#define XDSA_PI 3.14159265359
#define XDSA_ABS(val) ((val) < 0) ? -(val) : (val)
#define XDSA_BIT_CHK(bit, reg) ((reg >> (bit)) & 1)
#define XDSA_BIT_CLR(value, bit) ((value) &= ~(1L << (bit)))
#define XDSA_BIT_LSB(reg) ((reg) & 1)
#define XDSA_BIT_SET(value, bit) ((value) |= (1L << (bit)))
#define XDSA_CIRCUMFERENCE(radius)                                             \
  (XDSA_PI * radius * radius) // circle circumference
#define XDSA_IN_RANGE(x, lo, hi)                                               \
  (((x > lo) && (x < hi)) || (x == lo) || (x == hi))
#define XDSA_OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE)0)->ELEMENT))
#define XDSA_PERCENT(val, per) ((val)\* (per) / 100.0)
#define XDSA_RAND_INT(min, max) ((rand() % (int)(((max) + 1) - (min))) + (min))
#define XDSA_SIZE(x) (sizeof(x) / sizeof(x[0]))
#define XDSA_SUM(a, b) (a + b)
#define XDSA_SWAP(Type, x, y)                                                  \
  do {                                                                         \
    Type *a = &(x);                                                            \
    Type *b = &(y);                                                            \
    Type t = *a;                                                               \
    *a = *b;                                                                   \
    *b = t;                                                                    \
  }

// DOUBLY LINKED LIST
// HASH TABLE
// DYNAMIC ARRAY
// STACK
// HEAP

// SINGLY LINKED LIST
// TODO: Needs more testing
struct xdsa_sll {
  int data;
  struct xdsa_sll *next;
};
extern struct xdsa_sll *xdsa_sll_create_node(int data, struct xdsa_sll *next);
extern void xdsa_sll_destroy_node(struct xdsa_sll *node);
extern struct xdsa_sll *xdsa_sll_create_list(int *array, size_t length);
extern void xdsa_sll_destroy_list(struct xdsa_sll *list);
extern void *xdsa_sll_insert_front(int data, struct xdsa_sll *list);
extern void xdsa_sll_insert_back(int data, struct xdsa_sll *list);
extern void xdsa_sll_print(struct xdsa_sll *list);
extern void xdsa_sll_iterative_print(struct xdsa_sll *list);
extern void xdsa_sll_recursive_print(struct xdsa_sll *list);
extern void xdsa_sll_recursive_reversed_print(struct xdsa_sll *list);
extern struct xdsa_sll *xdsa_sll_find_node(struct xdsa_sll *node, int data);

// MATH
float Q_rsqrt(float number);

int main(int argc, char **argv);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // __XDSA_H__
