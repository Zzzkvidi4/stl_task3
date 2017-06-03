#pragma once
#include "Command.h"
#include "TemplateContainer.h"
#include "ContainerUtils.h"

template<typename T>
class ReadFromFileCommand: public Command
{
private:
    TemplateContainer<T>* cont;
public:
    ReadFromFileCommand(std::string title, TemplateContainer<T>* cont) : Command(title) {
        this->cont = cont;
    }

    void Execute() {
		RuntimeInfo* runtime_info = RuntimeInfo::getInstance();
        std::cout << "������� ��� ����� (������ ������ ��� ������):" << std::endl;
        std::string file_name;
        std::getline(std::cin, file_name);
        if (file_name != "") {
            cont->clear();
			runtime_info->setFileName(file_name);
            try {
				std::ifstream fin(file_name);
                if (!ContainerUtils<Bill>::read_from_file(fin, *cont)) {
                    print_message("��������, ���������� ����� ����� ���� �������� �����������!");
                }
            }
            catch (std::exception e) {
				if (cont->size() == 0) {
					print_message("������ �� ������� ���������. ��������, ���� ���� ��� ���������.");
				} else {
					print_message("���� ��������� ��������. ���������� ����� �� ���� ��������.");
				}
            }
        }
    }

    ~ReadFromFileCommand() {
    }
};

