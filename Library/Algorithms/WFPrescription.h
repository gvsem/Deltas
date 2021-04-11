#pragma once

#include <vector>
#include <algorithm>
#include "../Operations/SequenceOperation/SequenceOperation.h"

#include "VectorDifferenceAlgorithm.h"

#define INF 1000000000

template <class T>
class Delta;

template <class T, class U>
class WFPrescription: public VectorDifferenceAlgorithm<T, U> {

public:

    // O ( a.size() * b.size() )
    WFPrescription(T& initial, T& final): a(initial), b(final) {
        this->calculate();
    }

    int size() override {
        return d[this->a.size()][this->b.size()];
    }

    std::vector<SequenceOperation<U>*>& getEditorialPrescription() override {

        //this->printTable();

        std::vector<SequenceOperation<U>*>* r = new std::vector<SequenceOperation<U>*>();

        for (int i = this->a.size(), j = this->b.size(); (i > 0) || (j > 0);) {

            char m = this->minimalOperation(i, j);

            if (m == 'D') {
                r->push_back(new DeleteSequenceOperation<U>(this->a[i - 1]));
                i--;
            } else if (m == 'I') {
                r->push_back(new InsertSequenceOperation<U>(this->b[j - 1]));
                j--;
            } else if (m == 'R') {
                if (this->a[i - 1] == this->b[j - 1]) {
                    r->push_back(new MatchSequenceOperation<U>(1));
                } else {
                    DeltaSequenceOperation<U>* d = new DeltaSequenceOperation<U>(this->a[i - 1], this->b[j - 1]);
                    if (d->getDelta().hasSpecialization()) {
                        r->push_back(d);
                    } else {
                        r->push_back(new DeleteSequenceOperation<U>(this->a[i - 1]));
                        r->push_back(new InsertSequenceOperation<U>(this->b[j - 1]));
                    }


                    //r->push_back(new DeltaSequenceOperation<U>(this->a[i - 1], this->b[j - 1]));
                    //r.push_back(new DeleteSequenceOperation<T>(s1));
                    //r.push_back(new InsertSequenceOperation<T>(s2));
                }
                i--;
                j--;
            }

        }

        std::reverse(r->begin(), r->end());

        return *r;

    }

    std::string printTable() {
        std::stringstream ss;
        for (int i = 0; i <= this->a.size(); i++) {
            for (int j = 0; j <= this->b.size(); j++) {
                ss << d[i][j] << " ";
            }
            ss << "\n";
        }
        return ss.str();
    }


private:

    int DeleteCost(size_t i, size_t j) {
        return (i >= 1) ? (d[i - 1][j] + 1) : INF; // D
    }

    int InsertCost(size_t i, size_t j) {
        return (j >= 1) ? (d[i][j - 1] + 1) : INF; // I
    }

    int ReplaceCost(size_t i, size_t j) {
        return ((i >= 1) && (j >= 1)) ? (d[i - 1][j - 1] + 2 * ((this->a[i - 1] == this->b[j - 1]) ? 0 : 1)) : INF; // R
    }

    size_t m(size_t i, size_t j) {
        return std::min(DeleteCost(i, j), std::min(InsertCost(i, j), ReplaceCost(i, j)));
    }

    char minimalOperation(size_t i, size_t j) {
        int m = this->m(i, j);
        if (ReplaceCost(i, j) == m) { return 'R'; }
        if (InsertCost(i, j) == m) { return 'I'; }
        if (DeleteCost(i, j) == m) { return 'D'; }
    }

    size_t D(size_t i, size_t j) {
        if (j > 0) {
            if (i > 0) {
                return this->m(i, j);
            }
            else {
                return j;
            }
        }
        else {
            if (i > 0) {
                return i;
            }
            else {
                return 0;
            }
        }
    }

    void calculate() {

        if (this->d.empty()) {
            this->d = std::vector<std::vector<int>>(this->a.size() + 1, std::vector<int>(this->b.size() + 1, 0));

            for (int i = 1; i <= this->a.size(); i++) {
                d[i][0] = i;
            }

            for (int j = 1; j <= this->b.size(); j++) {
                d[0][j] = j;
            }

            for (int j = 1; j <= this->b.size(); j++) {
                for (int i = 1; i <= this->a.size(); i++) {
                    d[i][j] = D(i, j);
                }
            }
        }

    }

    std::vector<std::vector<int>> d;
    T& a;
    T& b;

};