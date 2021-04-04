#pragma once

// #include "../Delta.h"

template <class T>
class IMerge {

public:

    virtual Delta<T>* delta() {
        throw std::runtime_error("Not implemented method.");
        return nullptr;
    }
    virtual bool hasConflicts(){
        throw std::runtime_error("Not implemented method.");
        return true;
    };

    virtual std::string print() {
        throw std::runtime_error("Not implemented method.");
        return "";
    }


};