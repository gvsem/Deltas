#pragma once
#include <sstream>
#include "SetOperation.h"

template <class T>
class DeleteSetOperation : public SetOperation<T> {

public:

	DeleteSetOperation(T& value, unsigned long quantity = 1) : _value(value), _quantity(quantity) {

	}

	typename SetOperation<T>::OperationType type() override {
		return SetOperation<T>::OperationType::Delete;
	}

	std::string print() override {
		typename std::stringstream ss;
		ss << "Delete " << _value << " x" << _quantity;
		return ss.str();
	}

    T& getValue() override {
        return _value;
    }

    unsigned long getQuantity() override {
        return _quantity;
    }

    long getBalance() override {
        return (-1) * this->getQuantity();
    }

    SetOperation<T>* clone() override {
        return new DeleteSetOperation(*this);
    }

protected:
    DeleteSetOperation(DeleteSetOperation<T> const & ) = default;
    DeleteSetOperation& operator=(DeleteSetOperation<T> const & ) = default;

private:
	T _value;
	unsigned long _quantity;

};