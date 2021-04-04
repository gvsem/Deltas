#pragma once

#include <Deltas/Delta.h>
#include "IMerge.h"


template <class T>
class Merge : public IMerge<T> {

protected:

    friend Delta<T>;

};

#include "MergeSet.h"
#include "MergeMultiset.h"
#include "MergeVector.h"