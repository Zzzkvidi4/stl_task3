#include "stdafx.h"
#include "HavePeniFunctor.h"
#include "Bill.h"


HavePeniFunctor::HavePeniFunctor()
{
    comparator = Bill::peniComparator;
}

bool HavePeniFunctor::operator()(Bill bill)
{
    return (bill.countPeni() > dec::decimal_cast<2>(DBL_EPSILON)) == hasPeni;
}

void HavePeniFunctor::Initialize()
{
    std::string str;
    std::cout << "������� ����� � ������������ (Y/N) (N) (abort - ������):" << std::endl;
    std::getline(std::cin, str);
    if (str == "abort") {
        throw std::exception("");
    } else if ((str.length() != 0) && ((str[0] == 'Y') || (str[0] == 'y'))) {
        hasPeni = true;
    } else {
        hasPeni = false;
    }
	isInitialized = true;
}

std::string HavePeniFunctor::GetStringValue() {
	if (!isInitialized) {
		throw std::exception("���������� ������������ �������������������� �������.");
	}
	return std::to_string(hasPeni);
}

bool HavePeniFunctor::Initialize(std::string value) {
	hasPeni = value == "1";
	isInitialized = true;
	return true;
}


Bill HavePeniFunctor::GetValue()
{
	if (!isInitialized) {
		throw std::exception("���������� ������������ �������������������� �������.");
	}
    Bill* bill = new Bill();
    bill->setHasPeni(hasPeni);
    return *bill;
}

HavePeniFunctor::~HavePeniFunctor()
{
}
