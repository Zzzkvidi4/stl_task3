#pragma once
#include "Command.h"
#include "TemplateContainer.h"
#include "RuntimeInfo.h"

class AddBillCommand: public Command
{
private:
    TemplateContainer<Bill>* cont;
public:

    AddBillCommand(std::string title, TemplateContainer<Bill>* cont): Command(title)
    {
        this->cont = cont;
    }

    void Execute() {
        Bill bill = Bill();
        bool isCorrect = false;
        std::string str;
        while (!isCorrect) {
            std::cout << "������� �����:" << std::endl;
            std::getline(std::cin, str);
            if (str == "abort") {
				throw std::exception("");
            }
            try {
                bill.setStreetName(str);
                isCorrect = true;
            }
            catch (std::exception e) {
                print_message(e.what());
            }
        }

        isCorrect = false;
        while (!isCorrect) {
            std::cout << "������� ����� ����:" << std::endl;
            std::getline(std::cin, str);
            if (str == "abort") {
				throw std::exception("");
            }
            try {
                bill.setHouseNumber(str);
                isCorrect = true;
            }
            catch (std::exception e) {
                print_message(e.what());
            }
        }

        isCorrect = false;
        while (!isCorrect) {
            std::cout << "������� ����� �������� (������ ������ ��� ��������):" << std::endl;
            std::getline(std::cin, str);
            if (str == "abort") {
				throw std::exception("");
            }
            try {
                bill.setBlockNumber(str);
                isCorrect = true;
            }
            catch (std::exception e) {
                print_message(e.what());
            }
        }

        isCorrect = false;
        while (!isCorrect) {
            std::cout << "������� ����� �������� (������ ������ ��� ��������):" << std::endl;
            std::getline(std::cin, str);
            if (str == "abort") {
				throw std::exception("");
            }
            try {
                bill.setApartmentNumber(str);
                isCorrect = true;
            }
            catch (std::exception e) {
                print_message(e.what());
            }
        }

        isCorrect = false;
        while (!isCorrect) {
            std::cout << "������� ��� �������:" << std::endl;
            std::getline(std::cin, str);
            if (str == "abort") {
				throw std::exception("");
            }
            try {
                bill.getDate().setYear(str);
                isCorrect = true;
            }
            catch (std::exception e) {
                print_message(e.what());
            }
        }

        isCorrect = false;
        while (!isCorrect) {
            std::cout << "������� ����� �������:" << std::endl;
            std::getline(std::cin, str);
            if (str == "abort") {
				throw std::exception("");
            }
            try {
                bill.getDate().setMonth(str);
                isCorrect = true;
            }
            catch (std::exception e) {
                print_message(e.what());
            }
        }

        isCorrect = false;
        while (!isCorrect) {
            std::cout << "������� ���� �������:" << std::endl;
            std::getline(std::cin, str);
            if (str == "abort") {
				throw std::exception("");
            }
            try {
                bill.getDate().setDay(str);
                isCorrect = true;
            }
            catch (std::exception e) {
                print_message(e.what());
            }
        }

        isCorrect = false;
        while (!isCorrect) {
            std::cout << "������� ������� ���������:" << std::endl;
            std::getline(std::cin, str);
            if (str == "abort") {
				throw std::exception("");
            }
            try {
                bill.setSurname(str);
                isCorrect = true;
            }
            catch (std::exception e) {
                print_message(e.what());
            }
        }

        isCorrect = false;
        while (!isCorrect) {
            std::cout << "������� ��� �������:" << std::endl;
            std::getline(std::cin, str);
            if (str == "abort") {
				throw std::exception("");
            }
            try {
                bill.setPaymentType(str);
                isCorrect = true;
            }
            catch (std::exception e) {
                print_message(e.what());
            }
        }

        isCorrect = false;
        while (!isCorrect) {
            std::cout << "������� ����� �������:" << std::endl;
            std::getline(std::cin, str);
            if (str == "abort") {
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

        isCorrect = false;
        while (!isCorrect) {
            std::cout << "������� ������� ����:" << std::endl;
            std::getline(std::cin, str);
            if (str == "abort") {
				throw std::exception("");
            }
            try {
                bill.setPeni(str);
                isCorrect = true;
            }
            catch (std::exception e) {
                print_message(e.what());
            }
        }

        isCorrect = false;
        while (!isCorrect) {
            std::cout << "������� ���������� ���� ���������:" << std::endl;
            std::getline(std::cin, str);
            if (str == "abort") {
				throw std::exception("");
            }
            try {
                bill.setDelayNumber(str);
                isCorrect = true;
            }
            catch (std::exception e) {
                print_message(e.what());
            }
        }
        cont->Add(bill);
		RuntimeInfo* runtime_info = RuntimeInfo::getInstance();
		runtime_info->synchronizeContainers();
    }

    ~AddBillCommand()
    {
    }
};

