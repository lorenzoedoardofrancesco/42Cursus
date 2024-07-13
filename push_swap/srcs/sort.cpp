#include "push_swap.hpp"

void indexer(const shared_ptr<Stack> &stack, int triangle_num)
{
    vector<int> values;
    for (int i = 0; i < triangle_num; i++)
        values.push_back(stack->elements[i].value);
    sort(values.begin(), values.end());

    for (int i = 0; i < triangle_num; i++)
    {
        auto &e = stack->elements[i];
        e.index = distance(values.begin(), find(values.begin(), values.end(), e.value));
        e.triangle = triangle_num;
    }
}

bool upordown(const shared_ptr<Stack> &stack, int index, int max)
{
    auto &e = stack->elements;
    auto it = find_if(e.begin(), e.end(), [index](const Element &elem)
                      { return elem.index == index; });

    auto dist = distance(e.begin(), it);
    return dist > max;
}

bool is_sort(const shared_ptr<Stack> &a)
{
    return is_sorted(a->elements.begin(), a->elements.end(), [](const Element &a, const Element &b)
                     { return a.value < b.value; });
}

void push_smallest(const shared_ptr<Stack> &a)
{
    auto &e = a->elements;
    auto b = a->other_stack.lock();
    int i = 0;

    indexer(a, e.size());

    while (e.size() != 3)
    {
        if (e[0].index == i && ++i)
            push(b);
        else if (upordown(a, i, 3))
            rev_rotate(a);
        else if (e[1].index == i)
            swap(a);
        else
            rotate(a);
    }
}

void sort_5_or_less(const shared_ptr<Stack> &a)
{
    auto &e = a->elements;

    if (e.size() == 2)
        return swap(a);

    if (e.size() >= 4)
        push_smallest(a);

    if (e[0].value > e[1].value && e[0].value > e[2].value)
        rotate(a);
    if (e[1].value > e[0].value && e[1].value > e[2].value)
        rev_rotate(a);
    if (!is_sort(a))
        swap(a);

    auto b = a->other_stack.lock();
    while (!b->elements.empty())
        push(a);
}

void sort(const shared_ptr<Stack> &a)
{
    if (is_sort(a))
        return;
    else if (a->elements.size() <= 5)
        sort_5_or_less(a);
    else
    {
        split(a, a->elements.size(), true);
        auto b = a->other_stack.lock();
        merge(a, b, b->triangle);
    }
    return;
}