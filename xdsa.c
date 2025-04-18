// xdsa.c
#include "xdsa.h"
#include <assert.h>
#include <stdio.h>
#define IMD_MEMORY_DEBUG // turns on the memory debugging system
#include "imd.h"

/******************************************************************************/
/*                                                               STACK - LIFO */
/******************************************************************************/

/******************************************************************************/
/*                                   VECTOR - DYNAMIC ARRAY - RESIZABLE ARRAY */
/******************************************************************************/

struct xdsa_vector *xdsa_vector_create(size_t size) {
    struct xdsa_vector *vector = malloc(sizeof(*vector));
    if (vector == NULL) {
        fprintf(stderr,
                "Failed to allocate %zu bytes in file %s on line %u within "
                "function %s.\n",
                sizeof(*vector), __FILE__, __LINE__, __func__);
        exit(EXIT_FAILURE);
    }
    if (size != 0) {
        vector->capacity = size * 2;
    } else {
        vector->capacity = 1;
    }
    vector->array = malloc(vector->capacity * sizeof(vector->array));
    if (vector->array == NULL) {
        fprintf(stderr,
                "Failed to allocate %zu bytes in file %s on line %u within "
                "function %s.\n",
                sizeof(vector->array), __FILE__, __LINE__, __func__);
        exit(EXIT_FAILURE);
    }
    vector->size = 0;
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
        vector->array = realloc(vector->array,
                                vector->capacity * 2 * sizeof(*vector->array));
        vector->capacity *= 2;
        if (vector->array == NULL) {
            fprintf(stderr,
                    "Failed to allocate %zu bytes in file %s on line %u within "
                    "function %s.\n",
                    sizeof(vector->array), __FILE__, __LINE__, __func__);
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
    if (!xdsa_vector_empty(vector)) {
        return vector->array[vector->size - 1];
    }
    return -1;
}

int xdsa_vector_front(struct xdsa_vector *vector) {
    if (!xdsa_vector_empty(vector)) {
        return vector->array[0];
    }
    return -1;
}

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
        fprintf(stderr,
                "Failed to allocate %zu bytes in file %s on line %u within "
                "function %s.\n",
                sizeof(vector->array), __FILE__, __LINE__, __func__);
        exit(EXIT_FAILURE);
    }
    vector->capacity = capacity;
}

// TODO: move to separate test file and directory
void xdsa_test_vector(void) {

    // Test creation and basic properties
    struct xdsa_vector *v = xdsa_vector_create(5);

    assert(v != NULL);
    assert(v->array != NULL);
    assert(xdsa_vector_size(v) == 0);
    assert(xdsa_vector_capacity(v) == 5 * 2);
    assert(xdsa_vector_empty(v) == true);

    xdsa_vector_destroy(v);

    // Test push and pop operations
    v = xdsa_vector_create(2);

    // Test push_back
    xdsa_vector_push_back(v, 10);
    assert(xdsa_vector_size(v) == 1);
    assert(xdsa_vector_back(v) == 10);
    assert(xdsa_vector_front(v) == 10);

    xdsa_vector_push_back(v, 20);
    assert(xdsa_vector_size(v) == 2);
    assert(xdsa_vector_back(v) == 20);
    assert(xdsa_vector_front(v) == 10);

    // Test pop_back
    assert(xdsa_vector_pop_back(v) == 20);
    assert(xdsa_vector_size(v) == 1);
    assert(xdsa_vector_back(v) == 10);

    xdsa_vector_destroy(v);

    // Test capacity growth
    v = xdsa_vector_create(2);

    assert(v->capacity == 4);

    // Fill to initial capacity
    xdsa_vector_push_back(v, 1);
    xdsa_vector_push_back(v, 2);
    xdsa_vector_push_back(v, 3); // This should trigger resize
    xdsa_vector_push_back(v, 4);
    xdsa_vector_push_back(v, 5); // This should trigger another resize

    assert(v->capacity == 8);
    assert(xdsa_vector_size(v) == 5);

    xdsa_vector_destroy(v);

    // Test at() function
    v = xdsa_vector_create(5);

    xdsa_vector_push_back(v, 10);
    xdsa_vector_push_back(v, 20);
    xdsa_vector_push_back(v, 30);

    assert(xdsa_vector_at(v, 0) == 10);
    assert(xdsa_vector_at(v, 1) == 20);
    assert(xdsa_vector_at(v, 2) == 30);
    assert(xdsa_vector_at(v, -1) == -1);
    assert(xdsa_vector_at(v, 3) == -1);

    xdsa_vector_destroy(v);

    // Test clear function
    v = xdsa_vector_create(5);

    xdsa_vector_push_back(v, 10);
    xdsa_vector_push_back(v, 20);
    xdsa_vector_push_back(v, 30);

    assert(xdsa_vector_size(v) == 3);
    xdsa_vector_clear(v);
    assert(xdsa_vector_size(v) == 0);
    assert(xdsa_vector_empty(v));

    // Verify elements were zeroed out
    for (int i = 0; i < 3; i++) {
        assert(v->array[i] == 0);
    }

    xdsa_vector_destroy(v);

    // Test reserve function
    v = xdsa_vector_create(5);

    assert(v->capacity == 10);

    xdsa_vector_reserve(v, 20);
    assert(v->capacity == 20);
    assert(xdsa_vector_size(v) == 0);

    // Test that we can still add elements
    for (int i = 0; i < 15; i++) {
        xdsa_vector_push_back(v, i);
    }
    assert(xdsa_vector_size(v) == 15);
    assert(v->capacity == 20);

    xdsa_vector_destroy(v);

    // Test edge cases
    v = xdsa_vector_create(0);

    // Test empty vector operations
    assert(xdsa_vector_pop_back(v) == -1);
    assert(xdsa_vector_back(v) == -1);
    assert(xdsa_vector_front(v) == -1);

    // Test push after creation with size 0
    xdsa_vector_push_back(v, 42);
    assert(xdsa_vector_size(v) == 1);
    assert(xdsa_vector_back(v) == 42);

    printf("%s %s %u\n", __FILE__, __func__, __LINE__);
    xdsa_vector_destroy(v);

    // Test destruction
    v = xdsa_vector_create(5);

    xdsa_vector_push_back(v, 1);
    xdsa_vector_push_back(v, 2);
    xdsa_vector_push_back(v, 3);

    xdsa_vector_destroy(v);
    // Can't assert much here, but this should not crash or leak memory
}

/******************************************************************************/
/*                                               SINGLY LINKED LIST - ONE WAY */
/******************************************************************************/

struct xdsa_list_node *xdsa_list_node_create(int data) {
    struct xdsa_list_node *node = malloc(sizeof(*node));
    if (node == NULL) {
        fprintf(stderr,
                "Failed to allocate %zu bytes in file %s on line %u within "
                "function %s.\n",
                sizeof(*node), __FILE__, __LINE__, __func__);
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
        fprintf(stderr,
                "Failed to allocate %zu bytes in file %s on line %u within "
                "function %s.\n",
                sizeof(*sll), __FILE__, __LINE__, __func__);
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
        struct xdsa_list_node *temp = sll->head->next;
        sll->head->data = 0;
        xdsa_list_node_destroy(sll->head);
        sll->head = temp;
    }
    sll->size = 0;
    sll->head = sll->tail = NULL;
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
    if (!sll->tail) {
        sll->tail = sll->head;
    }
    sll->size++;
}

int xdsa_sll_pop_front(struct xdsa_sll *sll) {
    if (!sll->size)
        return -1;
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

int xdsa_sll_front(struct xdsa_sll *sll) {
    if (!sll->size)
        return -1;
    return sll->head->data;
}

int xdsa_sll_back(struct xdsa_sll *sll) {
    if (!sll->size)
        return -1;
    return sll->tail->data;
}

void xdsa_test_sll(void) {
    printf("=== Starting Singly Linked List Tests ===\n");

    // Test 1: Node creation and basic properties
    printf("Test 1: Node operations...\n");
    struct xdsa_list_node *node = xdsa_list_node_create(42);
    assert(node != NULL);
    assert(node->data == 42);
    assert(node->next == NULL);
    assert(node->previous == NULL); // Note: This suggests it's not purely SLL
    xdsa_list_node_destroy(node);

    // Test 2: List creation and basic properties
    printf("Test 2: List creation...\n");
    struct xdsa_sll *list = xdsa_sll_create();
    assert(list != NULL);
    assert(xdsa_sll_size(list) == 0);
    assert(list->head == NULL);
    assert(list->tail == NULL);
    assert(xdsa_sll_empty(list));

    // Test 3: Push front and basic operations
    printf("Test 3: Push front operations...\n");
    xdsa_sll_push_front(list, 10);
    assert(xdsa_sll_size(list) == 1);
    assert(xdsa_sll_front(list) == 10);
    assert(xdsa_sll_back(list) == 10);
    xdsa_sll_push_front(list, 20);
    assert(xdsa_sll_size(list) == 2);
    assert(xdsa_sll_front(list) == 20);
    assert(xdsa_sll_back(list) == 10);

    // Test 4: Pop front operations
    printf("Test 4: Pop front operations...\n");
    assert(xdsa_sll_pop_front(list) == 20);
    assert(xdsa_sll_size(list) == 1);
    assert(xdsa_sll_front(list) == 10);

    // Test 5: Push back operations
    printf("Test 5: Push back operations...\n");
    xdsa_sll_push_back(list, 30);
    assert(xdsa_sll_size(list) == 2);
    assert(xdsa_sll_front(list) == 10);
    assert(xdsa_sll_back(list) == 30);

    xdsa_sll_push_back(list, 40);
    assert(xdsa_sll_size(list) == 3);
    assert(xdsa_sll_back(list) == 40);

    // Test 6: Clear operation
    printf("Test 6: Clear operation...\n");
    xdsa_sll_clear(list);
    assert(xdsa_sll_size(list) == 0);
    assert(xdsa_sll_empty(list));
    assert(list->head == NULL);
    assert(list->tail == NULL);

    // Test 7: Mixed operations
    printf("Test 7: Mixed operations...\n");
    xdsa_sll_push_front(list, 2);
    xdsa_sll_push_back(list, 3);
    xdsa_sll_push_front(list, 1);
    xdsa_sll_push_back(list, 4);
    assert(xdsa_sll_size(list) == 4);
    assert(xdsa_sll_front(list) == 1);
    assert(xdsa_sll_back(list) == 4);

    assert(xdsa_sll_pop_front(list) == 1);
    assert(xdsa_sll_pop_front(list) == 2);
    assert(xdsa_sll_pop_front(list) == 3);
    assert(xdsa_sll_pop_front(list) == 4);
    assert(xdsa_sll_empty(list));

    // Test 8: Edge cases
    printf("Test 8: Edge cases...\n");
    // Note: Original implementation would crash on these - would need error
    assert(xdsa_sll_pop_front(list) == -1); // Would need error
    assert(xdsa_sll_front(list) == -1);     // Would need error
    assert(xdsa_sll_back(list) == -1);      // Would need error

    // Test single element case
    xdsa_sll_push_front(list, 99);
    assert(xdsa_sll_pop_front(list) == 99);
    assert(xdsa_sll_empty(list));
    // Clean up
    xdsa_sll_destroy(list);

    printf("=== All tests passed successfully ===\n");
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

// TODO: add tests for insertion sort
void xdsa_insertion_sort(int *array, size_t length) {
    // start from the first index
    size_t i;
    size_t j;
    for (i = 1; i < length; i++) {
        int key = array[i];
        j = i - 1;
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

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

void xdsa_test_binary_search(void) {
    printf("=== Starting Binary Search Tests ===\n");

    // Test Case 1: Empty array
    printf("Test 1: Empty array...\n");
    {
        int *empty = NULL;
        assert(xdsa_binary_search(empty, 0, 42) == -1);
    }

    // Test Case 2: Single element array (target present)
    printf("Test 2: Single element array (target present)...\n");
    {
        int single[] = {5};
        assert(xdsa_binary_search(single, 1, 5) == 0);
    }

    // Test Case 3: Single element array (target absent)
    printf("Test 3: Single element array (target absent)...\n");
    {
        int single[] = {5};
        assert(xdsa_binary_search(single, 1, 7) == -1);
    }

    // Test Case 4: Small even-sized array
    printf("Test 4: Small even-sized array...\n");
    {
        int small_even[] = {2, 4, 6, 8};
        assert(xdsa_binary_search(small_even, 4, 2) == 0);
        assert(xdsa_binary_search(small_even, 4, 4) == 1);
        assert(xdsa_binary_search(small_even, 4, 6) == 2);
        assert(xdsa_binary_search(small_even, 4, 8) == 3);
        assert(xdsa_binary_search(small_even, 4, 1) == -1);
        assert(xdsa_binary_search(small_even, 4, 5) == -1);
        assert(xdsa_binary_search(small_even, 4, 9) == -1);
    }

    // Test Case 5: Small odd-sized array
    printf("Test 5: Small odd-sized array...\n");
    {
        int small_odd[] = {1, 3, 5, 7, 9};
        assert(xdsa_binary_search(small_odd, 5, 1) == 0);
        assert(xdsa_binary_search(small_odd, 5, 3) == 1);
        assert(xdsa_binary_search(small_odd, 5, 5) == 2);
        assert(xdsa_binary_search(small_odd, 5, 7) == 3);
        assert(xdsa_binary_search(small_odd, 5, 9) == 4);
        assert(xdsa_binary_search(small_odd, 5, 0) == -1);
        assert(xdsa_binary_search(small_odd, 5, 2) == -1);
        assert(xdsa_binary_search(small_odd, 5, 8) == -1);
        assert(xdsa_binary_search(small_odd, 5, 10) == -1);
    }

    // Test Case 6: Large array
    printf("Test 6: Large array...\n");
    {
        int large[1000];
        for (int i = 0; i < 1000; i++) {
            large[i] = i * 2; // Even numbers from 0 to 1998
        }
        assert(xdsa_binary_search(large, 1000, 0) == 0);
        assert(xdsa_binary_search(large, 1000, 1998) == 999);
        assert(xdsa_binary_search(large, 1000, 1000) == 500);
        assert(xdsa_binary_search(large, 1000, 1234) == 617);
        assert(xdsa_binary_search(large, 1000, -1) == -1);
        assert(xdsa_binary_search(large, 1000, 1999) == -1);
        assert(xdsa_binary_search(large, 1000, 2000) == -1);
    }

    // Test Case 7: Duplicate elements (should return any matching index)
    printf("Test 7: Duplicate elements...\n");
    {
        int duplicates[] = {1, 2, 2, 2, 3, 4};
        int result = xdsa_binary_search(duplicates, 6, 2);
        assert(result >= 1 && result <= 3); // Could be any of the three 2's
    }

    // Test Case 8: All identical elements
    printf("Test 8: All identical elements...\n");
    {
        int identical[] = {5, 5, 5, 5, 5};
        int result = xdsa_binary_search(identical, 5, 5);
        assert(result >= 0 && result <= 4); // Could be any index
        assert(xdsa_binary_search(identical, 5, 4) == -1);
    }

    // Test Case 9: Target at beginning/end
    printf("Test 9: Target at beginning/end...\n");
    {
        int medium[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
        assert(xdsa_binary_search(medium, 10, 10) == 0);
        assert(xdsa_binary_search(medium, 10, 100) == 9);
    }

    // Test Case 10: Negative numbers
    printf("Test 10: Negative numbers...\n");
    {
        int negatives[] = {-50, -40, -30, -20, -10, 0, 10, 20, 30, 40, 50};
        assert(xdsa_binary_search(negatives, 11, -50) == 0);
        assert(xdsa_binary_search(negatives, 11, 50) == 10);
        assert(xdsa_binary_search(negatives, 11, -25) == -1);
        assert(xdsa_binary_search(negatives, 11, 25) == -1);
    }

    printf("=== All binary search tests passed successfully ===\n");
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
    int array[7] = {0, 1, 2, 3, 6, 4, 5};
    xdsa_insertion_sort(array, 7);
    size_t i;
    for (i = 0; i < 7; i++) {
        printf("%d\n", array[i]);
    }

    // xdsa_test_vector(); // PASSED
    // xdsa_test_sll();    // PASSED
    // xdsa_test_binary_search(); // PASSED
    imd_debug_memory_init(NULL, NULL, NULL);
    imd_debug_memory_print(0);
    imd_debug_memory_reset();

    return 0;
}
