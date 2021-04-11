#pragma once

template <class T>
class DeleteSequenceOperation : public SequenceOperation<T> {

public:

    DeleteSequenceOperation(T& value) : _value(value) {

    }

    typename SequenceOperation<T>::OperationType type() override {
        return SequenceOperation<T>::OperationType::Delete;
    }

    std::string print() override {
        typename std::stringstream ss;
        ss << "Delete " << _value;
        return ss.str();
    }

    T& getValue() {
        return _value;
    }

    T patch(T& a) override {
        return _value;
    }

    SequenceOperation<T>* clone() override {
        return new DeleteSequenceOperation(*this);
    }

protected:
    //DeleteSequenceOperation() = default;
    DeleteSequenceOperation(DeleteSequenceOperation<T> const & ) = default;
    DeleteSequenceOperation& operator=(DeleteSequenceOperation<T> const & ) = default;

private:
    T _value;

};