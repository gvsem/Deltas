#pragma once
#include "IMerge.h"
#include "Deltas/Delta.h"

template <class T>
class Merge : public IMerge<T> {
public:

    Merge(Delta<T>& a, Delta<T>& b) {
        throw std::runtime_error("Not implemented method.");
    }

    virtual Delta<T>* delta() {
        throw std::runtime_error("Not implemented method.");
    }

    virtual std::string print() {
        throw std::runtime_error("Not implemented method.");
    }

    bool hasSpecialization() override {
        return false;
    }

protected:

    friend Delta<T>;
};

#include "MergeSet.h"
#include "MergeMultiset.h"
#include "MergeVector.h"
#include "MergeMap.h"