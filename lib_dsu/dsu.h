#ifndef LIB_DSU_DSU_H_
#define LIB_DSU_DSU_H_

#include <stdexcept>
#include <iostream> 

// добавить модификацию сжатия путей
class DSU {
	// множество элементов {0, 1, 2, ..., size}
	int* _parent; // "массив родителей"
	int* _rank;
	size_t _size;
public:
	DSU(size_t size);
	DSU(const DSU&);
	~DSU();

	void dsu_union(int x, int y);
	int find(int x);
	int find_rec(int x);

};

DSU::DSU(size_t size) {

}

void DSU::dsu_union(int x, int y) {
	if (x >= _size || y >= _size || x < 0 || y < 0) {
		throw std::invalid_argument("");
	}

	if (x == y) return;

	int parent_x = find(x);
	int parent_y = find(y);

	if (_rank[parent_x] >= _rank[parent_y]) {
		_parent[parent_y] = parent_x;
	}

	else if (_rank[parent_x] < _rank[parent_y]) {
		_parent[parent_x] = parent_y;
	}

	if (_rank[parent_x] == _rank[parent_y]) {
		_rank[parent_x]++;
	}

	_parent[parent_y] = parent_x;
}

int DSU::find(int x) {
	if (x >= _size || x < 0) {
		throw std::invalid_argument("");
	}

	while (x != _parent[x]) {
		x = _parent[x];
	}

	return x;
}

int DSU::find_rec(int x) {
	if (x >= _size || x < 0) {
		throw std::invalid_argument("");
	}

	if (x == _parent[x]) {
		return x;
	}

	return x = find(_parent[x]);
}

#endif  // LIB_DSU_DSU_H_