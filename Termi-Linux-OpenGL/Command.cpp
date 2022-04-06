#include "Access.hpp"

int main()
{
    static Access acc;

    acc.AddLog("hello from oher file");

    return 0;
}