#pragma once
#include <string>

class TelephoneNumber {

public:

	static enum Type {
		NotSpecified,
		Home,
		Office
	};

	TelephoneNumber(std::string phone, TelephoneNumber::Type type): _phone(phone), _type(type) {

	}

private:
	std::string _phone;
	TelephoneNumber::Type _type;

};
