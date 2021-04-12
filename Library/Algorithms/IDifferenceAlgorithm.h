#pragma once

#include "Operations/SequenceOperation/SequenceOperation.h"

#include <string>
#include <exception>
#include <vector>


template <class T, class U>
class IDifferenceAlgorithm {

public:

//    static void apply(const T& initialState, const T& finalState, Delta<T>& delta) {
//        throw std::runtime_error("Not implemented method.");
//    }

    virtual std::vector<SequenceOperation<U>*>& getEditorialPrescription() {
        throw std::runtime_error("Not implemented method.");
    }

    virtual int size() {
        throw std::runtime_error("Not implemented method.");
    }

    virtual std::string print() {
        throw std::runtime_error("Not implemented method.");
    }

};