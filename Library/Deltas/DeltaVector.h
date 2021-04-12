#pragma once

#include "Delta.h"

#include <vector>
#include <vector>
#include <iostream>
#include <string>
#include "Algorithms/MyersDifferenceAlgorithm.h"
#include "Algorithms/WFDifferenceAlgorithm.h"

//template <typename U>
//class Delta<std::vector<U>,  MyersDifferenceAlgorithm<std::vector<U>, U>> : public IDelta<std::vector<U>> {
//
//};

#define DefaultDifferenceAlgorithm MyersDifferenceAlgorithm<T,U>

    template <typename U>
    class Delta<std::vector<U>> : public IDelta<std::vector<U>> {

    public:

        typedef std::vector<U> T;
        typedef SequenceOperation<U> CollectionOperation;

        Delta() {}


        Delta(T& initialState, T& finalState) : Delta<std::vector<U>>(initialState, finalState, new DefaultDifferenceAlgorithm(initialState, finalState)) {

        }

        Delta(T& initialState, T& finalState, IDifferenceAlgorithm<T, U>* algorithm) : IDelta<std::vector<U>>(initialState, finalState) {
            IDifferenceAlgorithm<T, U>* sdf = algorithm;
            std::vector<SequenceOperation<U>*> o = std::vector<SequenceOperation<U>*>(sdf->getEditorialPrescription());

            this->ops = std::vector<SequenceOperation<U>*>();
            std::vector<SequenceOperation<U>*> buffD = std::vector<SequenceOperation<U>*>();
            std::vector<SequenceOperation<U>*> buffI = std::vector<SequenceOperation<U>*>();

            for (auto v : o) {
                if (v->type() == SequenceOperation<U>::OperationType::Match) {
                    for (auto u : buffD) {
                        this->ops.push_back(u);
                    }
                    buffD.clear();
                    for (auto u : buffI) {
                        this->ops.push_back(u);
                    }
                    buffI.clear();
                    this->ops.push_back(v);
                }
                if (v->type() == SequenceOperation<U>::OperationType::Delta) {
//                    Merge<U> m = new Merge<U>();
//                    if (m.hasSpecialization()) {
//                        this->ops.push_back(v);
//                    } else {
//
//                    }

                    for (auto u : buffD) {
                        this->ops.push_back(u);
                    }
                    buffD.clear();
                    for (auto u : buffI) {
                        this->ops.push_back(u);
                    }
                    buffI.clear();
                    this->ops.push_back(v);
                }
                if (v->type() == SequenceOperation<U>::OperationType::Insert) {
                    buffI.push_back(v);
                }
                if (v->type() == SequenceOperation<U>::OperationType::Delete) {
                    buffD.push_back(v);
                }

            }

            for (auto u : buffD) {
                this->ops.push_back(u);
            }
            buffD.clear();
            for (auto u : buffI) {
                this->ops.push_back(u);
            }
            buffI.clear();

            //this->ops = o;

        }

        Delta& operator=(const Delta& other) {
            this->ops = std::vector<SequenceOperation<U>*>(other.ops);
            return *this;
        }

        Delta& operator=(const Delta&& other) {
            this->ops = std::move(other.ops);
            return *this;
        }

        T patch(T& initialState) override {

            //T finalState;

            //int i = 0;
            //for (SequenceOperation<U>* op : ops) {
            //	if (op->type() == SequenceOperation<U>::OperationType::Match) {
            //		int matches = dynamic_cast<MatchSequenceOperation<U>*>(op)->getQuantity();
            //		for (int j = 0; j < matches; j++) {
            //			finalState.push_back(initialState[i]);
            //			i++;
            //		}
            //	}
            //	if (op->type() == SequenceOperation<U>::OperationType::Insert) {
            //		U& u = dynamic_cast<InsertSequenceOperation<U>*>(op)->getValue();
            //		finalState.push_back(u);
            //		i += 1;
            //	}
            //	if (op->type() == SequenceOperation<U>::OperationType::Delete) {
            //		i += 1;
            //	}
            //}

            // return finalState;

            std::vector<U> s(initialState);

            typename std::vector<U>::iterator i = s.begin();

            for (SequenceOperation<U>* j : ops) {

                //if (DEBUG_PRINT_OPERATIONS_STEP_BY_STEP) {
                //	for (auto p = initialState->t->begin(); p != initialState->t->end(); p++) {
                //		std::cout << (*p) << ((p - initialState->t->begin() == i - initialState->t->begin()) ? " <- " : "") << "\n";
                //	}
                //	std::cout << "\n";
                //}

                if (j->type() == SequenceOperation<U>::OperationType::Match) {
                    i += dynamic_cast<MatchSequenceOperation<U>*>(j)->getQuantity();
                }

                if (j->type() == SequenceOperation<U>::OperationType::Delete) {
                    size_t k = i - s.begin();
                    s.erase(i);
                    i = s.begin() + (k);
                }

                if (j->type() == SequenceOperation<U>::OperationType::Insert) {
                    size_t k = i - s.begin();
                    s.insert(i, dynamic_cast<InsertSequenceOperation<U>*>(j)->getValue());
                    i = s.begin() + (k + 1);
                }

                if (j->type() == SequenceOperation<U>::OperationType::Delta) {
                    size_t k = i - s.begin();
                    *i = j->patch(*i);
                    i = s.begin() + (k + 1);
                }

            }

            return s;
        }

        std::string print() override {

            typename std::stringstream ss;
            for (auto op : ops) {
//                if (op->type() == CollectionOperation::Match) {
//                    for (int i = 0; i < dynamic_cast<MatchSequenceOperation<U>*>(op)->getQuantity(); i++) {
//                        ss << "M";
//                    }
//                }
//                if (op->type() == CollectionOperation::Insert) {
//                    ss << "I";
//                }
//                if (op->type() == CollectionOperation::Delete) {
//                    ss << "D";
//                }

                ss << op->print() << "\n";
            }
            //ss << "\n";
            return ss.str();

        }

    private:

        Delta(std::vector<SequenceOperation<U>*> _ops) : ops(_ops) {

        }

    public:

        Delta<T> * invert()  {
            std::vector<SequenceOperation<U>*> reverseOps;

            for (SequenceOperation<U>* op : ops) {
                if (op->type() == SequenceOperation<U>::OperationType::Match) {
                    reverseOps.push_back(new MatchSequenceOperation<U>(dynamic_cast<MatchSequenceOperation<U>*>(op)->getQuantity()));
                }
                if (op->type() == SequenceOperation<U>::OperationType::Insert) {
                    reverseOps.push_back(new DeleteSequenceOperation<U>(dynamic_cast<InsertSequenceOperation<U>*>(op)->getValue()));
                }
                if (op->type() == SequenceOperation<U>::OperationType::Delete) {
                    reverseOps.push_back(new InsertSequenceOperation<U>(dynamic_cast<DeleteSequenceOperation<U>*>(op)->getValue()));
                }
                if (op->type() == SequenceOperation<U>::OperationType::Delta) {
                    reverseOps.push_back(dynamic_cast<DeltaSequenceOperation<U>*>(op)->getReverseOperation());
                }
            }

            return new Delta<T>(reverseOps);
        }

        Delta<T>* clone() {
            return new Delta<T>(this->getOperations());
        }

        Merge<T>* merge(Delta<T>& other) {
            return new Merge<T>(*this, other);
        }

        ~Delta() {
            for (SequenceOperation<U>* op : ops) {
                delete op;
            }
        }

    protected:
        std::vector<SequenceOperation<U>*> ops;

        void fill(std::vector<CollectionOperation*>& operations) {
            this->ops = operations;
        }

        std::vector<CollectionOperation*> getOperations() {
            std::vector<CollectionOperation*> r;
            for (CollectionOperation* op : this->ops) {
                r.push_back(op->clone());
            }
            return r;
        }

        friend class Merge<T>;
        friend class MyersDifferenceAlgorithm<T, U>;
        friend class WFDifferenceAlgorithm<T, U>;

    };

