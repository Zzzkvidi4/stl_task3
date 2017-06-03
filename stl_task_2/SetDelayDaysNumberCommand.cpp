#include "stdafx.h"
#include "SetDelayDaysNumberCommand.h"


SetDelayDaysNumberCommand::SetDelayDaysNumberCommand(std::string title, Bill& bill): Command(title), bill(bill)
{
}

void SetDelayDaysNumberCommand::Execute()
{
	bool isCorrect = false;
	std::string str;
	std::cout << "Текущее значение: " << bill.getDelayNumber() << std::endl;
	while (!isCorrect) {
		std::cout << "Введите новое количество дней задолжности (пустая строка - отмена):" << std::endl;
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
