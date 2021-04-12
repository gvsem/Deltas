#pragma once

#include "../Delta.h"
#include <vector>

template <class T>
class PrescriptionForwardIterator;

template <class U>
class PrescriptionForwardIterator<std::vector<U>> {
public:
    
    typedef std::vector<U> T;
    typedef typename Delta<T>::CollectionOperation CollectionOperation;
    
    PrescriptionForwardIterator(std::vector<CollectionOperation*>& _operations) : operations(_operations) {
        this->i = operations.begin();
    }
    
    typename CollectionOperation::OperationType type() {
        if (!end()){
            return (*i)->type();
        }
        return CollectionOperation::OperationType::Empty;
    }
    
    bool end() {
        return i == operations.end();
    }
    
    CollectionOperation* get() {
        return (*i)->clone();
    }
    
    void next(int k = 1) {
    
        if (end()) {
            return;
        }
    
        if (this->type() == CollectionOperation::OperationType::Match) {
            count += k;
            int m = dynamic_cast<MatchSequenceOperation<U>*>(*i)->getQuantity();
            if (count >= m) {
                i++;
                count = 0;
            }
        } else {
            i++;
            count = 0;
        }
    
    }
    
    int getQuantity() {
        return dynamic_cast<MatchSequenceOperation<U>*>(*i)->getQuantity() - count;
    }
    
protected:
    
    std::vector<CollectionOperation*>& operations;
    typename std::vector<CollectionOperation*>::iterator i;
    long count = 0;

};