#include "push_swap.hpp"

vector<string> optimize_operations(const vector<string> &operations)
{
    vector<string> optimized_operations;
    for (const auto &op : operations)
    {
        if (!optimized_operations.empty())
        {
            auto &last = optimized_operations.back();
            if ((op == "rra" && last == "rrb") || (op == "rrb" && last == "rra"))
            {
                last = "rrr";
                continue;
            }
        }
        optimized_operations.push_back(op);
    }

    return optimized_operations;
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return 0;

    auto operations = make_shared<vector<string>>();
    auto a = make_shared<Stack>('a');
    auto b = make_shared<Stack>('b');
    a->other_stack = b;
    b->other_stack = a;
    a->operations = operations;
    b->operations = operations;

    try
    {
        if (argc == 2)
            parse_string(argv[1], a);
        else
            parse_args(argc, argv, a);
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    sort(a);

    *operations = optimize_operations(*operations);

    for (const auto &op : *operations)
        cout << op << endl;

    return 0;
}