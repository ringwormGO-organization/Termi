/**
 * @author Andrej Bartulin
 * PROJECT: tlib = Lesper
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: Just runs tlib
 */

#include "tlib.hpp"

class InteractiveEnviroment
{
    public:
        InteractiveEnviroment();
        ~InteractiveEnviroment();

        bool exitTime;

    private:
        const std::string filename = "tmp.lesper";

        std::string path, line;
        std::vector<std::string> history;
        void line_input();
        void execute();
};

InteractiveEnviroment::InteractiveEnviroment()
{
    while (!exitTime)
    {
        line_input();
    }
}

InteractiveEnviroment::~InteractiveEnviroment()
{
    path = "";
    line = "";
    history.clear();
    remove(filename.c_str());
}

void InteractiveEnviroment::line_input()
{
    std::cout << "> ";
    std::getline(std::cin, line);

    if (line == "exit")
    {
        exitTime = true;
        return;
    }

    execute();
}

void InteractiveEnviroment::execute()
{
    history.push_back(line);

    std::ofstream file;
    file.open(filename);

    for (int i = 0; i < history.size(); ++i)
    {
        file << history[i] << '\n';
    }

    file.close();

    try
    {
        run(filename);
    }

    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        remove(filename.c_str());
    }

    remove(filename.c_str());
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Entering interactive mode, file path not specified!\n\n";
        InteractiveEnviroment enviroment = InteractiveEnviroment();
        if (enviroment.exitTime)
        {
            return 0;
        }
    }

    std::string path = argv[1];
    run(path);

    return 0;
}
