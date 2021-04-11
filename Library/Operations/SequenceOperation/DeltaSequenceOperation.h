#pragma once


template <class T>
class Delta;

template <class T>
class DeltaSequenceOperation : public SequenceOperation<T> {

public:

    DeltaSequenceOperation(T& a, T& b) {
        this->delta = new Delta<T>(a, b);
    }

    DeltaSequenceOperation(Delta<T>* other) {
        this->delta = other;
    }

    typename SequenceOperation<T>::OperationType type() override {
        return SequenceOperation<T>::OperationType::Delta;
    }

    T patch(T& a) override {
        return this->delta->patch(a);
    }

    Delta<T>& getDelta() {
        return *delta;
    }


    DeltaSequenceOperation<T>* getReverseOperation() {
        return new DeltaSequenceOperation<T>(this->delta->reverse());
    }

    std::string print() override {
        typename std::stringstream ss;
        ss << "Delta \n" << this->delta->print();
        return ss.str();
    }

    SequenceOperation<T>* clone() override {
        return new DeltaSequenceOperation(this->delta->clone());
    }

    ~DeltaSequenceOperation() {
        delete delta;
    }


protected:
    //InsertSequenceOperation() = default;
    DeltaSequenceOperation(DeltaSequenceOperation<T> const & other) {
        this->delta = new Delta<T>(other->delta);
    }
    DeltaSequenceOperation& operator=(DeltaSequenceOperation<T> const & other) {
        this->delta = new Delta<T>(other->delta);
    }

    Delta<T>* delta;

};