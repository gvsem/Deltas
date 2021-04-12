#pragma once

#include "Deltas/Delta.h"
#include "Merge.h"

#include <set>

template <typename U>
class Merge<std::set<U>> : public IMerge<std::set<U>> {

public:
    typedef std::set<U> T;
    typedef typename Delta<T>::CollectionOperation CollectionOperation;

    Merge(Delta<T>& a, Delta<T>& b) {
        this->operationsA = a.getOperations();
        this->operationsB = b.getOperations();
    }

    Delta<T>* delta() override {

        auto operationalDifference = std::map<U, std::pair<CollectionOperation*, CollectionOperation*>>();
        for (CollectionOperation* op : this->operationsA) {
            operationalDifference[op->getValue()].first = op;
        }
        for (CollectionOperation* op : this->operationsB) {
            operationalDifference[op->getValue()].second = op;
        }

        std::vector<CollectionOperation*> r = std::vector<CollectionOperation*>();
        for (auto& p : operationalDifference) {

            typename CollectionOperation::OperationType a = CollectionOperation::OperationType::Empty;
            typename CollectionOperation::OperationType b = CollectionOperation::OperationType::Empty;
            if (p.second.first != nullptr) {
                a = p.second.first->type();
            }
            if (p.second.second != nullptr) {
                b = p.second.second->type();
            }

            if (a == b) {
                r.push_back(p.second.first->clone());
            } else if (a == CollectionOperation::OperationType::Empty) {
                r.push_back(p.second.second->clone());
            } else {
                r.push_back(p.second.first->clone());
            }

        }

        return new Delta<T>(r);
    }

    std::string print() override {
        return "";
    }

protected:

    std::vector<CollectionOperation*> operationsA;
    std::vector<CollectionOperation*> operationsB;

    friend class Delta<T>;

};