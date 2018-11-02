#ifndef BDD_HPP_
#define BDD_HPP_

#include <iostream>
#include <iomanip>
#include <cstdint>
#include <unordered_map>
#include <bdd_node.hpp>
#include <hash_table.hpp>
#include <unordered_set>

using namespace std;


class bdd
{

private:
	bdd_node* root;
	static hash_table unique_table;

public:

	// leaf nodes
	static bdd bdd_one;
	static bdd bdd_zero;

	enum class bdd_op {NOT, AND, OR};

	bdd();
	bdd(uint32_t index);

	bdd_node* get_root();
	uint32_t  get_index();

	bdd get_low();
	bdd get_high();

	bool empty();

	friend inline bool operator==(const bdd& f, const bdd& g);
	bdd& operator=(const bdd& g);


	static void bdd_init(unsigned int num_var);
	static void bdd_exit();
	static bdd bdd_not(bdd f);
	static bdd bdd_and(bdd f, bdd g);
	static bdd bdd_or(bdd f, bdd g);
	static bdd ite(bdd f,  bdd g, bdd h);

	void print();

private:
	static bdd_node* ite(bdd_node* f,  bdd_node* g, bdd_node* h);


};



#endif /* BDD_HPP_ */
