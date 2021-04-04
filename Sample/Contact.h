#pragma once

#include <string>
#include <vector>

#include "TelephoneNumber.h"

class Contact : public Deltable {

protected:
	
	//
	//

	std::string firstName;
	std::string middleName;
	std::string lastName;

	std::vector<TelephoneNumber> telephones;

};

template <>
class Delta<Contact> : ... {

	Delta(Contact& initial, Contact& final)[
		//if (initial.firstName != final.firstName)
	]

		Contact& patch(Contact& initial) {
			return ...;
		}
};