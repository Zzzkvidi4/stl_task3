#include "stdafx.h"
#include "SetBlockNumberCommand.h"


SetBlockNumberCommand::SetBlockNumberCommand(std::string title, Bill & bill): Command(title), bill(bill)
{
}

void SetBlockNumberCommand::Execute()
{
	std::string str;
	bool isCorrect = false;
	std::cout << "������� ��������: " << bill.getBlockNumber() << std::endl;
	std::cout << "������� ����� ����� �������� (������ ������ - ������, 0 - ��� ������ ��������):" << std::endl;
	while (!isCorrect) {
		std::getline(std::cin, str);
		if (str == "") {
			throw  std::exception("");
		}
		try {
			if (str != "0") {
				bill.setBlockNumber(str);
			} else {
				bill.setBlockNumber("");
			}
			isCorrect = true;
		}
		catch (std::exception e) {
			print_message(e.what());
		}
	}
}

SetBlockNumberCommand::~SetBlockNumberCommand()
{
}
