#include "stdafx.h"
#include "SetHouseNumberCommand.h"


SetHouseNumberCommand::SetHouseNumberCommand(std::string title, Bill& bill): Command(title), bill(bill)
{
}

void SetHouseNumberCommand::Execute()
{
	std::string str;
	bool isCorrect = false;
	std::cout << "������� ��������: " << bill.getHouseNumber() << std::endl;
	std::cout << "������� ����� ����� ���� (������ ������ - ������):" << std::endl;
	while (!isCorrect) {
		std::getline(std::cin, str);
		if (str == "") {
			throw  std::exception("");
		}
		try {
			bill.setHouseNumber(str);
			isCorrect = true;
		}
		catch (std::exception e) {
			print_message(e.what());
		}
	}
}


SetHouseNumberCommand::~SetHouseNumberCommand()
{
}
