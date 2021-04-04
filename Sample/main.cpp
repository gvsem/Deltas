
//#include "..//Library/Deltas/Delta.h"
#include <library.h>
//#include "..//CPPDelta/SequenceDeltaFactory.h"

#include <vector>
#include <set>

//using namespace CPPDelta;

template <class T>
void demoDiff(T& a, T& b) {

	Delta<T>* d = new Delta<T>(a, b);
	std::cout << d->print();

	T c = d->patch(a);

	for (auto a : c) {
		std::cout << a << " ";
	}
	std::cout << "\n";

	std::cout << d->reverse()->print();
	T g = d->reverse()->patch(c);

	for (auto a : g) {
		std::cout << a << " ";
	}

}

void demoSets() {
	std::set<int> a = { 1, 2, 3, 4, 5 };
	std::set<int> b = { 1, 3, 5, 4, 7 };

	demoDiff<std::set<int>>(a, b);
}

void demoStrings() {
	
	typedef std::vector<char> T;

	std::string str1 = "Good morning, everyone! My name is Ivan.";
	std::string str2 = "Good evening, every! My surname is Ivanov.";
	T a(str1.begin(), str1.end());
	T b(str2.begin(), str2.end());

	Delta<T>* d = new Delta<T>(a, b);
	std::cout << d->print();
	T c = d->patch(a);

	for (auto a : c) {
		std::cout << a << " ";
	}
	std::cout << "\n";

	std::cout << d->reverse()->print();
	T g = d->reverse()->patch(c);

	for (auto a : g) {
		std::cout << a << " ";
	}

	demoDiff<T>(a, b);
}

void demoVectors() {

	typedef std::vector<int> T;

	std::vector<int> a = { 1, 2, 3, 4, 5 };
	std::vector<int> b = { 1, 3, 5, 4, 7 };

	Delta<std::vector<int>>* d = new Delta<std::vector<int>>(a, b);
	std::cout << d->print();
	std::vector<int> c = d->patch(a);

	for (auto a : c) {
		std::cout << a << " ";
	}
	std::cout << "\n";

	std::cout << d->reverse()->print();
	std::vector<int> g = d->reverse()->patch(c);

	for (auto a : g) {
		std::cout << a << " ";
	}

}

template <class T>
void print(T d) {
    for (auto s: d) {
        std::cout << s << " ";
    }
    std::cout << "\n";
}

template <class T>
T threeWayMerge(T a, T b, T c) {

    Delta<T>* d1 = new Delta<T>(a, b);
    Delta<T>* d2 = new Delta<T>(a, c);
    //std::cout << d1->print();
    //std::cout << d2->print();
    Merge<T>* m = d1->merge(*d2);
    Delta<T>* d3 = m->delta();
    //std::cout << m->print();
    T result = d3->patch(a);

    //print<T>(a);
    //print<T>(b);
    //print<T>(c);
    //print<T>(result);

    return result;

}

void threeSetsDemo() {

    typedef std::set<int> T;

    T a = { 1, 2, 3, 4, 5 };
    T b = { 1, 3, 4, 5, 7 };
    T c = { 2, 3, 4, 6, 7 };

    threeWayMerge<T>(a, b, c);

}

int main(int argv, char** args) {

    //threeSetsDemo();

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


	//demoSets();
	//demoStrings();
	

	//for (auto )
	//assert(b == c);

	//Delta<Contacts> ...;

	//Delta<Deltable> ...;

	// Delta<std::string>(v1, v2)
	// Delta<std::string>

	return 0;
}