#pragma once

template <class T>
class IOperation {

public:

	virtual std::string print() {
		return "Empty";
	}

    virtual T patch(T& a) {
        return T();
    }

};
