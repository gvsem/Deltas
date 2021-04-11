#pragma once

#include "Merge.h"
#include <set>
#include <Operations/SequenceOperation/SequenceOperation.h>
#include <iostream>

#include "../Delta.h"

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


template <typename U>
class Merge<std::vector<U>> : public IMerge<std::vector<U>> {

public:
    typedef std::vector<U> T;
    typedef typename Delta<T>::CollectionOperation CollectionOperation;

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
//        typename std::vector<CollectionOperation*>::iterator i = this->operationsA.begin();
//        typename std::vector<CollectionOperation*>::iterator j = this->operationsB.begin();

        //typedef std::vector<char> T;
        //std::string str1 = "Good morning, everyone! My name is Ivan.";
        //std::string str2 = "Good evening, every! My surname is Ivanov!";
        //std::string str3 = "It is good morning today, everyone! My name is, however, Ivan.";
        //std::string str4 = "It is good evening today, every! My surname is, however, Ivanov!";

        //G         ood morevening,          everyone   ! My surname is           Ivanov.
        //M         MMMMDDDIIIMMMMM         MMMMMMDDD   MMMMMIIIMMMMMMM M         MMMMIIM
        // GIt is g ood m   orning today,    everyone   ! My    name is, however, Ivan  .
        // DIIIIIII MMMM M   MMMMMMIIIIIIM   MMMMMMMMM   MMMMM   MMMMMMMIMIIIIIIIIIMMMM  M


        // ddd
        // ddd

        auto i = new PrescriptionForwardIterator<T>(this->operationsA);
        auto j = new PrescriptionForwardIterator<T>(this->operationsB);
        std::cout << "\n";
        while(!(i->end())) {
            if (i->type() == CollectionOperation::OperationType::Match) {
                std::cout << "M";
            }
            if (i->type() == CollectionOperation::OperationType::Insert) {
                std::cout << "I";
            }
            if (i->type() == CollectionOperation::OperationType::Delete) {
                std::cout << "D";
            }
            if (i->type() == CollectionOperation::OperationType::Delta) {
                std::cout << "d";
            }
            i->next();
        }

        std::cout << "\n";

        while(!(j->end())) {
            if (j->type() == CollectionOperation::OperationType::Match) {
                std::cout << "M";
            }
            if (j->type() == CollectionOperation::OperationType::Insert) {
                std::cout << "I";
            }
            if (j->type() == CollectionOperation::OperationType::Delete) {
                std::cout << "D";
            }
            if (j->type() == CollectionOperation::OperationType::Delta) {
                std::cout << "d";
            }
            j->next();
        }
        std::cout << "\n";
        //return new Delta<T>(r);

        i = new PrescriptionForwardIterator<T>(this->operationsA);
        j = new PrescriptionForwardIterator<T>(this->operationsB);

        //M       MMMMDDDIIIIMMMM      MMMMMMMDDDMMMMMIIIMMMMMMM M         MMMMDIII
        //DIIIIIIIMMMMMMM    MMMMIIIIIIMMMMMMMMMMMMMMM   MMMMMMMIMIIIIIIIIIMMMMM
        //DIIIIIIIMMMMDDDIIIIMMMMIIIIIIMMMMMMMDDDMMMMMIIIMMMMMMMIMIIIIIIIIIMMMMDIII

        while (!(i->end()) && !(j->end())) {

            typename CollectionOperation::OperationType typeA = i->type();
            typename CollectionOperation::OperationType typeB = j->type();

            if (r.size() != 0) {
                if (r[r.size() - 1]->type() == CollectionOperation::OperationType::Match) {
                    for (int counter = 0; counter < dynamic_cast<MatchSequenceOperation<U>*>(r[r.size() - 1])->getQuantity(); counter++) {
                        std::cout << "M";
                    }
                }
                if (r[r.size() - 1]->type() == CollectionOperation::OperationType::Insert) {
                    std::cout << "I";
                }
                if (r[r.size() - 1]->type() == CollectionOperation::OperationType::Delete) {
                    std::cout << "D";
                }
                if (r[r.size() - 1]->type() == CollectionOperation::OperationType::Delta) {
                    std::cout << "d";
                }
                std::cout.flush();
            }


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


//                } else {
//                    std::vector<CollectionOperation*> r = std::vector<CollectionOperation*>();
//                    Delta<U>
//                }
//
//                r.push_back(new DeltaSequenceOperation<U>(m->delta()));
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
//                } else {
                    if (policy == ConflictPolicy::PreferA) {
                        r.push_back(opA);
                        i->next();
                    }
                    if (policy == ConflictPolicy::PreferB) {
                        r.push_back(opB);
                        j->next();
                    }
//                }

                continue;
            }

            if (typeA == CollectionOperation::OperationType::Match) {
                if (j->type() == CollectionOperation::Insert) {
                    r.push_back(j->get());
                    j->next();
                }
                if (j->type() == CollectionOperation::Delete){
                    r.push_back(j->get());
                    i->next();
                    j->next();
                }
                if (j->type() == CollectionOperation::Empty){
                    r.push_back(i->get());
                    i->next();
                    j->next();
                }
                if (j->type() == CollectionOperation::Delta){
                    r.push_back(j->get());
                    i->next();
                    j->next();
                }
                continue;
            }

            if (typeB == CollectionOperation::OperationType::Match) {
                if (i->type() == CollectionOperation::Insert) {
                    r.push_back(i->get());
                    i->next();
                }
                if (i->type() == CollectionOperation::Delete){
                    r.push_back(i->get());
                    i->next();
                    j->next();
                }
                if (i->type() == CollectionOperation::Empty){
                    r.push_back(j->get());
                    i->next();
                    j->next();
                }
                if (i->type() == CollectionOperation::Delta){
                    r.push_back(i->get());
                    i->next();
                    j->next();
                }
                continue;
            }

            if ((typeA == CollectionOperation::OperationType::Delete)) {
                if ((typeB == CollectionOperation::OperationType::Insert)) {
                    r.push_back(j->get());
                    j->next();
                }
                if ((typeB == CollectionOperation::OperationType::Delta)) {
                    r.push_back(j->get());
                    j->next();
                }
                continue;
            }

            if ((typeA == CollectionOperation::OperationType::Insert)) {
                if ((typeB == CollectionOperation::OperationType::Delete)) {
                    r.push_back(i->get());
                    i->next();
                }
                if ((typeB == CollectionOperation::OperationType::Delta)) {
                    r.push_back(i->get());
                    i->next();
                }

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