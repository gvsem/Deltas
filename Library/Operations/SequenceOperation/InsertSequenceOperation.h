#pragma once

template <class T>
class DeleteSequenceOperation;

template <class T>
class InsertSequenceOperation : public SequenceOperation<T> {

public:

    InsertSequenceOperation(T& value): _value(value) {

    }

    typename SequenceOperation<T>::OperationType type() override {
        return SequenceOperation<T>::OperationType::Insert;
    }

    T& getValue() {
        return _value;
    }

    SequenceOperation<T>* clone() override {
        return new InsertSequenceOperation(*this);
    }

    T patch(T& a) override {
        return _value;
    }

    std::string print() override {
        typename std::stringstream ss;
        ss << "Insert " << _value;
        return ss.str();
    }

protected:
    //InsertSequenceOperation() = default;
    InsertSequenceOperation(InsertSequenceOperation<T> const & ) = default;
    InsertSequenceOperation& operator=(InsertSequenceOperation<T> const & ) = default;

private:
    T _value;

};