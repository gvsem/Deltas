#pragma once

#include <map>
#include <Deltas/Delta.h>
#include "MapOperation.h"


template <class K, class V>
class DeltaMapOperation : public MapOperation<K, V> {

public:

    typedef std::map<K, V> T;

    DeltaMapOperation(K key, Delta<V>* delta): _key(key), _delta(delta) {

    }

    typename MapOperation<K, V>::OperationType type() override {
        return MapOperation<K, V>::OperationType::Delta;
    }

    std::string print() override {
        typename std::stringstream ss;
        ss << "Delta " << _delta->print();
        return ss.str();
    }

    K getKey() override {
        return _key;
    }

    Delta<V>& getDelta() {
        return *_delta;
    }

    T patch(T& a)  {
        T newValue = T(a);
        newValue[this->getKey()] = _delta->patch(newValue[this->getKey()]);
        return newValue;
    }

    MapOperation<K, V>* clone() override {
        return new DeltaMapOperation(*this);
    }

protected:
    //DeltaMapOperation() = default;
    DeltaMapOperation(DeltaMapOperation<K, V> const & ) = default;
    DeltaMapOperation& operator=(DeltaMapOperation<K, V> const & ) = default;

private:
    K _key;
    Delta<V>* _delta;

};