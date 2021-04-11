#pragma once

#include "../Library/Deltas/Delta.h"

#include "Contact.h"
#include <set>

class Contacts: public Deltable {

public:

	// getPropertiesList();
	// getProperty(name)

	Contacts() {
		this->_contactList = std::set<Contact>();
	}

private:
	std::set<Contact> _contactList;

	Contacts(std::set<Contact> contactList): _contactList(contactList) {

	}

	friend Delta<Contacts>;
};

template <>
class Delta<Contacts>: protected Delta<std::vector<Contact *>> {

	typedef Contacts T;

public:

	Delta(T& initialState, T& finalState) : IDelta<T>(initialState, finalState) {
		this->_contactList = Delta<std::set<Contact>>(initialState._contactList, finalState._contactList);
	}

	Delta& operator=(const Delta& other) {
		this->_contactList = other._contactList;
		return *this;
	}

	Delta& operator=(const Delta&& other) {
		this->_contactList = std::move(other._contactList);
		return *this;
	}

	T patch(T& initialState) override {
		return finalState(this->_contactList.patch(initialState._contactsList));
	}

	Delta<T>* reverse() {
		return Delta<T>(*this->_contactList.reverse());
	}
	
	std::string print() {
		return "";
	}

	~Delta() override {

	}

private:

	Delta(Delta<std::set<Contact>> contactList): _contactList(contactList) {

	}

	Delta<std::set<Contact>> _contactList;

};