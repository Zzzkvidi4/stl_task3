#include "stdafx.h"
#include "DateFunctor.h"
#include "Bill.h"


DateFunctor::DateFunctor()
{
    comparator = Bill::dateComparator;
}

bool DateFunctor::operator()(Bill bill)
{
	if (!isInitialized) {
		throw std::exception("���������� ������������ �������������������� �������.");
	}
    return bill.getDate() == date;
}

void DateFunctor::Initialize()
{
    std::string str;
    bool isCorrect = false;
    while (!isCorrect) {
        std::cout << "������� ��� ������� (abort - ������):" << std::endl;
        std::getline(std::cin, str);
        if (str == "abort") {
            throw std::exception("");
        }
        try {
            date.setYear(str);
            isCorrect = true;
        }
        catch (std::exception e) {
            print_message(e.what());
        }
    }

    isCorrect = false;
    while (!isCorrect) {
        std::cout << "������� ����� ������� (abort - ������):" << std::endl;
        std::getline(std::cin, str);
        if (str == "abort") {
            throw std::exception("");
        }
        try {
            date.setMonth(str);
            isCorrect = true;
        }
        catch (std::exception e) {
            print_message(e.what());
        }
    }

    isCorrect = false;
    while (!isCorrect) {
        std::cout << "������� ���� ������� (abort - ������):" << std::endl;
        std::getline(std::cin, str);
        if (str == "abort") {
            throw std::exception("");
        }
        try {
            date.setDay(str);
            isCorrect = true;
        }
        catch (std::exception e) {
            print_message(e.what());
        }
    }
    isInitialized = true;
}

bool DateFunctor::Initialize(std::string value) {
	try {
		Date::StrToDate(value, date);
		isInitialized = true;
		return true;
	}
	catch (std::exception e) {
		return false;
	}
}

std::string DateFunctor::GetStringValue() {
	if (!isInitialized) {
		throw std::exception("���������� ������������ �������������������� �������.");
	}
	return date.to_string();
}

Bill DateFunctor::GetValue()
{
	if (!isInitialized) {
		throw std::exception("���������� ������������ �������������������� �������.");
	}
    Bill* bill = new Bill();
    bill->setDate(date);
    return *bill;
}


DateFunctor::~DateFunctor()
{
}
