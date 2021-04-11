#pragma once

#include "Merge.h"
#include <map>

#include "../Delta.h"

template <typename K, typename V>
class Merge<std::map<K, V>> : public IMerge<std::map<K, V>> {

public:

    typedef std::map<K, V> T;
    typedef MapOperation<K, V> CollectionOperation;

    enum ConflictPolicy {
        PreferA,
        PreferB
    };

    bool hasSpecialization() override {
        return true;
    }

    Delta<T>* delta() override {
        return delta(ConflictPolicy::PreferA);
    }

    Delta<T>* delta(ConflictPolicy policy) {

        std::vector<CollectionOperation*> r = std::vector<CollectionOperation*>();

        // I I
        // I D

        std::map<K, std::pair<CollectionOperation*, CollectionOperation*>> operationalDifference;

        for (CollectionOperation* op : this->operationsA) {
            operationalDifference[op->getKey()].first = op;
        }

        for (CollectionOperation* op : this->operationsB) {
            operationalDifference[op->getKey()].second = op;
        }

        for (auto& p : operationalDifference) {

            typename CollectionOperation::OperationType a = CollectionOperation::OperationType::Empty;
            typename CollectionOperation::OperationType b = CollectionOperation::OperationType::Empty;
            if (p.second.first != nullptr) {
                a = p.second.first->type();
            }
            if (p.second.second != nullptr) {
                b = p.second.second->type();
            }

            if ((a == CollectionOperation::OperationType::Empty) && (b != CollectionOperation::OperationType::Empty)) {
                r.push_back(p.second.second);
            }

            if ((a != CollectionOperation::OperationType::Empty) && (b == CollectionOperation::OperationType::Empty)) {
                r.push_back(p.second.first);
            }

            if (a == CollectionOperation::OperationType::Insert) {
                if (b == CollectionOperation::OperationType::Insert) {

                    InsertMapOperation<K, V>* opA = dynamic_cast<InsertMapOperation<K, V>*>(p.second.first);
                    InsertMapOperation<K, V>* opB = dynamic_cast<InsertMapOperation<K, V>*>(p.second.second);

                    if (opA->getValue() == opB->getValue()) {
                        r.push_back(p.second.first);
                    } else {
                        if (policy == ConflictPolicy::PreferA) {
                            r.push_back(p.second.first);
                        } else if (policy == ConflictPolicy::PreferB) {
                            r.push_back(p.second.second);
                        }
                    }
                }
            }

            if (a == CollectionOperation::OperationType::Delete) {
                if (b == CollectionOperation::OperationType::Delete) {
                    r.push_back(p.second.first);
                }
                if (b == CollectionOperation::OperationType::Delta) {
                    if (policy == ConflictPolicy::PreferA) {
                        r.push_back(p.second.first);
                    } else if (policy == ConflictPolicy::PreferB) {
                        r.push_back(p.second.second);
                    }
                }
            }

            if (a == CollectionOperation::OperationType::Delta) {
                if (b == CollectionOperation::OperationType::Delta) {

                    DeltaMapOperation<K, V>* opA = dynamic_cast<DeltaMapOperation<K, V>*>(p.second.first);
                    DeltaMapOperation<K, V>* opB = dynamic_cast<DeltaMapOperation<K, V>*>(p.second.second);

                    Merge<V>* m = new Merge<V>(opA->getDelta(), opB->getDelta());

                    if (m->hasSpecialization()) {
                        r.push_back(new DeltaMapOperation<K, V>(opA->getKey(), m->delta()));
                    } else {
                        if (policy == ConflictPolicy::PreferA) {
                            r.push_back(opA);
                        }
                        if (policy == ConflictPolicy::PreferB) {
                            r.push_back(opB);
                        }
                    }


                }
                if (b == CollectionOperation::OperationType::Delete) {
                    if (policy == ConflictPolicy::PreferA) {
                        r.push_back(p.second.first);
                    } else if (policy == ConflictPolicy::PreferB) {
                        r.push_back(p.second.second);
                    }
                }
            }

        }

        return new Delta<T>(r);
    }

    bool hasConflicts() override {
        return false;
    }

    std::string print() {
        std::string r;
        return r;
    }

    Merge(Delta<T>& a, Delta<T>& b) {
        this->operationsA = a.getOperations();
        this->operationsB = b.getOperations();
    }

protected:
    std::vector<CollectionOperation*> operationsA;
    std::vector<CollectionOperation*> operationsB;

    friend class Delta<T>;

};