#include <gtest/gtest.h>
#include "library.h"
#include "CommonTemplatedTests.cpp"

#include <set>

template<class T>
void print(T&& s) {
    for (auto v : s) {
        std::cout << v;
    }
    std::cout << "\n";
}


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

    Delta<T>* deltaBA = deltaAB->invert();
    T d = deltaBA->patch(c);
    ASSERT_EQ(a, d);

}

//
TEST(VectorDelta, ThreeWayMerge1) {


    typedef std::vector<char> T;
    std::string str1 = "Good morning, everyone! My name is Ivan.";
    std::string str2 = "Good eveening, every! My surname is Ivanov!";
    std::string str3 = "It is good morning today, everyone! My name is, however, Ivan.";
    std::string str4_PreferA = "It is good eveening today, every! My surname is, however, Ivanov!";
    std::string str4_PreferB = "It is good eveening today, every! My surname is, however, Ivanov!";

    //M       MMMMDDDIIIIMMMM      MMMMMMMDDDMMMMMIIIMMMMMMM M         MMMMDIII
    //DIIIIIIIMMMMMMM    MMMMIIIIIIMMMMMMMMMMMMMMM   MMMMMMMIMIIIIIIIIIMMMMM
    //DIIIIIIIMMMMDDDIIIIMMMMIIIIIIMMMMMMMDDDMMMMMIIIMMMMMMMIMIIIIIIIIIMMMMDIII

    T a(str1.begin(), str1.end());
    T b(str2.begin(), str2.end());
    T c(str3.begin(), str3.end());
    T d_PreferA(str4_PreferA.begin(), str4_PreferA.end());
    T d_PreferB(str4_PreferB.begin(), str4_PreferB.end());

    Delta<T>* deltaAB = new Delta<T>(a, b);
    Delta<T>* deltaAC = new Delta<T>(a, c);
    //std::cout << deltaAB->print() << "\n";
    //std::cout << deltaAC->print() << "\n";
    Merge<T>* mergeABC = deltaAB->merge(*deltaAC);
    //Delta<T>* deltaAD = mergeABC->delta();

    Delta<T>* deltaAD_PreferA = mergeABC->delta(Merge<T>::ConflictPolicy::PreferA);
    Delta<T>* deltaAD_PreferB = mergeABC->delta(Merge<T>::ConflictPolicy::PreferB);
    //std::cout << deltaAD->print() << "\n";

    ASSERT_EQ(deltaAD_PreferA->patch(a), d_PreferA);
    ASSERT_EQ(deltaAD_PreferB->patch(a), d_PreferB);

}


TEST(VectorDelta, ThreeWayMerge2_Conflict) {


    typedef std::vector<char> T;
    std::string str1 = "Good morning, everyone! My name is Ivan. Bye!";
    std::string str2 = "Good eveening, every! My surname is Ivanov! Stay calm! Bye!";
    std::string str3 = "It is good morning today, everyone! My name is, however, Ivan. Stay soft! Bye!";
    std::string str4_PreferA = "It is good eveening today, every! My surname is, however, Ivanov! Stay calm! Stay soft! Bye!";
    std::string str4_PreferB = "It is good eveening today, every! My surname is, however, Ivanov! Stay soft! Stay calm! Bye!";

    //M       MMMMDDDIIIIMMMM      MMMMMMMDDDMMMMMIIIMMMMMMM M         MMMMDIII
    //DIIIIIIIMMMMMMM    MMMMIIIIIIMMMMMMMMMMMMMMM   MMMMMMMIMIIIIIIIIIMMMMM
    //DIIIIIIIMMMMDDDIIIIMMMMIIIIIIMMMMMMMDDDMMMMMIIIMMMMMMMIMIIIIIIIIIMMMMDIII

    T a(str1.begin(), str1.end());
    T b(str2.begin(), str2.end());
    T c(str3.begin(), str3.end());
    T d_PreferA(str4_PreferA.begin(), str4_PreferA.end());
    T d_PreferB(str4_PreferB.begin(), str4_PreferB.end());

    Delta<T>* deltaAB = new Delta<T>(a, b);
    Delta<T>* deltaAC = new Delta<T>(a, c);
    //std::cout << deltaAB->print() << "\n";
    //std::cout << deltaAC->print() << "\n";
    Merge<T>* mergeABC = deltaAB->merge(*deltaAC);
    //Delta<T>* deltaAD = mergeABC->delta();

    Delta<T>* deltaAD_PreferA = mergeABC->delta(Merge<T>::ConflictPolicy::PreferA);
    Delta<T>* deltaAD_PreferB = mergeABC->delta(Merge<T>::ConflictPolicy::PreferB);
    //std::cout << deltaAD->print() << "\n";

    print<T>(deltaAD_PreferA->patch(a));
    print<T>(deltaAD_PreferB->patch(a));
    ASSERT_EQ(deltaAD_PreferA->patch(a), d_PreferA);
    ASSERT_EQ(deltaAD_PreferB->patch(a), d_PreferB);

}