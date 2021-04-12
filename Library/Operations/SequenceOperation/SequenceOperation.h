#pragma once

#include <string>
#include <sstream>

#include "../IOperation.h"

template <class T>
class SequenceOperation: public IOperation<T> {

public:

	enum OperationType {
		Empty,
		Insert,
		Delete,
		Delta,
		Match
	};

	virtual SequenceOperation<T>::OperationType type() {
		return SequenceOperation<T>::OperationType::Empty;
	}

    virtual SequenceOperation<T>* clone() = 0;

protected:

    SequenceOperation() = default;
    SequenceOperation(SequenceOperation<T> const & ) = default;
    SequenceOperation& operator=(SequenceOperation<T> const & ) = default;

};

#include "InsertSequenceOperation.h"
#include "DeleteSequenceOperation.h"
#include "MatchSequenceOperation.h"
#include "DeltaSequenceOperation.h"

