#pragma once

#include "Delta.h"

#include <vector>
#include <set>
#include <map>
#include "../Operations/SetOperation/SetOperation.h"

#include "Merges/MergeSet.h"

template <typename U, typename V>
class Delta<std::map<U, V>> : public IDelta<std::map<U, V>> {

public:

    typedef std::map<U, V> T;
    typedef SetOperation<U> CollectionOperation;

    Delta(T& initialState, T& finalState) : IDelta<T>(initialState, finalState) {

        this->ops = std::vector<CollectionOperation*>();

        this->counts = std::map<U, int>();
        for (typename T::iterator i = initialState.begin(); i != initialState.end(); i++) {
            this->counts[*i]++;
        }
        for (typename T::iterator i = finalState.begin(); i != finalState.end(); i++) {
            this->counts[*i]--;
        }

        for (std::pair<U, int> p : this->counts) {
            if (p.second > 0) {
                this->ops.push_back(new DeleteSetOperation<U>(p.first));
            }
            else if (p.second < 0) {
                this->ops.push_back(new InsertSetOperation<U>(p.first));
            }
        }

    }

    Delta& operator=(const Delta& other) {
        this->ops = std::vector<CollectionOperation*>(other.ops);
        this->counts = std::map<U, int>(other.counts);
        return *this;
    }

    Delta& operator=(const Delta&& other) {
        this->ops = std::move(other.ops);
        this->counts = std::move(other.counts);
        return *this;
    }

    T patch(T& initialState) override {

        T finalState(initialState);

        for (CollectionOperation* op : this->ops) {
            if (op->type() == CollectionOperation::OperationType::Delete) {
                finalState.erase(finalState.find(dynamic_cast<DeleteSetOperation<U>*>(op)->getValue()));
            }
            if (op->type() == CollectionOperation::OperationType::Insert) {
                finalState.insert(dynamic_cast<InsertSetOperation<U>*>(op)->getValue());
            }
        }

        return finalState;
    }

    bool hasSpecialization() override {
        return true;
    }

    std::string print() override {

        typename std::stringstream ss;
        for (auto op : this->ops) {
            ss << op->print() << "\n";
        }
        return ss.str();

    }


private:

    Delta(std::vector<CollectionOperation*> _ops): ops(_ops) {
        this->counts = std::map<U, int>();
        for (CollectionOperation* op : _ops) {
            if (op->type() == CollectionOperation::OperationType::Delete) {
                this->counts[dynamic_cast<DeleteSetOperation<U>*>(op)->getValue()]--;
            }
            if (op->type() == CollectionOperation::OperationType::Insert) {
                this->counts[dynamic_cast<InsertSetOperation<U>*>(op)->getValue()]++;
            }
        }
    }

    Delta(std::vector<CollectionOperation*> _ops,  std::map<U, int> _counts) : ops(_ops), counts(_counts) {

    }

public:

    Delta<T>* reverse() override {

        std::vector<CollectionOperation*> reverseOps;

        for (CollectionOperation* op : this->ops) {
            if (op->type() == CollectionOperation::OperationType::Delete) {
                reverseOps.push_back(new InsertSetOperation<U>(dynamic_cast<DeleteSetOperation<U>*>(op)->getValue()));
            }
            if (op->type() == CollectionOperation::OperationType::Insert) {
                reverseOps.push_back(new DeleteSetOperation<U>(dynamic_cast<InsertSetOperation<U>*>(op)->getValue()));
            }
        }

        std::map<U, int> reverseCounts(this->counts);
        for (typename std::map<U, int>::iterator it = reverseCounts.begin(); it != reverseCounts.end(); it++) {
            it->second = (it->second) * (-1);
        }

        return new Delta<T>(reverseOps, counts);

    }


    Delta<T>* clone() {
        return new Delta<T>(this->getOperations());
    }

    Merge<T>* merge(Delta<T>& other) {
        return new Merge<T>(*this, other);
    }

    ~Delta() {
        for (CollectionOperation* op : ops) {
            delete op;
        }
    }

protected:
    std::vector<CollectionOperation*> ops;
    std::map<U, int> counts;

    std::vector<CollectionOperation*> getOperations() {
        std::vector<CollectionOperation*> r;
        for (CollectionOperation* op : this->ops) {
            //auto uptr = op->clone();
            r.push_back(op->clone());
            // TODO: seg
            //uptr.release();
        }

        return r;
    }

    friend class Merge<T>;

};
