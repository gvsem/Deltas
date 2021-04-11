#pragma once

#include <string>
#include <vector>
#include <set>

#include "library.h"

//template <class T>
//class Delta;

class Contact {

public:

    Contact() {
        this->names = std::vector<std::string>();
        this->telephones = std::set<std::string>();
    }

    Contact* addName(std::string n) {
        this->names.push_back(n);
        return this;
    }

    Contact* addPhone(std::string n) {
        this->telephones.insert(n);
        return this;
    }

    std::vector<std::string>& getNames() {
        return this->names;
    }

    std::set<std::string>& getPhones() {
        return this->telephones;
    }


protected:

	std::vector<std::string> names;
    std::set<std::string> telephones;

    friend class Delta<Contact>;

};


template <>
class Delta<Contact> : public IDelta<Contact> {

    typedef Contact T;

public:

    Delta(T& initialState, T& finalState) : IDelta<T>(initialState, finalState) {
        this->deltaNames = new Delta<std::vector<std::string>>(initialState.getNames(), finalState.getNames());
        this->deltaPhones = new Delta<std::set<std::string>>(initialState.getPhones(), finalState.getPhones());
    }

    Delta<T> & operator=(const Delta<T>& other) = default;
    Delta<T> & operator=(Delta<T>&& other) = default;

    T patch(T& initialState) override {
        T* finalState = new T(initialState);
        finalState->names = this->deltaNames->patch(initialState.names);
        finalState->telephones = this->deltaPhones->patch(initialState.telephones);
        return *finalState;
    }

    bool hasSpecialization() override {
        return true;
    }

    std::string print() override {
        typename std::stringstream ss;
        ss << deltaNames->print() << "\n";
        ss << deltaPhones->print() << "\n";
        return ss.str();
    }

public:

    ~Delta() {
        delete this->deltaNames;
        delete this->deltaPhones;
    }

protected:

    Delta() {}

    Delta<std::vector<std::string>>* deltaNames;
    Delta<std::set<std::string>>* deltaPhones;

    friend class Merge<T>;

};


template <>
class Merge<Contact> : public IMerge<Contact> {

public:
    typedef Contact T;

    Delta<T>* delta() override {
        Delta<T>* d = new Delta<T>();
        //auto mNames = new Merge<std::vector<std::string>>(a.deltaNames, b.deltaNames);

        d->deltaNames = (new Merge<std::vector<std::string>>(*a.deltaNames, *b.deltaNames))->delta();
        d->deltaPhones = (new Merge<std::set<std::string>>(*a.deltaPhones, *b.deltaPhones))->delta();
        return d;
    }

    std::string print() {
        return "";
    }

    Merge(Delta<T>& _a, Delta<T>& _b): a(_a), b(_b) {

    }

protected:

    Delta<T>& a;
    Delta<T>& b;

    friend class Delta<T>;

};