#include "push_swap.hpp"

void rotate(const shared_ptr<Stack> &stack)
{
    if (stack->elements.size() > 1)
    {
        rotate(stack->elements.begin(), stack->elements.begin() + 1, stack->elements.end());
        stack->operations->push_back("r" + string(1, stack->name));
    }
}

void rev_rotate(const shared_ptr<Stack> &stack)
{
    if (stack->elements.size() > 1)
    {
        rotate(stack->elements.rbegin(), stack->elements.rbegin() + 1, stack->elements.rend());
        stack->operations->push_back("rr" + string(1, stack->name));
    }
}

void push(const shared_ptr<Stack> &s2)
{
    auto s1 = s2->other_stack.lock();
    if (!s1->elements.empty())
    {
        s2->elements.push_front(s1->elements.front());
        s1->elements.pop_front();
        s2->operations->push_back("p" + string(1, s2->name));
    }
}

void swap(const shared_ptr<Stack> &stack)
{
    if (stack->elements.size() > 1)
    {
        iter_swap(stack->elements.begin(), stack->elements.begin() + 1);
        stack->operations->push_back("s" + string(1, stack->name));
    }
}
