#pragma once

#include "Deltas/Delta.h"
#include "Merge.h"
#include "Operations/SequenceOperation/SequenceOperation.h"
#include "PrescriptionForwardIterator.h"

#include <set>
#include <iostream>

template <typename U>
class Merge<std::vector<U>> : public IMerge<std::vector<U>> {

public:
    typedef std::vector<U> T;
    typedef typename Delta<T>::CollectionOperation CollectionOperation;

    enum ConflictPolicy {
        PreferA,
        PreferB
    };

    Merge(Delta<T>& a, Delta<T>& b) {
        this->operationsA = a.getOperations();
        this->operationsB = b.getOperations();
    }
    
    Delta<T>* delta() override {
        return delta(ConflictPolicy::PreferA);
    }

    Delta<T>* delta(ConflictPolicy policy) {

        std::vector<CollectionOperation*> r = std::vector<CollectionOperation*>();
        auto i = new PrescriptionForwardIterator<T>(this->operationsA);
        auto j = new PrescriptionForwardIterator<T>(this->operationsB);

        while (!(i->end()) && !(j->end())) {

            typename CollectionOperation::OperationType typeA = i->type();
            typename CollectionOperation::OperationType typeB = j->type();
          
            if ((typeA == CollectionOperation::OperationType::Match) && (typeA == typeB)) {
                int m = std::min(i->getQuantity(), j->getQuantity());
                r.push_back(new MatchSequenceOperation<U>(m));
                i->next(m);
                j->next(m);
                continue;
            }

            if ((typeA == CollectionOperation::OperationType::Delete) && (typeA == typeB)) {
                r.push_back(i->get());
                i->next();
                j->next();
                continue;
            }

            if ((typeA == CollectionOperation::OperationType::Delta) && (typeA == typeB)) {
                DeltaSequenceOperation<U>* opA = dynamic_cast<DeltaSequenceOperation<U>*>(i->get());
                DeltaSequenceOperation<U>* opB = dynamic_cast<DeltaSequenceOperation<U>*>(j->get());

                Merge<U>* m = new Merge<U>(opA->getDelta(), opB->getDelta());
                if (m->hasSpecialization()) {
                    r.push_back(new DeltaSequenceOperation<U>(m->delta()));
                } else {
                    if (policy == ConflictPolicy::PreferA) {
                        r.push_back(opA);
                    }
                    if (policy == ConflictPolicy::PreferB) {
                        r.push_back(opB);
                    }
                }
                
                i->next();
                j->next();
                continue;
            }

            if ((typeA == CollectionOperation::OperationType::Insert) && (typeA == typeB)) {
                InsertSequenceOperation<U>* opA = dynamic_cast<InsertSequenceOperation<U>*>(i->get());
                InsertSequenceOperation<U>* opB = dynamic_cast<InsertSequenceOperation<U>*>(j->get());
                
//                if (opA->getValue() == opB->getValue()) {
//                    r.push_back(opA);
//                    i->next();
//                    j->next();
//                    continue;
//                }
                
                if (policy == ConflictPolicy::PreferA) {
                    r.push_back(opA);
                    i->next();
                }
                if (policy == ConflictPolicy::PreferB) {
                    r.push_back(opB);
                    j->next();
                }

                continue;
            }

            if (typeA == CollectionOperation::OperationType::Match) {
                if (j->type() == CollectionOperation::Insert) {
                    r.push_back(j->get());
                }
                if (j->type() == CollectionOperation::Delete){
                    r.push_back(j->get());
                    i->next();
                }
                if (j->type() == CollectionOperation::Empty){
                    r.push_back(i->get());
                    i->next();
                }
                if (j->type() == CollectionOperation::Delta){
                    r.push_back(j->get());
                    i->next();
                }
                j->next();
                continue;
            }

            if (typeB == CollectionOperation::OperationType::Match) {
                if (i->type() == CollectionOperation::Insert) {
                    r.push_back(i->get());
                }
                if (i->type() == CollectionOperation::Delete){
                    r.push_back(i->get());
                    j->next();
                }
                if (i->type() == CollectionOperation::Empty){
                    r.push_back(j->get());
                    j->next();
                }
                if (i->type() == CollectionOperation::Delta){
                    r.push_back(i->get());
                    j->next();
                }
                i->next();
                continue;
            }

            if ((typeA == CollectionOperation::OperationType::Delete) &&
                    ((typeB == CollectionOperation::OperationType::Insert) || 
                        (typeB == CollectionOperation::OperationType::Delta))) {
                r.push_back(j->get());
                j->next();
                continue;
            }

            if ((typeA == CollectionOperation::OperationType::Insert) &&
                    ((typeB == CollectionOperation::OperationType::Delete) ||
                            (typeB == CollectionOperation::OperationType::Delta))) {
                r.push_back(i->get());
                i->next();
                continue;
            }

        }

        while (!(i->end())) {
            r.push_back(i->get());
            i->next();
        }

        while (!(j->end())) {
            r.push_back(j->get());
            j->next();
        }

        return new Delta<T>(r);
    }

    std::string print() {
        return "";
    }

protected:
    std::vector<CollectionOperation*> operationsA;
    std::vector<CollectionOperation*> operationsB;

    friend class Delta<T>;

};