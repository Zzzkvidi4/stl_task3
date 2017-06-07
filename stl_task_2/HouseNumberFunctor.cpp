#include "stdafx.h"
#include "HouseNumberFunctor.h"
#include "Bill.h"


HouseNumberFunctor::HouseNumberFunctor()
{
    house_number = -1;
    comparator = Bill::houseNumberComparator;
}

bool HouseNumberFunctor::operator()(Bill bill)
{
    return bill.getHouseNumber() == house_number;
}

void HouseNumberFunctor::Initialize()
{
    bool isCorrect = false;
    std::string str;
    while (!isCorrect) {
        std::cout << "������� ����� ���� (abort - ������):" << std::endl;
        std::getline(std::cin, str);
        if (str == "abort") {
            throw std::exception("");
        }
        try {
			if (!checkInt(str)) {
				throw std::invalid_argument("");
			}
            house_number = std::stoi(str);
            if (house_number <= 0) {
                house_number = -1;
                throw std::exception("����� ���� ������ ���� ������ ����!");
            }
            isCorrect = true;
        }
        catch (std::invalid_argument e) {
            print_message("����� ���� ������ ���� ������!");
        }
        catch (std::exception e) {
            print_message(e.what());
        }
    }
	isInitialized = true;
}

std::string HouseNumberFunctor::GetStringValue() {
	if (!isInitialized) {
		throw std::exception("���������� ������������ �������������������� �������.");
	}
	return std::to_string(house_number);
}

bool HouseNumberFunctor::Initialize(std::string value) {
	try {
		if (!checkInt(value)) {
			throw std::invalid_argument("");
		}
		house_number = std::stoi(value);
		if (house_number <= 0) {
			house_number = -1;
			throw std::exception("����� ���� ������ ���� ������ ����!");
		}
		isInitialized = true;
		return true;
	}
	catch (std::exception e) {
		return false;
	}
}

Bill HouseNumberFunctor::GetValue()
{
    if (house_number == -1) {
        throw std::invalid_argument("���������� ������� �������� �� ��������������������� ��������!");
    }
    Bill* bill = new Bill();
    bill->setHouseNumber(house_number);
    return *bill;
}


HouseNumberFunctor::~HouseNumberFunctor()
{
}
