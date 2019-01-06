/* Run all the test set */
#include "data.h"
#include "api.h"

/* Runs the applications tests */
void runTests();

/* Runs the applications tests corresponding to PR2 */
void runTestsPR2(int* totalTest, int* passedTest);

/* Test stack initialization */
void test_init(int *totalTest, int *passedTest);

/* Test stack push of elements */
void test_push(int *totalTest, int *passedTest);

/* Test stack pop of elements */
void test_pop(int *totalTest, int *passedTest);

/* Test stack top */
void test_top(int *totalTest, int *passedTest);

/* Test stack empty checking */
void test_empty(int *totalTest, int *passedTest);

/* Test stack full checking */
void test_full(int *totalTest, int *passedTest);

/* Test stack inversion */
void test_invert(int *totalTest, int *passedTest);

/* Test the stack data persistence */
void test_stack_persistence(int *totalTest, int *passedTest);

/* Test the warehouse stock checking */
void test_check_stocks(int *totalTest, int *passedTest);

/* Test the search train on platforms */
void test_search_train(int *totalTest, int *passedTest);

/* Test the train loading of goods */
void test_load_train(int *totalTest, int *passedTest);

/* Test the train transportation */
void test_train_transport(int *totalTest, int *passedTest);

/* Test the train unloading of goods */
void test_unload_train(int *totalTest, int *passedTest);
