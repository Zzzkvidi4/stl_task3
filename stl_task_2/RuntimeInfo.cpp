#include "stdafx.h"
#include "RuntimeInfo.h"
#include "help_utils.h"


RuntimeInfo* RuntimeInfo::instance = 0;

std::ostream & operator<<(std::ostream & out, RuntimeInfo & info) {
	out << info.getFileName() << std::endl;
	out << std::to_string(info.getUserStatus()) << std::endl;
	out << std::to_string(info.getCommandPosition()) << std::endl;
	out << std::to_string(info.getItemPosition()) << std::endl;
	out << info.getFactoryName() << std::endl;
	out << info.getQueryValue() << std::endl;
	return out;
}

std::istream& operator>>(std::istream& in, RuntimeInfo& info) {
	std::string str;
	std::getline(in, str);
	info.setFileName(str);

	std::getline(in, str);
	if (checkInt(str)) {
		int value = std::stoi(str);
		switch (value) {
			case ROLE_MANAGER: {
				info.setManagerStatus();
				break;
			}
			default: {
				info.setUserStatus();
				break;
			}
		}
	}

	std::getline(in, str);
	if (checkInt(str)) {
		info.setCommandPosition(std::stoi(str));
	}

	std::getline(in, str);
	if (checkInt(str)) {
		info.setItemPosition(std::stoi(str));
	}

	std::getline(in, str);
	info.setFactoryName(str);

	std::getline(in, str);
	info.setQueryValue(str);
	return in;
}

void RuntimeInfo::setCommandPosition(int command_position) {
	this->command_position = command_position;
}

int RuntimeInfo::getCommandPosition() {
	return command_position;
}

bool RuntimeInfo::recoverInfo() {
	std::ifstream fin(runtime_info_file_name);
	fin >> *this;
	fin.close();
	bool recover_succeed = true;
	if (file_name != "") {
		std::ifstream fin(file_name);
		ContainerUtils<Bill>::read_from_file(fin, *main_container);
		container_status = CONTAINER_EXISTS;
	}


	if (factory_name != "") {
		SearchFunctorFactory<Bill> factory = SearchFunctorFactory<Bill>();
		SelectCommand::PrepareFactory(factory);
		BaseFunctor<Bill>* functor = factory.Create<Bill>(factory_name);
		if ((functor != NULL) && (functor->Initialize(query_value))) {
			sub_container = main_container->GetElemsIf(functor);
			container_status = SUBCONTAINER_EXISTS;
		} else {
			recover_succeed = false;
		}
	}

	if (item_position != -1) {
		switch (container_status) {
			case CONTAINER_EXISTS: {
				try {
					concrete_element = &(main_container->operator[](item_position));
					break;
				}
				catch (std::exception e) {
					recover_succeed = false;
				}
			}
			case SUBCONTAINER_EXISTS: {
				try {
					concrete_element = &(sub_container->operator[](item_position));
					break;
				}
				catch (std::exception e) {
					recover_succeed = false;
				}
			}
		}
	}
	return recover_succeed;
}

void RuntimeInfo::saveInfo() {
	std::ofstream fout(runtime_info_file_name);
	fout << *this;
	fout.close();
}
