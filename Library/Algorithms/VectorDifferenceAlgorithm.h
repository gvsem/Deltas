#pragma once
//
//template <class T>
//class Delta;

#include <string>
#include <exception>
#include <stdexcept>
#include <Operations/SequenceOperation/SequenceOperation.h>
#include <vector>


template <class T, class U>
class VectorDifferenceAlgorithm {

public:

//    VectorDifferenceAlgorithm(T& initialState, T& finalState) {
//
//    }

    virtual std::string print() {
        throw std::runtime_error("Not implemented method.");
        return "";
    }

    virtual int size() {
        throw std::runtime_error("Not implemented method.");
        return 0;
    }

    virtual std::vector<SequenceOperation<U>*>& getEditorialPrescription() {
        throw std::runtime_error("Not implemented method.");
    }

};