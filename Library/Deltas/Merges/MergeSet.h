#pragma once

#include "Merge.h"
#include <set>

#include "../Delta.h"

template <typename U>
class Merge<std::set<U>> : public IMerge<std::set<U>> {

public:
    typedef std::set<U> T;
    typedef typename Delta<T>::CollectionOperation CollectionOperation;

    Delta<T>* delta() override {

        this->calculateOperationalDifference();
        std::vector<CollectionOperation*> r = std::vector<CollectionOperation*>();

        for (auto& p : this->operationalDifference) {

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

    bool hasConflicts() override {
        return false;
    }

    std::string print() {

        this->calculateOperationalDifference();

        std::string r;
        for (auto& p : this->operationalDifference) {

            typename CollectionOperation::OperationType a = CollectionOperation::OperationType::Empty;
            typename CollectionOperation::OperationType b = CollectionOperation::OperationType::Empty;
            if (p.second.first != nullptr) {
                a = p.second.first->type();
            }
            if (p.second.second != nullptr) {
                b = p.second.second->type();
            }

            if (a == b) {
                r += "MATCH: " + p.second.first->print() + "\n";
            } else if (a == CollectionOperation::OperationType::Empty) {
                r += "UNIQUE B: " + p.second.second->print() + "\n";
            } else {
                r += "UNIQUE A: " + p.second.first->print() + "\n";
            }
        }

        return r;

    }

    Merge(Delta<T>& a, Delta<T>& b) {
        this->operationsA = a.getOperations();
        this->operationsB = b.getOperations();
        this->operationalDifference = std::map<U, std::pair<CollectionOperation*, CollectionOperation*>>();
    }

protected:


    void calculateOperationalDifference() {
        if (this->operationalDifference.size() != 0) {
            return;
        }

        for (CollectionOperation* op : this->operationsA) {
            this->operationalDifference[op->getValue()].first = op;
        }

        for (CollectionOperation* op : this->operationsB) {
            this->operationalDifference[op->getValue()].second = op;
        }
    }

    std::vector<CollectionOperation*> operationsA;
    std::vector<CollectionOperation*> operationsB;
    std::map<U, std::pair<CollectionOperation*, CollectionOperation*>> operationalDifference;

    friend class Delta<T>;

};