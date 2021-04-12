#pragma once

#include <vector>

class MyersTree {

public:

	MyersTree(int capacity) {
		this->tree = std::vector<std::vector<std::pair<int, EditorialGraphReason>>>();
		this->resize(capacity);
	}

	enum EditorialGraphReason {
		Undefined,
		Deletion,
		Insertion
	};

	std::pair<int, EditorialGraphReason>& at(int i, int j) {

		if (i >= this->capacity()) {
			this->resize(i + 1);
		}

		if (i == 0) {
			if (j == 1) {
				return _cell;
			}
		}

		if (i > 0) {
			return this->tree.at(i - 1).at((j - (1 - i)) / 2); // [i - 1] [(j - (1 - i)) / 2] ;
		}

		//assert(false);
		return _cell;
	}

protected:

	// make tree available from index 0 to depth
	void resize(int depth) {
		int n = tree.size();
		int s = depth - n;
		for (int i = 0; i < s; i++) {
			int newTreeIndex = n + i;
			tree.push_back(std::vector<std::pair<int, EditorialGraphReason>>(newTreeIndex + 1, std::pair<int, EditorialGraphReason>(0, EditorialGraphReason::Undefined)));
			tree[newTreeIndex].reserve(newTreeIndex + 1);
		}
	}

	int capacity() {
		return tree.size() + 1;
	}

private:

	// 0 .. to MAXD + 1
	std::vector<std::vector<std::pair<int, EditorialGraphReason>>> tree;
	std::pair<int, EditorialGraphReason> _cell = std::make_pair(0, Undefined);

};