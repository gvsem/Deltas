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

    Delta<T>& getDelta() {
        return *delta;
    }

    SequenceOperation<T>* clone() override {
        return new DeltaSequenceOperation(this->delta->clone());
    }

    T patch(T& a) override {
        return this->delta->patch(a);
    }

    std::string print() override {
        typename std::stringstream ss;
        ss << "Delta \n" << this->delta->print();
        return ss.str();
    }

    DeltaSequenceOperation<T>* getReverseOperation() {
        return new DeltaSequenceOperation<T>(this->delta->inverse());
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