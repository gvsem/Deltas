#pragma once

#include <memory>
#include "../IOperation.h"


template <class T>
class SetOperation: public IOperation<T> {

public:

	enum OperationType {
		Insert,
		Delete,
		Empty
	};

	virtual SetOperation<T>::OperationType type() {
		return SetOperation<T>::OperationType::Empty;
	}

    virtual T& getValue() {
        throw std::runtime_error("Not implemented method.");
    }

    virtual unsigned long getQuantity() {
        return 0;
    }

    virtual long getBalance() {
	    return this->getQuantity();
	}

    virtual SetOperation<T>* clone() = 0;

protected:
    SetOperation() = default;
    SetOperation(SetOperation<T> const & ) = default;
    SetOperation& operator=(SetOperation<T> const & ) = default;

};

#include "InsertSetOperation.h"
#include "DeleteSetOperation.h"
