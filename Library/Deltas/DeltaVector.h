#pragma once

#include "Delta.h"

#include <vector>
#include "../Algorithms/EditorialPrescription.h"


    template <typename U>
    class Delta<std::vector<U>> : public IDelta<std::vector<U>> {

    public:

        typedef std::vector<U> T;
        typedef SequenceOperation<U> CollectionOperation;

        Delta(T& initialState, T& finalState) : IDelta<std::vector<U>>(initialState, finalState) {

            EditorialPrescription<T, U> * sdf = new EditorialPrescription<T, U>(initialState, finalState);
            std::vector<SequenceOperation<U>*> o = std::vector<SequenceOperation<U>*>(sdf->getEditorialPrescription());

            this->ops = o;

            //TODO: add Delta modify operation
            //for (i = 0; i < o.size(); i++) {
            //	if (i + 1 < o.size()) {
            //		this->ops.push_back(new Modify)
            //	}
            //	else {
            //		this->ops.push_back(o[i]);
            //	}
            //}
            //
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

            }

            return s;
        }

        std::string print() override {

            typename std::stringstream ss;
            for (auto op : ops) {
                ss << op->print() << "\n";
            }
            return ss.str();

        }

    private:

        Delta(std::vector<SequenceOperation<U>*> _ops) : ops(_ops) {

        }

    public:

        Delta<T> * reverse() override {
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
            }

            return new Delta<T>(reverseOps);
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

        std::vector<CollectionOperation*> getOperations() {
            std::vector<CollectionOperation*> r;
            for (CollectionOperation* op : this->ops) {
                r.push_back(op->clone());
            }

            return r;
        }

        friend class Merge<T>;

    };

