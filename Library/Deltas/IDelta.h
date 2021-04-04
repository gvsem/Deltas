#pragma once
//
//template <class T>
//class Delta;

#include <string>
#include <exception>
#include <stdexcept>
#include "Delta.h"

template <class T>
class IMerge;

template <class T>
class IDelta {

public:

	IDelta() {
		//throw new typename std::exception("It is not possible to instantiate abstract class.");
	}

	IDelta(T& initialState, T& finalState) {

	}

	virtual IDelta& operator=(const IDelta& other) {
		return *this;
	}

	virtual IDelta& operator=(const IDelta&& other) {
		*this = std::move(other);
		return *this;
	}

	virtual T patch(T& initialState) {
        throw std::runtime_error("Not implemented method.");
		return T();
	}

	virtual IDelta<T>* reverse() {
		throw std::runtime_error("Not implemented method.");
		return this;
	}

//    virtual IMerge<T>* merge(IDelta<T>& other) {
//        throw std::runtime_error("Not implemented method.");
//        return nullptr;
//    }

	virtual std::string print() {
        throw std::runtime_error("Not implemented method.");
        return "";
	}

	virtual ~IDelta() {

	}

};