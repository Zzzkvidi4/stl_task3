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
            throw new std::exception("");
        }
        try {
			if (!checkInt(str)) {
				throw std::invalid_argument("");
			}
            house_number = std::stoi(str);
            if (house_number <= 0) {
                house_number = -1;
                throw new std::exception("����� ���� ������ ���� ������ ����!");
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
}

Bill HouseNumberFunctor::GetValue()
{
    if (house_number == -1) {
        throw new std::invalid_argument("���������� ������� �������� �� ��������������������� ��������!");
    }
    Bill* bill = new Bill();
    bill->setHouseNumber(house_number);
    return *bill;
}


HouseNumberFunctor::~HouseNumberFunctor()
{
}
