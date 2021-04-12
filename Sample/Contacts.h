#pragma once

#include "Deltas/Delta.h"
#include "Contact.h"

#include <map>


class Contacts {

public:

    Contacts() {
        this->_contacts = std::map<int, Contact>();
    }

    Contact& addContact() {
        ID_ENUMERATOR++;
        this->_contacts[ID_ENUMERATOR] = Contact();
        return this->_contacts[ID_ENUMERATOR];
    }

    std::string print() {
        typename std::stringstream ss;
        ss << "Contacts: ";
        for (auto i : this->_contacts) {
            ss << i.second.print();
        }
        return ss.str();
    }

protected:

    int ID_ENUMERATOR = 0;
    std::map<int, Contact> _contacts;

    friend class Delta<Contacts>;

};

template <>
class Delta<Contacts> : public IDelta<Contacts> {

    typedef Contacts T;

public:

    Delta(T& initialState, T& finalState) : IDelta<T>(initialState, finalState) {
        this->deltaContacts = new Delta<std::map<int, Contact>>(initialState._contacts, finalState._contacts);
    }

    Delta<T> & operator=(const Delta<T>& other) = default;
    Delta<T> & operator=(Delta<T>&& other) = default;

    T patch(T& initialState) override {
        T* finalState = new T(initialState);
        finalState->_contacts = this->deltaContacts->patch(initialState._contacts);
        return *finalState;
    }

    std::string print() override {
        typename std::stringstream ss;
        ss << deltaContacts->print() << "\n";
        return ss.str();
    }

public:

    ~Delta() {
        delete this->deltaContacts;
    }

protected:

    Delta() {}
    Delta<std::map<int, Contact>>* deltaContacts;

    friend class Merge<T>;

};


template <>
class Merge<Contacts> : public IMerge<Contacts> {

public:
    typedef Contacts T;

    Delta<T>* delta() override {
        Delta<T>* d = new Delta<T>();
        d->deltaContacts = (new Merge<std::map<int, Contact>>(*a.deltaContacts, *b.deltaContacts))->delta();
        return d;
    }

    std::string print() override {
        return "";
    }

    Merge(Delta<T>& _a, Delta<T>& _b): a(_a), b(_b) {

    }

protected:

    Delta<T>& a;
    Delta<T>& b;

    friend class Delta<T>;

};