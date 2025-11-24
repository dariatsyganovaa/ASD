#ifndef LIB_DSU_DSU_H_
#define LIB_DSU_DSU_H_

#include <stdexcept>
#include <iostream> 

class DSU {
	int* _parent;
	int* _rank;
	size_t _size;
public:
	DSU(size_t size);
	DSU(const DSU&);
	~DSU();

	size_t size() const noexcept;
	const int* parent() const noexcept;
	const int* rank() const noexcept;

	void union_dsu(int x, int y);
	int find(int x);
	int find_rec(int x);

};

#endif  // LIB_DSU_DSU_H_