#pragma once
#include <sstream>
#include "SetOperation.h"

template <class T>
class InsertSetOperation : public SetOperation<T> {

public:

	InsertSetOperation(T& value, unsigned long quantity = 1) : _value(value), _quantity(quantity) {

	}

	typename SetOperation<T>::OperationType type() override {
		return SetOperation<T>::OperationType::Insert;
	}

	std::string print() override {
		typename std::stringstream ss;
		ss << "Insert " << _value << " x" << _quantity;
		return ss.str();
	}

	T& getValue() override {
		return _value;
	}

    unsigned long getQuantity() override {
        return _quantity;
    }

    long getBalance() override {
        return this->getQuantity();
    }

    SetOperation<T>* clone() override {
        return new InsertSetOperation(*this);
	}

    T patch(T& a) override {
        return _value;
    }

protected:
    InsertSetOperation(InsertSetOperation<T> const & ) = default;
    InsertSetOperation& operator=(InsertSetOperation<T> const & ) = default;

private:
	T _value;
    unsigned long _quantity;

};