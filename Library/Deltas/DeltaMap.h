#pragma once

#include "Delta.h"

#include <vector>
#include <set>
#include <map>
#include "../Operations/MapOperation/MapOperation.h"

#include "Merges/MergeMap.h"

template <typename K, typename V>
class Delta<std::map<K, V>> : public IDelta<std::map<K, V>> {

public:

    typedef std::map<K, V> T;
    typedef MapOperation<K, V> CollectionOperation;

    Delta(T& initialState, T& finalState) : IDelta<T>(initialState, finalState) {

        this->ops = std::vector<CollectionOperation*>();

        T finalStateCopy = T(finalState);

        for (typename T::iterator i = initialState.begin(); i != initialState.end(); i++) {
            auto j = finalStateCopy.find(i->first); //std::find(finalStateCopy.begin(), finalStateCopy.end(), i->first);
            if (j != finalStateCopy.end()) {
                if (i->second == j->second) {
                    // match
                } else {
                    // modify
                    this->ops.push_back(new DeltaMapOperation<K, V>(i->first, new Delta<V>(i->second, j->second)));
                }
                finalStateCopy.erase(j);
            } else {
                // deleted
                this->ops.push_back(new DeleteMapOperation<K, V>(i->first, i->second));
            }
        }
        for (typename T::iterator i = finalStateCopy.begin(); i != finalStateCopy.end(); i++) {
            auto j = initialState.find(i->first);
            if (j == initialState.end()) {
                // inserted
                this->ops.push_back(new InsertMapOperation<K, V>(i->first, i->second));
            }
        }

    }

    Delta& operator=(const Delta& other) {
        this->ops = std::vector<CollectionOperation*>(other.ops);
        return *this;
    }

    Delta& operator=(const Delta&& other) {
        this->ops = std::move(other.ops);
        return *this;
    }

    T patch(T& initialState) override {

        T finalState(initialState);

        for (CollectionOperation* op : this->ops) {
            if (op->type() == CollectionOperation::OperationType::Delete) {
                finalState.erase(dynamic_cast<DeleteMapOperation<K, V>*>(op)->getKey());
            }
            if (op->type() == CollectionOperation::OperationType::Insert) {
                auto opE = dynamic_cast<InsertMapOperation<K, V>*>(op);
                finalState[opE->getKey()] = opE->getValue();
            }
            if (op->type() == CollectionOperation::OperationType::Delta) {
                auto opE = dynamic_cast<DeltaMapOperation<K, V>*>(op);
                finalState[opE->getKey()] = opE->getDelta().patch(finalState[opE->getKey()]);
            }
        }

        return finalState;

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

    }

public:

    Delta<T>* inverse() {

        std::vector<CollectionOperation*> reverseOps;

        for (CollectionOperation* op : this->ops) {
            if (op->type() == CollectionOperation::OperationType::Delete) {
                auto opE = dynamic_cast<DeleteMapOperation<K, V>*>(op);
                reverseOps.push_back(new InsertMapOperation<K, V>(op->getKey(), opE->getValue()));
            }
            if (op->type() == CollectionOperation::OperationType::Insert) {
                auto opE = dynamic_cast<InsertMapOperation<K, V>*>(op);
                reverseOps.push_back(new DeleteMapOperation<K, V>(op->getKey(), opE->getValue()));
            }
            if (op->type() == CollectionOperation::OperationType::Delta) {
                auto opE = dynamic_cast<DeltaMapOperation<K, V>*>(op);
                reverseOps.push_back(new DeltaMapOperation<K, V>(op->getKey(), opE->getDelta().inverse()));
            }
        }

        return new Delta<T>(reverseOps);

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
