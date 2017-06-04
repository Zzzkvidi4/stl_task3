#include "stdafx.h"
#include "Bill.h"
#include "decimal.h"

//����������� �� ���������
Bill::Bill() {
	address = Address();
	date = Date();
	surname = "";
	payment_type = "";
	peni = 0.0;
	payment = 0.0;
	delay_number = 0;
	hasPeni = false;
}

//����������� �� ������
Bill::Bill(std::string str) {
	if (!StrToBill(str, *this)) {
		throw std::invalid_argument("������ �������������� ������ � ����!");
	}
}

//�������������� � ������
std::string Bill::to_string()
{
	return address.to_string() + '`' + surname + '`' + date.to_string() + '`' + payment_type + '`' + 
			dec::toString(payment) + '`' + dec::toString(peni) + '`' + std::to_string(delay_number);
}

//�������������� �� ������
bool Bill::StrToBill(std::string str, Bill& bill) {
	bool res = true;
	size_t position = str.find('`');
	if (position == std::string::npos) {
		return false;
	}
	std::string buf = str.substr(0, position);
	res = Address::StrToAddress(buf, bill.address);
	if (!res) {
		return false;
	}
	str = str.substr(position + 1);

	position = str.find('`');
	if (position == std::string::npos) {
		return false;
	}
	bill.surname = str.substr(0, position);
	str = str.substr(position + 1);

	position = str.find('`');
	if (position == std::string::npos) {
		return false;
	}
	buf = str.substr(0, position);
	res = Date::StrToDate(buf, bill.date);
	if (!res) {
		return false;
	}
	str = str.substr(position + 1);

	position = str.find('`');
	if (position == std::string::npos) {
		return false;
	}
	bill.payment_type = str.substr(0, position);
	str = str.substr(position + 1);

	position = str.find('`');
	if (position == std::string::npos) {
		return false;
	}
	buf = str.substr(0, position);
	try {
		if (!checkInt(buf)) {
			throw std::invalid_argument("");
		}
		bill.payment = std::stoi(buf);
	}
	catch (std::exception e) {
		return false;
	}
	str = str.substr(position + 1);

	position = str.find('`');
	if (position == std::string::npos) {
		return false;
	}
	buf = str.substr(0, position);
	try {
		if (!checkDouble(buf)) {
			throw std::invalid_argument("");
		}
		bill.peni = std::stod(buf);
	}
	catch (std::exception e) {
		return false;
	}
	str = str.substr(position + 1);

	try {
		if (!checkInt(buf)) {
			throw std::invalid_argument("");
		}
		bill.delay_number = std::stoi(buf);
	}
	catch (std::exception e) {
		return false;
	}
	return true;
}

//������� ��� ������
void Bill::setAddress(Address adr) {
	address = adr;
}

//������� � ������� ��� �����
void Bill::setStreetName(std::string street_name)
{
	if (street_name == "") {
        throw std::exception("����� �� ����� ���� ������ �������.");
	}
    this->address.setStreetName(street_name);
}

std::string Bill::getStreetName() {
	return address.getStreetName();
}

//������� � ������� ��� ������ ����
void Bill::setHouseNumber(std::string house_number)
{
	if (house_number == "0") {
        throw std::exception("����� ���� �� ������ ���� ����� 0.");
	}
    this->address.setHouseNumber(house_number);
}

void Bill::setHouseNumber(int num) {
	address.setHouseNumber(num);
}

int Bill::getHouseNumber() {
	return address.getHouseNumber();
}

//������� � ������� ������ ��������
void Bill::setBlockNumber(std::string block_number)
{
	this->address.setBlockNumber(block_number);
}

int Bill::getBlockNumber() {
	return address.getBlockNumber();
}

//������� � ������� ��� ������ ��������
void Bill::setApartmentNumber(std::string appartment_number)
{
	this->address.setApartmentNumber(appartment_number);
}

void Bill::setApartmentNumber(int num) {
	address.setApartmentNumber(num);
}

int Bill::getApartmentNumber() {
	return address.getApartmentNumber();
}

//������� � ������� ��� �������
void Bill::setSurname(std::string surname)
{
	if (surname == "") {
		throw std::invalid_argument("������� ��������� �� ����� ���� ������!");
	}
	this->surname = surname;
}

std::string Bill::getSurname() {
	return surname;
}

//������� � ������� ��� ����
void Bill::setDate(Date date)
{
	this->date = date;
}

Date& Bill::getDate() {
	return date;
}

//������� � ������� ��� ���� ������
void Bill::setPaymentType(std::string payment_type)
{
	if (payment_type == "") {
		throw std::invalid_argument("��� ������� �� ����� ���� ������ �������!");
	}
	this->payment_type = payment_type;
}

std::string Bill::getPaymentType() {
	return payment_type;
}

//������� � ������� ��� ����� ������
void Bill::setPayment(double payment)
{
	this->payment = payment;
}

void Bill::setPayment(std::string str) {
	double buf;
	dec::decimal<2> tmp = payment;
	try {
		if (!checkDouble(str)) {
			throw std::invalid_argument("");
		}
		buf = std::stod(str);
		dec::fromString(str, this->payment);
	}
	catch (std::exception e) {
		throw std::invalid_argument("����� ������� �� ����� ���� �� ������!");
	}
	if (buf < 0) {
		payment = tmp;
		throw std::invalid_argument("����� �� ����� ���� ������ ����!");
	}
}

dec::decimal<2> Bill::getPayment() {
	return payment;
}

//������� � ������� ��� �������� ����
void Bill::setPeni(double peni)
{
	if (peni > DBL_EPSILON) {
		this->peni = peni;
	}
}

void Bill::setPeni(std::string str) {
	double buf;
	dec::decimal<2> tmp = peni;
	try {
		if (!checkDouble(str)) {
			throw std::invalid_argument("");
		}
		buf = std::stod(str);
		dec::fromString(str, this->peni);
	}
	catch (std::exception e) {
		throw std::invalid_argument("���� �� ����� ���� �� ������!");
	}
	if (buf < 0) {
		peni = tmp;
		throw std::invalid_argument("������� ���� �� ����� ���� ������ ����!");
	}
}

dec::decimal<2> Bill::getPeni() {
	return peni;
}

//������� � ������� ��� ���������� ���� ���������
void Bill::setDelayNumber(int delay_number)
{
	if (delay_number >= 0) {
		this->delay_number = delay_number;
		hasPeni = delay_number > 0;
	}
}

void Bill::setDelayNumber(std::string str) {
	int tmp = delay_number;
	try {
		if (!checkInt(str)) {
			throw std::invalid_argument("");
		}
		this->delay_number = std::stoi(str);
		hasPeni = delay_number > 0;
	}
	catch (std::exception e) {

		throw std::invalid_argument("���������� ���� ��������� �� ����� ���� �� ������!");
	}
	if (delay_number < 0) {
		delay_number = tmp;
		throw std::exception("���������� ���� �� ������ ���� ������ ����!");
	}
}

int Bill::getDelayNumber() {
	return delay_number;
}

void Bill::setHasPeni(bool val) {
	hasPeni = val;
}

//������� ����
dec::decimal<2> Bill::countPeni() {
	return dec::decimal_cast<2>(peni*delay_number)*payment;
}

//����������� �� �����
bool Bill::houseNumberComparator(Bill bill1, Bill bill2)
{
	return bill1.address.getHouseNumber() < bill2.address.getHouseNumber();
}

bool Bill::appartmentNumberComparator(Bill bill1, Bill bill2)
{
	return bill1.address.getApartmentNumber() < bill2.address.getApartmentNumber();
}

bool Bill::surnameComparator(Bill bill1, Bill bill2)
{
	return bill1.surname < bill2.surname;
}

bool Bill::dateComparator(Bill bill1, Bill bill2) {
	return bill1.date < bill2.date;
}

bool Bill::peniComparator(Bill bill1, Bill bill2) {
	return bill1.countPeni() < bill2.countPeni();
}

bool Bill::operator==(Bill bill)
{
	return this->to_string() == bill.to_string();
}

//�������� �����/������
std::ostream& operator<<(std::ostream & cout, Bill bill)
{
	cout << "�����: " << bill.address << std::endl << "��������: " << bill.surname << std::endl 
			<< "����: " << bill.date << std::endl << "��� �������: " << bill.payment_type << std::endl 
			<< "����� �������: " << dec::toString(bill.payment) << std::endl << "����: " << dec::toString(bill.peni) << std::endl 
			<< "���� �����������: " << bill.delay_number << std::endl << "����: " << bill.countPeni() + bill.getPayment();
	return cout;
}

std::istream& operator>>(std::istream & cin, Bill &bill)
{
	std::string buf;
	double buffer;
	std::getline(cin, buf);
	size_t position = buf.find("�����:");
	if (position == std::string::npos) {
		throw std::invalid_argument("���� �����������!");
	}
	buf = buf.substr(position + 7);
	if (!Address::StrToAddress(buf, bill.address)) {
		throw std::invalid_argument("���������� ������������� ������ � ������!");
	}

	std::getline(cin, buf);
	position = buf.find("��������:");
	if (position == std::string::npos) {
		throw std::invalid_argument("���� �����������!");
	}
	buf = buf.substr(position + 10);
	if (buf == "") {
		throw std::invalid_argument("������� ��������� �� ����� ���� ������ �������!");
	}
	bill.surname = buf;

	std::getline(cin, buf);
	position = buf.find("����:");
	if (position == std::string::npos) {
		throw std::invalid_argument("���� �����������!");
	}
	buf = buf.substr(position + 6);
	if (!Date::StrToDate(buf, bill.date)) {
		throw std::invalid_argument("���������� ������������� ������ � ����!");
	}

	std::getline(cin, buf);
	position = buf.find("��� �������:");
	if (position == std::string::npos) {
		throw std::invalid_argument("���� �����������!");
	}
	buf = buf.substr(position + 13);
	if (buf == "") {
		throw std::invalid_argument("��� ������� �� ����� ���� ������ �������!");
	}
	bill.payment_type = buf;

	std::getline(cin, buf);
	position = buf.find("����� �������:");
	if (position == std::string::npos) {
		throw std::invalid_argument("���� �����������!");
	}
	buf = buf.substr(position + 15);
	try {
		if (!checkDouble(buf)) {
			throw std::invalid_argument("");
		}
		buffer = std::stod(buf);
		dec::fromString(buf, bill.payment);
	}
	catch (std::invalid_argument e) {
		throw std::invalid_argument("����� ������� �� ����� ���� �� ������!");
	}
	if (buffer < 0) {
		throw std::invalid_argument("����� ������� �� ����� ���� �������������!");
	}

	std::getline(cin, buf);
	position = buf.find("����:");
	if (position == std::string::npos) {
		throw std::invalid_argument("���� �����������!");
	}
	buf = buf.substr(position + 6);
	try {
		if (!checkDouble(buf)) {
			throw std::invalid_argument("");
		}
		buffer = std::stod(buf);
		dec::fromString(buf, bill.peni);
	}
	catch (std::invalid_argument e) {
		throw std::invalid_argument("������� ���� �� ����� ���� �� ������!");
	}

	if (buffer < 0) {
		throw std::invalid_argument("����� ������� �� ����� ���� �������������!");
	}
	std::getline(cin, buf);
	position = buf.find("���� �����������:");
	if (position == std::string::npos) {
		throw std::invalid_argument("���� �����������!");
	}
	buf = buf.substr(position + 18);
	try {
		if (!checkInt(buf)) {
			throw std::invalid_argument("");
		}
		bill.delay_number = std::stoi(buf);
	}
	catch (std::invalid_argument e) {
		throw std::invalid_argument("���������� ���� ����������� �� ����� ���� �� ������!");
	}
	if (bill.delay_number < 0) {
		throw std::invalid_argument("���������� ���� ����������� �� ����� ���� �������������!");
	}

	std::getline(cin, buf);
	bill.hasPeni = bill.delay_number > 0;
	return cin;
}
