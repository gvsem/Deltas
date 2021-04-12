#pragma once

#include <map>
#include "MapOperation.h"

template <class K, class V>
class DeleteMapOperation;

template <class K, class V>
class InsertMapOperation : public MapOperation<K, V> {
    
public:
    
    typedef std::map<K, V> T;

    InsertMapOperation(K key, V& value): _key(key), _value(value) {

    }

    typename MapOperation<K, V>::OperationType type() override {
        return MapOperation<K, V>::OperationType::Insert;
    }

    std::string print() override {
        typename std::stringstream ss;
        ss << "Insert " << _value;
        return ss.str();
    }

    K getKey() override {
        return _key;
    }
    
    V& getValue() {
        return _value;
    }

    T patch(T& a) {
        T newValue = T(a);
        newValue[this->getKey()] = getValue();
        return newValue;
    }

    MapOperation<K, V>* clone() override {
        return new InsertMapOperation(*this);
    }

protected:
    //InsertMapOperation() = default;
    InsertMapOperation(InsertMapOperation<K, V> const & ) = default;
    InsertMapOperation& operator=(InsertMapOperation<K, V> const & ) = default;

private:
    K _key;
    V _value;

};