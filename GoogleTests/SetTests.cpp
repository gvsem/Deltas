#include <gtest/gtest.h>
#include "library.h"
#include "CommonTemplatedTests.cpp"

#include <set>


TEST(SetDelta, StableToObjectModification) {

    typedef std::set<int> T;
    T a = { 1, 2, 3, 4, 5 };
    T b = { 1, 3, 5, 4, 7 };
    T aCopy = a;

    Delta<T>* deltaAB = new Delta<T>(a, b);
    T c = deltaAB->patch(aCopy);
    a.insert(6);
    a.insert(45);
    a.insert(-4);
    a.erase(a.find(3));
    T d = deltaAB->patch(aCopy);

    ASSERT_EQ(c, d);

}

TEST(SetDelta, DeltaReversePatching) {

    typedef std::set<int> T;
    T a = { 1, 2, 3, 4, 5 };
    T b = { 1, 3, 5, 4, 7 };

    Delta<T>* deltaAB = new Delta<T>(a, b);
    T c = deltaAB->patch(a);
    ASSERT_EQ(b, c);

    Delta<T>* deltaBA = deltaAB->reverse();
    T d = deltaBA->patch(c);
    ASSERT_EQ(a, d);

}


TEST(SetDelta, ThreeWayMerge) {

    typedef std::set<int> T;
    T a = { 1, 2, 3, 4, 5 };
    T b = { 1, 3, 4, 5, 7 };
    T c = { 0, 2, 3, 5, 6 };
    T d_correct = {0, 3, 5, 6, 7};

    Delta<T>* deltaAB = new Delta<T>(a, b);
    Delta<T>* deltaAC = new Delta<T>(a, c);
    Merge<T>* mergeABC = deltaAB->merge(*deltaAC);
    Delta<T>* deltaAD = mergeABC->delta();

    T d = deltaAD->patch(a);
    ASSERT_EQ(d, d_correct);

}