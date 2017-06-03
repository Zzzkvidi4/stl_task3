#pragma once
#include "Command.h"
#include "TemplateContainer.h"
#include "ContainerUtils.h"

template<typename T>
class PrintCommand: public Command
{
private:
    TemplateContainer<T>* cont;
public:

    PrintCommand(std::string title, TemplateContainer<T>* cont): Command(title)
    {
        this->cont = cont;
    }

    void Execute() {
        if (cont->size() == 0) {
            print_message("Список счетов пуст!");
        } else {
			ContainerUtils<Bill>::print_to_console(std::cout, *cont);
			std::cout << "Для продолжения нажмите Enter..." << std::endl;
			std::string str;
			std::getline(std::cin, str);
        }
    }

    ~PrintCommand()
    {
    }
};

