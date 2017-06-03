#include "stdafx.h"
#include "SetYearCommand.h"


SetYearCommand::SetYearCommand(std::string title, Bill& bill): Command(title), bill(bill)
{
}

void SetYearCommand::Execute() {
	std::string str;
	bool isCorrect = false;
	std::cout << "������� ��������: " << bill.getDate().getYear() << std::endl;
	while (!isCorrect) {
		std::cout << "������� ����� ��� (������ ������ - ������):" << std::endl;
		std::getline(std::cin, str);
		if (str == "") {
			throw std::exception("");
		}
		try {
			bill.getDate().setYear(str);
			isCorrect = true;
		}
		catch (std::exception e) {
			print_message(e.what());
		}
	}
}

SetYearCommand::~SetYearCommand()
{
}
