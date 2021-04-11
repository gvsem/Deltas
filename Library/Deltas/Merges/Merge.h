#pragma once

#include <Deltas/Delta.h>
#include "IMerge.h"


template <class T>
class Merge : public IMerge<T> {
public:

    Merge(Delta<T>& a, Delta<T>& b) {

    }

    bool hasSpecialization() {
        return false;
    }

protected:

    friend Delta<T>;

};

#include "MergeSet.h"
#include "MergeMultiset.h"
#include "MergeVector.h"