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

// ## Common C Operation Antonyms
//
// - create <=> destroy - Often used for allocating/freeing resources
// - initialize <=> deinitialize / finalize - usually cleanup of initialized
// state
// - add <=> remove - For lists, arrays, sets, etc.
// - make <=> destroy - For objects, structs, modules
// - start <=> stop - Threads, timers, services
// - enable <=> disable - Features, flags, interrupts
// - open <=> close - Files, sockets, devices
// - lock <=> unlock - Mutexes, semaphores
// - push <=> pop - Stack, queue
// - set <=> unset / clear - Variables, bits, flags
// - show <=> hide - UIs, debugging/log info
// - increment <=> decrement - Counters, indexes
// - attach <=> detach - Processes, threads, signals
// - read <=> write - IO operations (note: not exactly opposites but
// complementary)
// - allocate <=> free - malloc() vs. free()
// - begin <=> end - Ranges, loops, sections
// - front <=> back - Often used with deques/lists
// - input <=> output - Data direction
// - connect <=> disconnect - Sockets, devices, resources
// - mount <=> unmount - Filesystems
// - assert <=> assume / ignore - Often assert() vs. silent handling
// - expand <=> shrink / compress - Buffers, memory regions
// - save <=> load - Persistent state

// NOTE: All data structures should have the following methods; int size(return
// the size), void clear(remove all elements), bool empty(check if empty), void
// print(obvious)
// NOTE: dynamic array and linked list: adding and removing from
// the end of the list should be constant time; accessing the front item should
// be constant time; the common methods they should have are: push_back(add to
// the end), pop_back(remove from the end), back (returns the last item), front
// (returns the first item)
// NOTE: doubly linked list: push_front ( add item to
// the front), pop_front (remvoe from the front)
// NOTE: dynamic array: array[i]
// (no bounds checking), at(i) (with bounds checking), capacity (return internal
// capacity), void reserve (set new capacity)
// TODO: SINGLY LINKED LIST
// TODO: DOUBLY LINKED LIST
// TODO: HASH TABLE
// TODO: DYNAMIC ARRAY
// TODO: STACK
// TODO: HEAP
//
//
//

/******************************************************************************/
/*                                                               STACK - LIFO */
/******************************************************************************/

/******************************************************************************/
/*                                            DYNAMIC ARRAY - RESIZABLE ARRAY */
/******************************************************************************/

// NOTE: constant time,
// push_back(add to the end),
// pop_back(remove from the end),
// back (returns the last item),
// front (returns the first item)

// NOTE: array[i] (no bounds checking),
// at(i) (with bounds checking),
// capacity (return internal capacity),
// void reserve (set new capacity)

struct xdsa_vector {
  int *array;
  size_t size;
  size_t capacity;
};

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

/******************************************************************************/
/*                                               SINGLY LINKED LIST - ONE WAY */
/******************************************************************************/

struct xdsa_node {
  int data;
  struct xdsa_node *previous;
  struct xdsa_node *next;
};

// NOTE: All data structures should have the following methods: int size(), void
// clear(), bool empty(), void print()
// NOTE: linked list: adding and removing from the end of the
// list should be constant time; accessing the front item should be constant
// time; the common methods they should have are: push_back(add to the end),
// pop_back(remove from the end), back (returns the last item), front (returns
// the first item)
// NOTE: doubly linked list: push_front ( add item to the
// front), pop_front (remvoe from the front)

struct xdsa_sll {
  size_t size;
  struct xdsa_node *head;
  struct xdsa_node *tail;
};

extern struct xdsa_vector *xdsa_sll_create(size_t size);
extern struct xdsa_vector *xdsa_sll_destroy(struct xdsa_sll *sll);
extern int xdsa_sll_size(struct xdsa_vector *sll);
extern void xdsa_sll_clear(struct xdsa_vector *sll);
extern bool xdsa_sll_empty(struct xdsa_vector *sll);
extern void xdsa_sll_print(struct xdsa_vector *sll);
extern void xdsa_sll_push_front(struct xdsa_vector *sll, int data);
extern int xdsa_sll_pop_front(struct xdsa_vector *sll);
extern void xdsa_sll_push_back(struct xdsa_vector *sll, int data);
extern int xdsa_sll_pop_back(struct xdsa_vector *sll);
extern int xdsa_sll_front(struct xdsa_vector *sll);
extern int xdsa_sll_back(struct xdsa_vector *sll);

/******************************************************************************/
/*                                               DOUBLY LINKED LIST - TWO WAY */
/******************************************************************************/

// NOTE: All data structures should have the following methods: int size(), void
// clear(), bool empty(), void print()
// NOTE: linked list: adding and removing from the end of the
// list should be constant time; accessing the front item should be constant
// time; the common methods they should have are: push_back(add to the end),
// pop_back(remove from the end), back (returns the last item), front (returns
// the first item)
// NOTE: doubly linked list: push_front ( add item to the
// front), pop_front (remvoe from the front)

struct xdsa_dll {
  size_t size;
  struct xdsa_node *head;
  struct xdsa_node *tail;
};

extern struct xdsa_vector *xdsa_dll_create(size_t size);
extern struct xdsa_vector *xdsa_dll_destroy(struct xdsa_dll *dll);
extern int xdsa_dll_size(struct xdsa_vector *dll);
extern void xdsa_dll_clear(struct xdsa_vector *dll);
extern bool xdsa_dll_empty(struct xdsa_vector *dll);
extern void xdsa_dll_print(struct xdsa_vector *dll);
extern void xdsa_dll_push_front(struct xdsa_vector *dll, int data);
extern int xdsa_dll_pop_front(struct xdsa_vector *dll);
extern void xdsa_dll_push_back(struct xdsa_vector *dll, int data);
extern int xdsa_dll_pop_back(struct xdsa_vector *dll);
extern int xdsa_dll_front(struct xdsa_vector *dll);
extern int xdsa_dll_back(struct xdsa_vector *dll);

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

extern int xdsa_binary_search(const int *array, int length, int target);

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

//  fast inverse square root implementation from Quake III Arena
extern float Q_rsqrt(float number);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // __XDSA_H__
