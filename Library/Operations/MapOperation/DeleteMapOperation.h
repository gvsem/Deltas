#pragma once

#include <map>
#include "MapOperation.h"

template <class K, class V>
class InsertMapOperation;

template <class K, class V>
class DeleteMapOperation : public MapOperation<K, V> {

public:

    typedef std::map<K, V> T;

    DeleteMapOperation(K key, V& value): _key(key), _value(value) {

    }

    typename MapOperation<K, V>::OperationType type() override {
        return MapOperation<K, V>::OperationType::Delete;
    }

    std::string print() override {
        typename std::stringstream ss;
        ss << "Delete " << _key;
        return ss.str();
    }

    K getKey() override {
        return _key;
    }

    V& getValue() {
        return _value;
    }

    T patch(T& a)  {
        T newValue = T(a);
        newValue.erase(getKey());
        return newValue;
    }

    MapOperation<K, V>* clone() override {
        return new DeleteMapOperation(*this);
    }

protected:
    //InsertMapOperation() = default;
    DeleteMapOperation(DeleteMapOperation<K, V> const & ) = default;
    DeleteMapOperation& operator=(DeleteMapOperation<K, V> const & ) = default;

private:
    K _key;
    V _value;

};