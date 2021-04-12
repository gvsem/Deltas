#pragma once

template <class T>
class IMerge {

public:

    virtual Delta<T>* delta() {
        throw std::runtime_error("Not implemented method.");
    }

    virtual std::string print() {
        throw std::runtime_error("Not implemented method.");
    }

    virtual bool hasSpecialization() {
        return true;
    }

};