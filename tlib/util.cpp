/**
 * @author Andrej Bartulin
 * PROJECT: tlib = Lesper
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: Main C++ file for utils
 */

#include "util.hpp"

Eval::Eval(std::string expr, std::vector<std::string> parentheses, std::vector<std::string> numbers)
{
    if (containsSomething(expr, parentheses) && containsSpecificOperators(expr, 1) && containsSomething(expr, numbers))
    {
        ret = Parentheses(expr, numbers);
    }

    else if (containsSpecificOperators(expr, 1) && containsSomething(expr, numbers))
    {
        ret = Operators(expr, numbers);
    }

    else if (containsSomething(expr, numbers))
    {
        ret = Numbers(expr, numbers);
    }

    else
    {
        ret = 0;
        error_state = true;
    }
}

Eval::~Eval()
{
    ret = 0;
}

float Eval::Parentheses(std::string expr, std::vector<std::string> numbers)
{
    std::map<std::size_t, std::string> data;
    std::vector<float> num;
    std::size_t temp;
    bool contains_additon_and_subtraction = false;
    bool multiple_or_division = false;
    bool contains_parentheses = false;
    int muls_and_divs = 0;
    int parentheses = 0;
    float number;

    num.push_back(0);
    for (std::size_t i = 0; i < expr.length(); i++)
    {
        if (containsSomething(expr.substr(i, 1), numbers))
        {
            temp = i;
            while (containsSomething(expr.substr(temp, 1), numbers))
            {
                temp++;
            }

            data.insert(
                {temp,
                 expr.substr(temp, temp - i)});
            num.push_back(std::stof(expr.substr(i, temp - i)));
        }
    }
    data.erase(std::prev(data.end()));

    for (auto y : data)
    {
        std::string chr;
        if (y.second.length() != 1)
        {
            chr = y.second.substr(y.second.length() - 1);
            y.second.pop_back();
            data[y.first] = y.second;
            data.insert({y.first + 1, chr});
        }
    }

    std::size_t final_key;
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        final_key = it->first;
    }

    for (auto z : data)
    {
        if (z.first == final_key)
        {
            data.insert({z.first + 1, ")"});
        }
    }

    for (auto x : data)
    {
        if (x.second == "(" || x.second == ")")
        {
            contains_parentheses = true;
            parentheses++;
        }

        if (x.second == "*" || x.second == "/")
        {
            multiple_or_division = true;
            muls_and_divs++;
        }

        if (x.second == "+" || x.second == "-")
        {
            contains_additon_and_subtraction = true;
        }
    }

    for (std::size_t i = 1; i < num.size(); i++)
    {
        if (num[i] > 9)
        {
            std::vector<float>::iterator a = num.begin();
            a += i * 2;
            num.erase(a);
        }
    }
    std::vector<float>::iterator b = num.begin();
    num.erase(b);

    if (!contains_parentheses && !multiple_or_division && contains_additon_and_subtraction)
    {
        std::cout << "here" << std::endl;
        return Numbers(expr, numbers);
    }

    else if (multiple_or_division && !contains_parentheses && !contains_additon_and_subtraction)
    {
        return Operators(expr, numbers);
    }

    else if (multiple_or_division && contains_additon_and_subtraction && !contains_parentheses)
    {
        return Operators(expr, numbers);
    }

    else
    {
        std::vector<int> left, right;
        std::vector<float> numbers_in_parantheses;
        std::string expression;
        float temp_num;
        for (auto pos : data)
        {
            if (pos.second == "(")
            {
                left.push_back(pos.first);
            }

            else if (pos.second == ")")
            {
                right.push_back(pos.first);
            }
        }

        expression = expr.substr(left[0], right[0] - 2);
        std::string::iterator it = expression.begin();
        expression.erase(it);

        number = Operators(expression, numbers);

        if (expr.substr(0, left[0]).length() != 0)
        {
            std::string chr = expr.substr(0, left[0]).substr(expr.substr(0, left[0]).length() - 1);

            expression = expr.substr(0, left[0]) + std::to_string(static_cast<int>(number));
            std::string::iterator it = expression.begin();
            it++;
            expression.erase(it);
            /*
                we can't use only single digits numbers because `data` map crashes, solution is to
                wait multiple-digits numbers
            */
            number = Operators(expression, numbers);
        }
    }

    return number;
}

float Eval::Operators(std::string expr, std::vector<std::string> numbers)
{
    std::map<std::size_t, std::string> data;
    std::vector<float> num;
    std::size_t temp;
    bool contains_additon_and_subtraction = false;
    bool multiple_or_division = false;
    int muls_and_divs = 0;
    float number;

    num.push_back(0);
    for (std::size_t i = 0; i < expr.length(); i++)
    {
        if (containsSomething(expr.substr(i, 1), numbers))
        {
            temp = i;
            while (containsSomething(expr.substr(temp, 1), numbers))
            {
                temp++;
            }

            data.insert(
                {temp,
                 expr.substr(temp, temp - i)});
            num.push_back(std::stof(expr.substr(i, temp - i)));
        }
    }
    data.erase(std::prev(data.end()));

    for (auto x : data)
    {
        if (x.second == "*" || x.second == "/")
        {
            multiple_or_division = true;
            muls_and_divs++;
        }

        if (x.second == "+" || x.second == "-")
        {
            contains_additon_and_subtraction = true;
        }
    }

    for (std::size_t i = 1; i < num.size(); i++)
    {
        if (num[i] > 9)
        {
            std::vector<float>::iterator a = num.begin();
            a += i * 2;
            num.erase(a);
        }
    }
    std::vector<float>::iterator b = num.begin();
    num.erase(b);

    if (!multiple_or_division && contains_additon_and_subtraction)
    {
        number = Numbers(expr, numbers);
    }

    else if (multiple_or_division && !contains_additon_and_subtraction)
    {
        number = num[0];
        for (auto pos : data)
        {
            switch (expr.at(pos.first))
            {
            case '*':
                number *= std::stof(pos.second);
                break;

            case '/':
                number /= std::stof(pos.second);
                break;

            default:
                break;
            }
        }
    }

    else
    {
        int add_sub_pos, mul_div_pos;
        std::size_t one, two, result;
        std::string temp1, temp2;
        for (auto pos : data)
        {
            if (pos.second == "*" || pos.second == "/")
            {
                mul_div_pos = pos.first;
                switch (expr.at(mul_div_pos))
                {
                case '*':
                    temp1 = expr.at(mul_div_pos - 1);
                    temp2 = expr.at(mul_div_pos + 1);
                    number = std::stof(temp1) * std::stof(temp2);
                    break;

                case '/':
                    temp1 = expr.at(mul_div_pos - 1);
                    temp2 = expr.at(mul_div_pos + 1);
                    number = std::stof(temp1) / std::stof(temp2);
                    break;

                default:
                    break;
                }
                muls_and_divs--;
            }

            else
            {
                if (muls_and_divs == 0)
                {
                }
            }
        }

        for (auto pos : data)
        {
            if (muls_and_divs == 0)
            {
                if (pos.second == "+" || pos.second == "-")
                {
                    add_sub_pos = pos.first;
                    switch (expr.at(add_sub_pos))
                    {
                    case '+':
                        temp1 = expr.at(add_sub_pos - 1);
                        number = std::stof(temp1) + number;
                        break;

                    case '-':
                        temp1 = expr.at(add_sub_pos - 1);
                        temp2 = expr.at(add_sub_pos + 1);
                        number = std::stof(temp1) - number;
                        break;

                    default:
                        break;
                    }
                }
            }
        }
    }

    return number;
}

float Eval::Numbers(std::string expr, std::vector<std::string> numbers)
{
    std::vector<std::size_t> pos;
    std::vector<int> num;
    std::size_t temp;

    num.push_back(0);
    pos.push_back(0);
    for (std::size_t i = 0; i < expr.length(); i++)
    {
        if (containsSomething(expr.substr(i, 1), numbers))
        {
            temp = i;
            while (containsSomething(expr.substr(temp, 1), numbers))
            {
                temp++;
            }
            pos.push_back(temp);
            num.push_back(std::stoi(expr.substr(i, temp - i)));
        }
    }

    for (std::size_t i = 1; i < num.size(); i++)
    {
        if (num[i] > 9)
        {
            std::vector<int>::iterator a = num.begin();
            a += i * 2;
            num.erase(a);

            std::vector<std::size_t>::iterator b = pos.begin();
            b += i * 2;
            pos.erase(b);
        }
    }

    std::vector<int>::iterator c = num.begin();
    num.erase(c);
    std::vector<std::size_t>::iterator d = pos.begin();
    pos.erase(d);

    float number = num[0];
    for (std::size_t i = 0; i < pos.size() - 1; i++)
    {
        switch (expr.at(pos[i]))
        {
        case '+':
            number += num[i + 1];
            break;

        case '-':
            number -= num[i + 1];
            break;

        default:
            break;
        }
    }

    return number;
}

std::string lower(std::string str)
{
    std::for_each(str.begin(), str.end(), [](char &c)
                  { c = ::tolower(c); });

    return str;
}

bool containsSomething(std::string str, std::vector<std::string> vec)
{
    for (auto x : vec)
    {
        if (str.find(x) != std::string::npos)
        {
            return true;
        }
    }

    return false;
}

bool containsSpecificOperators(std::string str, int id)
{
    if (id == 0) /* (+, -) */
    {
        if (str.find("+") || str.find("-") && !str.find("*") && !str.find("/"))
        {
            return true;
        }

        else
        {
            return false;
        }
    }

    else if (id == 1) /* (*, /) */
    {
        if (str.find("*") || str.find("/")) /* idk why == now works */
        {
            return true;
        }

        else
        {
            return false;
        }
    }

    else
    {
        throw "Invalid id!";
        return false;
    }
}

bool evaluateTokens(std::vector<std::string> tokens, int i, std::string str, int substr, int option)
{
    /*
     * Option list:
     * 0 - printing tokens
     * 1 - assigning tokens to variables
     */

    std::string temp;

    if (option == 0)
    {
        temp = tokens[i] + " " + tokens[i + 1].substr(0, substr);
    }

    else if (option == 1 && str != "VAR EQUALS EXPR")
    {
        temp = tokens[i].substr(0, substr) + " " + tokens[i + 1] + " " + tokens[i + 2].substr(0, substr);
    }

    else if (option == 1 && str == "VAR EQUALS EXPR")
    {
        temp = tokens[i].substr(0, substr - 1) + " " + tokens[i + 1] + " " + tokens[i + 2].substr(0, substr);
    }

    else
    {
        std::cout << "Invalid option: " << option << "\n\n";
        exit(0);
    }

    if (temp == str)
    {
        return true;
    }

    else
    {
        return false;
    }
}

bool compare(std::string str, std::string str2)
{
    if (str == str2)
    {
        return true;
    }

    else
    {
        return false;
    }
}
