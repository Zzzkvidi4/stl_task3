#include "stdafx.h"
#include "SetDelayDaysNumberCommand.h"


SetDelayDaysNumberCommand::SetDelayDaysNumberCommand(std::string title, Bill& bill): Command(title), bill(bill)
{
}

void SetDelayDaysNumberCommand::Execute()
{
	bool isCorrect = false;
	std::string str;
	std::cout << "������� ��������: " << bill.getDelayNumber() << std::endl;
	while (!isCorrect) {
		std::cout << "������� ����� ���������� ���� ����������� (������ ������ - ������):" << std::endl;
		std::getline(std::cin, str);
		if (str == "") {
			throw  std::exception("");
		}
		try {
			bill.setDelayNumber(str);
			RuntimeInfo* runtime_info = RuntimeInfo::getInstance();
			runtime_info->synchronizeContainers();
			isCorrect = true;
		}
		catch (std::exception e) {
			print_message(e.what());
		}
	}
}


SetDelayDaysNumberCommand::~SetDelayDaysNumberCommand()
{
}
