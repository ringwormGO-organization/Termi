
#include <string>
#include <iostream>

#include "includes/linenoise.hpp"

std::string READ(std::string input) { return input; }

std::string EVAL(std::string input) { return input; }

std::string PRINT(std::string input) { return input; }

std::string rep(std::string input) 
{
    auto ast = READ(input); 
    auto result = EVAL(ast);
    return PRINT(result);
}

int main()
{

    const auto history_path = "history.txt";
    // Load history
    linenoise::LoadHistory(history_path);

    std::string input;

    for (;;) 
    {
        auto quit = linenoise::Readline("Termi> ", input);

        if (quit)
            break;
            
        std::cout << rep(input) << std::endl;
        linenoise::AddHistory(input.c_str());
    }

    // Save history
    linenoise::SaveHistory(history_path);

    return 0;
}
