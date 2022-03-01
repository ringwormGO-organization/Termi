#include "Check.hpp"

using namespace std;

int check(std::string command)
{
	if (command == "help")
	{
		system("..\\..\\Programs\\bin\\help.exe");
		return 0;
	}

	else if(command == "open-calc")
	{
		system("..\\..\\Programs\\bin\\calculator.exe");
		return 0;
	}

	else if (command == "geocalc")
	{
		system("..\\..\\Programs\\bin\\GeoCalculator.exe");
		return 0;
	}

	else if (command == "clear" || command == "cls")
	{
		cout << "\033c";
	}

	else if (command == "exit")
	{
		exit(0);
	}

	else if(command.length() == 0)
	{
		return 0;
	}

	else
	{
		cout << "Command inavlid!!\n";
		return 0;
	}

	return 0;
}