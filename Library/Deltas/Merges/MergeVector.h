#pragma once

#include "Merge.h"
#include <set>
#include <Operations/SequenceOperation/MatchSequenceOperation.h>
//#include <Operations/SequenceOperation/SequenceOperation.h>

#include "../Delta.h"

template <class T>
class PrescriptionIterator;

template <class U>
class PrescriptionIterator<std::vector<U>> {
public:

    typedef std::vector<U> T;
    typedef typename Delta<T>::CollectionOperation CollectionOperation;

    PrescriptionIterator(std::vector<CollectionOperation*>& _operations) : operations(_operations) {
        this->i = operations.begin();
    }

    typename CollectionOperation::OperationType type() {
        return (*i)->type();
    }

    bool end() {
        return i == operations.end();
    }

    T& get() {
        return *i;
    }

    void next(int k = 1) {
        count += k;
        if (this->type() == CollectionOperation::OperationType::Match) {
            MatchSequenceOperation<T>* op = dynamic_cast<MatchSequenceOperation<T>*>(*i);
            if (op->getQuantity() >= count) {
                i++;
                count = 0;
            }
        } else {
            i++;
        }

    }

    int getQuantity() {
        return dynamic_cast<MatchSequenceOperation<T>*>(*i)->getQuantity();
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


    Delta<T>* delta() override {

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

        PrescriptionIterator<T>* i = new PrescriptionIterator<T>(this->operationsA);
        PrescriptionIterator<T>* j = new PrescriptionIterator<T>(this->operationsB);

        while (!(i->end()) || !(j->end())) {

            while((i->type() == CollectionOperation::OperationType::Match) && (i->type() == j->type())) {
                int m = std::min(i->getQuantity(), j->getQuantity());
                r.push_back(new MatchSequenceOperation<T>(m));
                i->next(m);
                j->next(m);
            }

            // TODO: continue


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


protected:

    Merge(Delta<T>& a, Delta<T>& b) {
        this->operationsA = a.getOperations();
        this->operationsB = b.getOperations();
    }

    std::vector<CollectionOperation*> operationsA;
    std::vector<CollectionOperation*> operationsB;

    friend class Delta<T>;

};