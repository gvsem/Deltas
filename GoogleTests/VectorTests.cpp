#include <gtest/gtest.h>
#include "library.h"
#include "CommonTemplatedTests.cpp"

#include <set>


TEST(VectorDelta, StableToObjectModification) {

    typedef std::vector<char> T;
    std::string str1 = "Good morning, everyone! My name is Ivan.";
    std::string str2 = "Good evening, every! My surname is Ivanov.";
    std::string str3 = "La-La-La-La!";
    T a(str1.begin(), str1.end());
    T b(str2.begin(), str2.end());
    T aCopy = a;

    Delta<T>* deltaAB = new Delta<T>(a, b);
    T c = deltaAB->patch(aCopy);
    a = T(str3.begin(), str3.end());
    T d = deltaAB->patch(aCopy);

    ASSERT_EQ(c, d);

}

TEST(VectorDelta, DeltaReversePatching) {

    typedef std::vector<char> T;
    std::string str1 = "Good morning, everyone! My name is Ivan.";
    std::string str2 = "Good evening, every! My surname is Ivanov.";
    T a(str1.begin(), str1.end());
    T b(str2.begin(), str2.end());

    Delta<T>* deltaAB = new Delta<T>(a, b);
    T c = deltaAB->patch(a);
    ASSERT_EQ(b, c);

    Delta<T>* deltaBA = deltaAB->reverse();
    T d = deltaBA->patch(c);
    ASSERT_EQ(a, d);

}

//
TEST(VectorDelta, ThreeWayMerge) {

    typedef std::vector<char> T;
    std::string str1 = "Good morning, everyone! My name is Ivan.";
    std::string str2 = "Good evening, every! My surname is Ivanov!";
    std::string str3 = "It is good morning today, everyone! My name is, however, Ivan.";
    std::string str4 = "It is good evening today, every! My surname is, however, Ivanov!";

    //G         ood morevening,          everyone   ! My surname is           Ivanov.
    //M         MMMMDDDIIIMMMMM         MMMMMMDDD   MMMMMIIIMMMMMMM M         MMMMIIM
    // GIt is g ood m   orning today,    everyone   ! My    name is, however, Ivan  .
    // DIIIIIII MMMM M   MMMMMMIIIIIIM   MMMMMMMMM   MMMMM   MMMMMMMIMIIIIIIIIIMMMM  M
    
    T a(str1.begin(), str1.end());
    T b(str2.begin(), str2.end());
    T c(str3.begin(), str3.end());

    Delta<T>* deltaAB = new Delta<T>(a, b);
    Delta<T>* deltaAC = new Delta<T>(a, c);
    std::cout << deltaAB->print() << "\n";
    std::cout << deltaAC->print() << "\n";

    Merge<T>* mergeABC = deltaAB->merge(*deltaAC);
    Delta<T>* deltaAD = mergeABC->delta();
    
//    T d_correct_PreferA = {0, 2, 3, 5, 5, 6, 7};
//    T d_correct_PreferB = {0, 2, 2, 3, 5, 5, 6, 7};
//    T d_correct_Insert = {0, 2, 2, 3, 5, 5, 6, 7};
//    T d_correct_Delete = {0, 2, 3, 5, 5, 6, 7};

//    Delta<T>* deltaAD_PreferA = mergeABC->delta(Merge<T>::ConflictPolicy::PreferA);
//    Delta<T>* deltaAD_PreferB = mergeABC->delta(Merge<T>::ConflictPolicy::PreferB);
//    Delta<T>* deltaAD_Insert = mergeABC->delta(Merge<T>::ConflictPolicy::ConsolidateInsertions);
//    Delta<T>* deltaAD_Delete = mergeABC->delta(Merge<T>::ConflictPolicy::ConsolidateDeletions);
//
//    ASSERT_EQ(deltaAD_PreferA->patch(a), d_correct_PreferA);
//    ASSERT_EQ(deltaAD_PreferB->patch(a), d_correct_PreferB);
//    ASSERT_EQ(deltaAD_Insert->patch(a), d_correct_Insert);
//    ASSERT_EQ(deltaAD_Delete->patch(a), d_correct_Delete);

}