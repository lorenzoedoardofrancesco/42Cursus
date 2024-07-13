#include "push_swap.hpp"

vector<string> split(const string &str)
{
    vector<string> tokens;
    string token;
    istringstream iss(str);

    while (iss >> token)
        tokens.push_back(token);

    return tokens;
}

bool is_valid_num(const string &str)
{
    regex integer_regex(R"(^[-+]?\d+$)");
    return regex_match(str, integer_regex);
}

bool check_duplicates(const vector<int> &numbers)
{
    return numbers.size() == unordered_set<int>(numbers.begin(), numbers.end()).size();
}

void stack_fill(const shared_ptr<Stack> &a, const vector<int> &numbers)
{
    for (const auto &num : numbers)
        a->elements.push_back(Element(num));

    auto size = a->elements.size();

    long unsigned int divisor = 3;

    while (size > divisor * 9 * 2)
        divisor *= 9;

    a->triangle_size = size / divisor;
}

bool parse_args(int argc, char **argv, const shared_ptr<Stack> &a)
{
    vector<int> numbers;
    for (int i = 1; i < argc; i++)
    {
        if (!is_valid_num(argv[i]))
            throw invalid_argument("Invalid number: " + string(argv[i]));
        try
        {
            numbers.push_back(stoi(argv[i]));
        }
        catch (const out_of_range &e)
        {
            throw out_of_range("Number out of range: " + string(argv[i]));
        }
    }
    if (!check_duplicates(numbers))
        throw invalid_argument("Duplicate numbers found");

    stack_fill(a, numbers);
    return true;
}

bool parse_string(const string &str, const shared_ptr<Stack> &a)
{
    auto tokens = split(str);
    vector<const char *> cstr_tokens;
    cstr_tokens.push_back("");
    for (const auto &token : tokens)
        cstr_tokens.push_back(token.c_str());

    return parse_args(cstr_tokens.size(), const_cast<char **>(cstr_tokens.data()), a);
}