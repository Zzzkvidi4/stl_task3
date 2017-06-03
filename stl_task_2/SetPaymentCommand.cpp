#include "stdafx.h"
#include "SetPaymentCommand.h"


SetPaymentCommand::SetPaymentCommand(std::string title, Bill& bill): Command(title), bill(bill)
{
}

void SetPaymentCommand::Execute()
{
	bool isCorrect = false;
	std::string str;
	std::cout << "������� ��������: " << bill.getPayment() << std::endl;
	while (!isCorrect) {
		std::cout << "������� ����� ����� ������� (������ ������ - ������):" << std::endl;
		std::getline(std::cin, str);
		if (str == "") {
			throw std::exception("");
		}
		try {
			bill.setPayment(str);
			isCorrect = true;
		}
		catch (std::exception e) {
			print_message(e.what());
		}
	}
}


SetPaymentCommand::~SetPaymentCommand()
{
}
