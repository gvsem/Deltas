#pragma once

#include <string>
#include <sstream>

#include "../IOperation.h"

template <class T>
class MapOperation: public IOperation<T> {

public:

    enum OperationType {
        Empty,
        InsertModify,
        Delete,
        Delta
    };

    virtual MapOperation<T>::OperationType type() {
        return MapOperation<T>::OperationType::Empty;
    }

    virtual MapOperation<T>* clone() = 0;

protected:

    SequenceOperation() = default;
    SequenceOperation(SequenceOperation<T> const & ) = default;
    SequenceOperation& operator=(SequenceOperation<T> const & ) = default;

};

#include "InsertSequenceOperation.h"
#include "DeleteSequenceOperation.h"
#include "MatchSequenceOperation.h"
#include "DeltaSequenceOperation.h"

