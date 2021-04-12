#include <gtest/gtest.h>
#include "library.h"
#include "CommonTemplatedTests.cpp"

#include <set>


TEST(MultisetDelta, StableToObjectModification) {

    typedef std::multiset<int> T;
    T a = { 1, 2, 2, 2, 3, 4, 5 };
    T b = { 1, 2, 3, 5, 5, 7 };
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

TEST(MultisetDelta, DeltaReversePatching) {

    typedef std::multiset<int> T;
    T a = { 1, 2, 2, 2, 3, 4, 5 };
    T b = { 1, 2, 3, 5, 5, 7 };

    Delta<T>* deltaAB = new Delta<T>(a, b);
    T c = deltaAB->patch(a);
    ASSERT_EQ(b, c);

    Delta<T>* deltaBA = deltaAB->invert();
    T d = deltaBA->patch(c);
    ASSERT_EQ(a, d);

}


TEST(MultisetDelta, ThreeWayMerge) {

    typedef std::multiset<int> T;
    T a = { 1, 2, 2, 2, 3, 4, 5 };
    T b = { 1, 2, 3, 5, 5, 7 };
    T c = { 0, 2, 2, 3, 5, 6 };

    T d_correct_PreferA = {0, 2, 3, 5, 5, 6, 7};
    T d_correct_PreferB = {0, 2, 2, 3, 5, 5, 6, 7};
    T d_correct_Insert = {0, 2, 2, 3, 5, 5, 6, 7};
    T d_correct_Delete = {0, 2, 3, 5, 5, 6, 7};

    Delta<T>* deltaAB = new Delta<T>(a, b);
    Delta<T>* deltaAC = new Delta<T>(a, c);
    Merge<T>* mergeABC = deltaAB->merge(*deltaAC);

    Delta<T>* deltaAD_PreferA = mergeABC->delta(Merge<T>::ConflictPolicy::PreferA);
    Delta<T>* deltaAD_PreferB = mergeABC->delta(Merge<T>::ConflictPolicy::PreferB);
    Delta<T>* deltaAD_Insert = mergeABC->delta(Merge<T>::ConflictPolicy::ConsolidateInsertions);
    Delta<T>* deltaAD_Delete = mergeABC->delta(Merge<T>::ConflictPolicy::ConsolidateDeletions);

    ASSERT_EQ(deltaAD_PreferA->patch(a), d_correct_PreferA);
    ASSERT_EQ(deltaAD_PreferB->patch(a), d_correct_PreferB);
    ASSERT_EQ(deltaAD_Insert->patch(a), d_correct_Insert);
    ASSERT_EQ(deltaAD_Delete->patch(a), d_correct_Delete);

}