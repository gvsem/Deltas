#pragma once

#include "IDelta.h"


template <class T>
class Delta : public IDelta<T> {

public:

    Delta(T& initialState, T& finalState) : IDelta<T>(initialState, finalState) {
        this->_initialState = initialState;
        this->_finalState = finalState;
    }

    Delta& operator=(const Delta& other) {
        this->_initialState = other._initialState;
        this->_finalState = other._finalState;
        return *this;
    }

    Delta& operator=(const Delta&& other) {
        this->_initialState = std::move(other._initialState);
        this->_finalState = std::move(other._finalState);
        return *this;
    }

    T patch(T& initialState) override {
        return this->_finalState;
    }

    Delta<T>* reverse() {
        return new Delta<T>(this->_finalState, this->_initialState);
    }

    Delta<T>* clone() {
        return new Delta<T>(_initialState, _finalState);
    }

    ~Delta() override {

    }

    bool hasSpecialization() override {
        return false;
    }

private:

    T _initialState;
    T _finalState;

};



#include "DeltaSet.h"
#include "DeltaMultiset.h"
#include "DeltaVector.h"