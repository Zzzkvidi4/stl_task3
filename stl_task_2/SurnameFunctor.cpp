#include "stdafx.h"
#include "SurnameFunctor.h"


SurnameFunctor::SurnameFunctor()
{
    comparator = Bill::surnameComparator;
}

bool SurnameFunctor::operator()(Bill bill)
{
	if (!isInitialized) {
		throw std::exception("Невозможно использовать неинициализированный функтор.");
	}
    return bill.getSurname() == surname;
}

void SurnameFunctor::Initialize()
{
    bool isCorrect = false;
    std::string str;
    while (!isCorrect) {
        std::cout << "Введите фамилию (abort - отмена):" << std::endl;
        std::getline(std::cin, str);
        if (str == "abort") {
            throw std::exception("");
        }
        if (str == "") {
            print_message("Фамилия не может быть пустой!");
        } else {
            surname = str;
            isCorrect = true;
        }
    }
	isInitialized = true;
}

std::string SurnameFunctor::GetStringValue() {
	if (!isInitialized) {
		throw std::exception("Невозможно использовать неинициализированный функтор.");
	}
	return surname;
}

bool SurnameFunctor::Initialize(std::string value) {
	if (!isInitialized) {
		throw std::exception("Невозможно использовать неинициализированный функтор.");
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
		throw std::exception("Невозможно использовать неинициализированный функтор.");
	}
    if (surname == "") {
        throw std::invalid_argument("Невозможно создать значение по неинициализированному функтору!");
    }
    Bill* bill = new Bill();
    bill->setSurname(surname);
    return *bill;
}

SurnameFunctor::~SurnameFunctor()
{
}
