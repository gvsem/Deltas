#pragma once

#include <string>
#include <sstream>

#include "../IOperation.h"

template <class K, class V>
class MapOperation: public IOperation<V> {

public:

    enum OperationType {
        Empty,
        Insert,
        Delete,
        Delta
    };

    virtual MapOperation<K, V>::OperationType type() {
        return MapOperation<K, V>::OperationType::Empty;
    }

    virtual MapOperation<K, V>* clone() = 0;

    virtual K getKey() = 0;

protected:

    MapOperation() = default;
    MapOperation(MapOperation<K, V> const & ) = default;
    MapOperation& operator=(MapOperation<K, V> const & ) = default;

};

#include "InsertMapOperation.h"
#include "DeleteMapOperation.h"
#include "DeltaMapOperation.h"

