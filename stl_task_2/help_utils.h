#pragma once
#include "stdafx.h"

//������� ��� ������ ���������
void print_message(std::string msg);

//������� ��������� ������ �� ��������� ����� min � max
void getChoice(int min, int max, int& choice_number);

//������� ��������� ����� ������ min
void getIntGreater(int min, int& value);

bool input_query(std::string str);

bool checkInt(std::string str);

bool checkDouble(std::string str);

