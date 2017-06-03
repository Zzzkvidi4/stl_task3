#include "stdafx.h"
#include "CommandList.h"
#include "Command.h"

CommandList::CommandList()
{
}

void CommandList::RegisterCommand(Command* command)
{
    commands.push_back(command);
}

void CommandList::ExecuteCommand(int index)
{
    if ((commands.size() <= index) || (index < 0)) {
        throw new std::out_of_range("Нарушение индексации списка меню.");
    }
	try {
		system("cls");
		commands[index]->Execute();
		system("cls");
	}
	catch (std::exception e) {
		std::string tmp = e.what();
		if (tmp != "") {
			print_message(tmp);
			system("cls");
		}
	}
}

void CommandList::PrintTitles(std::string header)
{
    std::cout << header << std::endl;
    int i = 1;
    for (std::vector<Command*>::iterator iter = commands.begin() + 1; iter != commands.end(); ++iter) {
        std::cout << i++ << ". " << (*iter)->GetTitle() << std::endl;
    }
	std::cout << "0. " << (*commands.begin())->GetTitle() << std::endl;
}

void CommandList::Clear()
{
	for (auto i = 0; i < commands.size(); ++i) {
		delete commands[i];
	}
    commands.clear();
}

size_t CommandList::Size()
{
    return commands.size();
}

CommandList::~CommandList()
{
    Clear();
}
