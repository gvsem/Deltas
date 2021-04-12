#pragma once

#include "MyersTree.h"
#include "../Operations/SequenceOperation/SequenceOperation.h"

#include <algorithm>
#include <iostream>

//template <class T>
//class Delta;
//#include "Delta.h"

#include "IDifferenceAlgorithm.h"

#define DEFAULT_MYERS_D 50
#define INF 1000000000

template <class T, class U>
class MyersDifferenceAlgorithm: public IDifferenceAlgorithm<T, U> {

public:

    MyersDifferenceAlgorithm(T& initial, T& final) : _initial(initial), _final(final) {
        this->maxD = DEFAULT_MYERS_D;
    }

	MyersDifferenceAlgorithm(T& initial, T& final, int d) : _initial(initial), _final(final), maxD(d) {
		this->maxD = std::max(5, d);
	}

    static void apply(T& initialState, T& finalState, Delta<T>& delta) {
        MyersDifferenceAlgorithm<T, U> a = MyersDifferenceAlgorithm<T, U>(initialState, finalState);
        delta.fill(a.getEditorialPrescription());
    }

    std::vector<SequenceOperation<U>*>& getEditorialPrescription() override {
        this->calculate();
        return this->ops;
    }

    int size() override {
        this->calculate();
        return ops.size();
    }

	std::string print() override {
		typename std::stringstream ss;
		for (auto op : ops) {
			ss << op->print() << "\n";
		}
		return ss.str();
	}

protected:

	void calculate() {

	    if (ops.size() != 0){
	        return;
	    }

		if (_initial.size() == 0) {
			for (auto v : _final) {
				this->ops.push_back(new InsertSequenceOperation<U>(v));
			}
			return;
		}

		if (_final.size() == 0) {
			for (auto v : _initial) {
				this->ops.push_back(new DeleteSequenceOperation<U>(v));
			}
			return;
		}

		MyersTree M(maxD);

		int finalI = -1;
		int finalK = INF;

		int x, y;
		for (int d = 0; (d <= maxD) && (finalK == INF); d++) {
			for (int k = -d; k <= d; k += 2) {

				if ((k == -d) || ((k != d) && (M.at(d, k - 1).first < M.at(d, k + 1).first))) {
					x = M.at(d, k + 1).first; // insert
					M.at(d + 1, k).second = MyersTree::EditorialGraphReason::Insertion; //M.at(d, k + 1).second;
				}
				else {
					x = M.at(d, k - 1).first + 1; // delete
					M.at(d + 1, k).second = MyersTree::EditorialGraphReason::Deletion; //M.at(d, k - 1).second;
				}

				y = x - k;

				while ((x < this->_initial.size()) && (y < this->_final.size()) && (this->_initial[x] == this->_final[y])) {
					x++; y++;
				}

				M.at(d + 1, k).first = x;

				if ((x >= this->_initial.size()) && (y >= this->_final.size())) {
					finalI = d + 1;
					finalK = k;
					break;
				}

			}

		}

		int k = finalK;
		for (int d = finalI; d >= 1; d--) {

			int matches = 0;
			if (M.at(d, k).second == MyersTree::EditorialGraphReason::Deletion) {
				matches = M.at(d, k).first - M.at(d - 1, k - 1).first - 1;
			}
			else if (M.at(d, k).second == MyersTree::EditorialGraphReason::Insertion) {
				matches = M.at(d, k).first - M.at(d - 1, k + 1).first;
			}

			int matchQuantity = 0;
			int j = M.at(d, k).first;
			while ((j > 0) && (matches > 0) && (j - 1 - k >= 0) && (j != INF) && (this->_initial[j - 1] == this->_final[j - 1 - k])) {
				matchQuantity++;
				j--;
				matches--;
			}

			if ((j == 0) && (d == 1)) {
				if (matchQuantity != 0) {
					ops.push_back(new MatchSequenceOperation<U>(matchQuantity));
				}
				continue;
			}

			if ((M.at(d, k).second == MyersTree::EditorialGraphReason::Deletion) && (M.at(d - 1, k - 1).first != INF)) {
				if (j - 1 == M.at(d - 1, k - 1).first) {
					if (matchQuantity != 0) {
						ops.push_back(new MatchSequenceOperation<U>(matchQuantity));
					}
					ops.push_back(new DeleteSequenceOperation<U>(this->_initial[j - 1]));
					k--;
					continue;
				}
			}

			if ((M.at(d, k).second == MyersTree::EditorialGraphReason::Insertion) && (M.at(d - 1, k + 1).first != INF)) {
				if (j == M.at(d - 1, k + 1).first) {
					if (matchQuantity != 0) {
						ops.push_back(new MatchSequenceOperation<U>(matchQuantity));
					}
					ops.push_back(new InsertSequenceOperation<U>(this->_final[j - k - 1]));
					k++;
					continue;
				}
			}

		}

		std::reverse(ops.begin(), ops.end());

	}

private:

	T& _initial;
	T& _final;
	int maxD;

	std::vector<SequenceOperation<U>*> ops;

};