#pragma once

#include "Merge.h"
#include "Deltas/Delta.h"

#include <set>

template <typename U>
class Merge<std::multiset<U>> : public IMerge<std::multiset<U>> {

public:
    typedef std::multiset<U> T;
    typedef typename Delta<T>::CollectionOperation CollectionOperation;

    enum ConflictPolicy {
        PreferA,
        PreferB,
        ConsolidateDeletions,
        ConsolidateInsertions
    };

    Merge(Delta<T>& a, Delta<T>& b) {
        this->operationsA = a.getOperations();
        this->operationsB = b.getOperations();

    }

    Delta<T>* delta() override {
        return delta(ConflictPolicy::PreferA);
    }

    Delta<T>* delta(ConflictPolicy policy) {

        auto operationalDifference = std::map<U, std::pair<CollectionOperation*, CollectionOperation*>>();
        for (CollectionOperation* op : this->operationsA) {
            operationalDifference[op->getValue()].first = op;
        }
        for (CollectionOperation* op : this->operationsB) {
            operationalDifference[op->getValue()].second = op;
        }
        
        std::vector<CollectionOperation*> r = std::vector<CollectionOperation*>();
        for (auto& p : operationalDifference) {
            long a = 0;
            long b = 0;
            if (p.second.first != nullptr) {
                a = p.second.first->getBalance();
            }
            if (p.second.second != nullptr) {
                b = p.second.second->getBalance();
            }
            CollectionOperation * op = this->getResultOperation(p.first, a, b, policy);
            if (op != nullptr) {
                r.push_back(op);
            }
        }

        return new Delta<T>(r);
    }

    std::string print() {
        
    }


protected:

    long getResultBalance(long a, long b, ConflictPolicy policy) {
        if (a == b) {
            return a;
        }
        if (a == 0) {
            return b;
        }
        if (b == 0) {
            return a;
        }
        switch (policy) {
            case ConflictPolicy::PreferA :
                return a;
                break;
            case ConflictPolicy::PreferB :
                return b;
                break;
            case ConflictPolicy::ConsolidateInsertions :
                return std::max(a, b);
                break;
            case ConflictPolicy::ConsolidateDeletions :
                return std::min(a, b);
                break;
            default:
                return 0;
        }
    }

    CollectionOperation* getResultOperation(U u, long a, long b, ConflictPolicy policy) {
        long r = this->getResultBalance(a, b, policy);
        if (r > 0) {
            return new InsertSetOperation<U>(u, (unsigned long) r);
        } else if (r < 0) {
            return new DeleteSetOperation<U>(u, (unsigned long)(-r));
        } else {
            return nullptr;
        }
    }

    std::vector<CollectionOperation*> operationsA;
    std::vector<CollectionOperation*> operationsB;

    friend class Delta<T>;

};