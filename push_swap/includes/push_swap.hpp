#include <algorithm>
#include <deque>
#include <exception>
#include <unordered_set>
#include <iostream>
#include <memory>
#include <regex>
#include <stdexcept>

using namespace std;

struct Element
{
    int value;
    int index;
    int triangle;

    Element(int val) : value(val), index(-1), triangle(0) {}
};

struct Stack
{
    char name;
    int triangle;
    int triangle_size;
    deque<Element> elements;
    weak_ptr<Stack> other_stack;
    shared_ptr<vector<string>> operations;

    Stack(char stack_name) : name(stack_name), triangle(0), triangle_size(0) {}
};

// algorithm.cpp
void split(const shared_ptr<Stack> &a, int n, bool type);
void merge(const shared_ptr<Stack> &s1, const shared_ptr<Stack> &s2, int triangle);
void push_smaller(const shared_ptr<Stack> &s1, const shared_ptr<Stack> &s2, int triangle);

// operations.cpp
void push(const shared_ptr<Stack> &s2);
void swap(const shared_ptr<Stack> &stack);
void rotate(const shared_ptr<Stack> &stack);
void rev_rotate(const shared_ptr<Stack> &stack);

// parsing.cpp
bool parse_args(int argc, char **argv, const shared_ptr<Stack> &a);
bool parse_string(const string &str, const shared_ptr<Stack> &a);

// sort.cpp
void sort(const shared_ptr<Stack> &a);
void indexer(const shared_ptr<Stack> &stack, int triangle_num);
bool upordown(const shared_ptr<Stack> &stack, int index, int max);