
//#include "..//Library/Deltas/Delta.h"
#include <library.h>
//#include "..//CPPDelta/SequenceDeltaFactory.h"

#include <vector>
#include <set>
#include <Algorithms/WFDifferenceAlgorithm.h>
#include "Contacts.h"

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

	std::cout << d->invert()->print();
	T g = d->invert()->patch(c);

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

	std::cout << d->invert()->print();
	T g = d->invert()->patch(c);

	for (auto a : g) {
		std::cout << a << " ";
	}

	demoDiff<T>(a, b);
}

void demoVectors() {

	typedef std::vector<int> T;

	std::vector<int> a = { 1, 2, 3, 4, 5 };
	std::vector<int> b = { 1, 3, 5, 4, 7 };

    Delta<T>* d = new Delta<T>();
    MyersDifferenceAlgorithm<T, int>::apply(a,b,*d);
	//Delta<std::vector<int>>* d = new Delta<std::vector<int>>(a, b);
	std::cout << d->print();
	std::vector<int> c = d->patch(a);

	for (auto a : c) {
		std::cout << a << " ";
	}
	std::cout << "\n";

	std::cout << d->invert()->print();
	std::vector<int> g = d->invert()->patch(c);

	for (auto a : g) {
		std::cout << a << " ";
	}

}




void threeSetsDemo() {

    typedef std::set<int> T;

    T a = { 1, 2, 3, 4, 5 };
    T b = { 1, 3, 4, 5, 7 };
    T c = { 2, 3, 4, 6, 7 };

    threeWayMerge<T>(a, b, c);

}

std::vector<char> s(std::string && s) {
    return std::vector<char>(s.begin(), s.end());
}


template <class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& o) {
    for (const T& v : o) {
        os << v << "/";
    }
    return os;
}


template <class T>
void print(T d) {
    for (auto s: d) {
        std::cout << s << " ";
    }
    std::cout << "\n";
}

void threeWayMergeMap() {

    typedef std::map<int, std::string> T;
    T a;
    a[1] = "a";
    a[2] = "b";
    a[3] = "c";

    T b;
    b[2] = "m";
    b[3] = "c";
    b[4] = "d";

    T c;
    c[1] = "m";
    c[2] = "c";
    c[3] = "d";
    c[4] = "e";

    T d = threeWayMerge<T>(a, b, c);
    for (auto v: d) {
        std::cout << v.first << " : " << v.second << "\n";
    }

}

void threeWayMergeText() {

    typedef std::vector<std::vector<char>> T;
    typedef std::vector<char> U;

    T a = {
            s("Good morning!"),
            s("How are you today?"),
            s("See you!"),
    };

    T b = {
            s("Good afternoon!"),
            s("How were you yesterday?"),
            s("See you!"),
    };

    T c = {
            s("Good evening!"),
            s("How are you tomorrow?"),
            s("See you soon!"),
    };

    std::cout << "\n";
    std::cout << "\n";

    Delta<T>* d1 = new Delta<T>(a, b, new WFDifferenceAlgorithm<T, U>(a, b));
    Delta<T>* d2 = new Delta<T>(a, c, new WFDifferenceAlgorithm<T, U>(a, c));
    //std::cout << d1->print();
    //std::cout << d2->print();
    Merge<T>* m = new Merge<T>(*d1, *d2);
    Delta<T>* d3 = m->delta();
    //std::cout << m->print();
    T d = d3->patch(a);

    //T d = threeWayMerge<T>(a, b, c);

    std::cout << "\n";
    std::cout << "\n";

    print<T>(d);

}

int main(int argv, char** args) {

    //threeSetsDemo();

   //threeWayMerge<std::>();

    //std::cout << deltaAC->print() << "\n";

    //demoVectors();

    threeWayMergeText();


    typedef Contact T;

    Contacts a = Contacts();
    Contacts b = Contacts();
    Contacts c = Contacts();
    Contacts d;

    a.addContact()
    .addName("Ivan")
    ->addName("Petrov")
    ->addPhone("+78882220920")
    ->addPhone("+76662220920")
    ->addPhone("+79992220920");

    std::cout << a.print() << "\n";

    b.addContact()
    .addName("Ivan")
    ->addName("Sergeevich")
    ->addName("Petrov")
    ->addPhone("+78882220920")
    ->addPhone("+79992220940");

    std::cout << b.print() << "\n";

    c.addContact()
    .addName("Ivan")
    ->addName("Petrov-Vodkin")
    ->addPhone("+78882220920")
    ->addPhone("+76662220920")
    ->addPhone("+79992220920")
    ->addPhone("+77772220920");

    std::cout << c.print() << "\n";


    Contacts ABC = threeWayMerge<Contacts>(a, b, c);
    std::cout << ABC.print();



//    Delta<T>* deltaAB = new Delta<T>(a, b, new WFDifferenceAlgorithm<T, std::vector<char>>(a,b));
//    std::cout << deltaAB->print();
//    std::cout << "done";
//
//    print<T>(a);
//    print<T>(b);
//    T c = deltaAB->patch(a);
//    print<T>(c);



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