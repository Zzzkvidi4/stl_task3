#include "stdafx.h"
#include "ApartmentNumberFunctor.h"


ApartmentNumberFunctor::ApartmentNumberFunctor()
{
    apartment_number = -1;
    comparator = Bill::appartmentNumberComparator;
}

bool ApartmentNumberFunctor::operator()(Bill bill)
{
    return bill.getApartmentNumber() == apartment_number;
}

void ApartmentNumberFunctor::Initialize()
{
    bool isCorrect = false;
    std::string str;
    while (!isCorrect) {
        std::cout << "������� ����� �������� (0 - ��� ������ ��������) (abort - ������):" << std::endl;
        std::getline(std::cin, str);
        if (str == "abort") {
            throw new std::exception("");
        }
        try {
			if (!checkInt(str)) {
				throw std::invalid_argument("");
			}
            apartment_number = std::stoi(str);
            if (apartment_number < 0) {
                apartment_number = -1;
                throw new std::exception("����� ���� ������ ���� ������ ���� ��� ����� ���!");
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

Bill ApartmentNumberFunctor::GetValue()
{
    if (apartment_number == -1) {
        throw new std::invalid_argument("���������� ������� �������� �� ��������������������� ��������!");
    }
    Bill* bill = new Bill();
    bill->setApartmentNumber(apartment_number);
    return *bill;
}


ApartmentNumberFunctor::~ApartmentNumberFunctor()
{
}
