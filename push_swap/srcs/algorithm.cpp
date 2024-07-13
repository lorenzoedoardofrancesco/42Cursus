#include "push_swap.hpp"

void push_big_or_small(const shared_ptr<Stack> &s1, const shared_ptr<Stack> &s2, int sign)
{
    auto &e1 = s1->elements;
    auto &e2 = s2->elements;

    auto s2f = e2.front().triangle;
    auto s1b = e1.back().triangle;
    auto s2b = e2.back().triangle;

    auto new_triangle = s2f + s1b + s2b;

    auto compare = [sign](int a, int b)
    { return sign > 0 ? a > b : a < b; };

    while (s2f || s1b || s2b)
    {
        if (s2f && (compare(e2[0].value, e1.back().value) || !s1b) && (compare(e2[0].value, e2.back().value) || !s2b))
        {
            s2->elements.front().triangle = new_triangle;
            push(s1);
            s2f--;
        }
        else if (s2b && (compare(e2.back().value, e1.back().value) || !s1b) && (compare(e2.back().value, e2[0].value) || !s2f))
        {
            s2->elements.back().triangle = new_triangle;
            rev_rotate(s2);
            push(s1);
            s2b--;
        }
        else if (s1b && (e2.empty() || compare(e1.back().value, e2[0].value) || !s2f) && (e2.empty() || compare(e1.back().value, e2.back().value) || !s2b))
        {
            s1->elements.back().triangle = new_triangle;
            rev_rotate(s1);
            s1b--;
        }
    }
    s2->triangle -= 2;
}

void push_one_third(const shared_ptr<Stack> &s1, const shared_ptr<Stack> &s2)
{
    if (!s2->triangle)
        push_one_third(s2, s1);

    while (s1->triangle < s2->triangle / 2)
    {
        int y = s2->elements.front().triangle;
        for (int i = 0; i < y; i++)
            push(s1);
        s1->triangle++, s2->triangle--;
    }
}

void push_bigger(const shared_ptr<Stack> &s1, const shared_ptr<Stack> &s2, int triangle)
{
    if (triangle == 3 && (!s1->triangle || !s2->triangle))
        push_one_third(s1, s2);
    if (triangle > 3)
    {
        push_bigger(s2, s1, triangle / 3);
        push_smaller(s2, s1, triangle / 3);
        push_smaller(s2, s1, triangle / 3);
    }
    else
        push_big_or_small(s1, s2, 1);
}

void push_smaller(const shared_ptr<Stack> &s1, const shared_ptr<Stack> &s2, int triangle)
{
    if (triangle > 3)
    {
        push_bigger(s2, s1, triangle / 3);
        push_bigger(s2, s1, triangle / 3);
        push_smaller(s2, s1, triangle / 3);
    }
    else
        push_big_or_small(s1, s2, -1);
}

void merge(const shared_ptr<Stack> &s1, const shared_ptr<Stack> &s2, int triangle)
{
    if (triangle == 1)
        return;
    push_bigger(s1, s2, triangle);
    merge(s1, s2, triangle / 3);
}

void split_push_to_b(const shared_ptr<Stack> &a, int n, bool type)
{
    auto &e = a->elements;
    auto b = a->other_stack.lock();
    int i = 0;

    indexer(a, n);

    while (i < n)
    {
        if ((type && e[0].index == n - i - 1) || (!type && e[0].index == i))
            push(b), i++;
        else if ((type && upordown(a, n - i - 1, n)) || (!type && upordown(a, i, n)))
            rev_rotate(a);
        else if ((type && e[1].index == n - i - 1) || (!type && e[1].index == i))
            swap(a);
        else
            rotate(a);
    }
}

void split(const shared_ptr<Stack> &a, int n, bool type)
{
    int limit = n / 3;
    if (limit >= a->triangle_size)
    {
        split(a, limit, true);
        if (type)
            split(a, limit + n % 3, false);
        else
            split(a, limit + n % 3, true);
        split(a, limit, false);
    }
    else
    {
        auto b = a->other_stack.lock();
        b->triangle++;
        split_push_to_b(a, n, type);
    }
}