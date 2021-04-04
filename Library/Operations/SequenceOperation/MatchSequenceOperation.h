#pragma once

template <class T>
class MatchSequenceOperation : public SequenceOperation<T> {

public:

    MatchSequenceOperation(int quantity): _quantity(quantity) {

    }

    typename SequenceOperation<T>::OperationType type() override {
        return SequenceOperation<T>::OperationType::Match;
    }

    std::string print() override {
        typename std::stringstream ss;
        ss << "Match x" << _quantity;
        return ss.str();
    }

    int getQuantity() {
        return _quantity;
    }

    SequenceOperation<T>* clone() override {
        return new MatchSequenceOperation(*this);
    }

protected:
    //MatchSequenceOperation() = default;
    MatchSequenceOperation(MatchSequenceOperation<T> const & ) = default;
    MatchSequenceOperation& operator=(MatchSequenceOperation<T> const & ) = default;

private:
    int _quantity;

};