#include "stdafx.h"
#include "SurnameFunctor.h"


SurnameFunctor::SurnameFunctor()
{
    comparator = Bill::surnameComparator;
}

bool SurnameFunctor::operator()(Bill bill)
{
	if (!isInitialized) {
		throw std::exception("���������� ������������ �������������������� �������.");
	}
    return bill.getSurname() == surname;
}

void SurnameFunctor::Initialize()
{
    bool isCorrect = false;
    std::string str;
    while (!isCorrect) {
        std::cout << "������� ������� (abort - ������):" << std::endl;
        std::getline(std::cin, str);
        if (str == "abort") {
            throw std::exception("");
        }
        if (str == "") {
            print_message("������� �� ����� ���� ������!");
        } else {
            surname = str;
            isCorrect = true;
        }
    }
	isInitialized = true;
}

std::string SurnameFunctor::GetStringValue() {
	if (!isInitialized) {
		throw std::exception("���������� ������������ �������������������� �������.");
	}
	return surname;
}

bool SurnameFunctor::Initialize(std::string value) {
	if (!isInitialized) {
		throw std::exception("���������� ������������ �������������������� �������.");
	}
	if (value != "") {
		surname = value;
		return true;
	}
	return false;
}

Bill SurnameFunctor::GetValue()
{
	if (!isInitialized) {
		throw std::exception("���������� ������������ �������������������� �������.");
	}
    if (surname == "") {
        throw std::invalid_argument("���������� ������� �������� �� ��������������������� ��������!");
    }
    Bill* bill = new Bill();
    bill->setSurname(surname);
    return *bill;
}

SurnameFunctor::~SurnameFunctor()
{
}
