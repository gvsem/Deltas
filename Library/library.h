#ifndef DELTAS_LIBRARY_H
#define DELTAS_LIBRARY_H

// void hello();

#include "Deltas/Delta.h"


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


#endif //DELTAS_LIBRARY_H