#ifndef BDD_HPP_
#define BDD_HPP_

#include <iostream>
#include <iomanip>
#include <cstdint>
#include <unordered_map>
#include <bdd_node.hpp>
#include <unique_table.hpp>
#include <computed_table.hpp>
#include <unordered_set>
#include <chrono>

using namespace std;

using milliseconds = std::chrono::duration<float, std::ratio<1, 1000>> ;

typedef struct bdd_stats_s
{
	uint32_t     ite_calls;
	uint32_t     ite_terminals;
	milliseconds ite_time_total;
} bdd_stats;


class bdd
{

private:
	bdd_node* root;

	static unique_table*   unique_tb;
	static computed_table* computed_tb;
	static uint32_t num_var;
	static unordered_map<uint32_t, string>* map_var;

public:

	// leaf nodes
	static bdd bdd_one;
	static bdd bdd_zero;

	enum class bdd_op {NOT, AND, OR};

	bdd();
	bdd(uint32_t index);

	bdd_node* get_root();
	uint32_t  get_index();
	string    get_var();

	bdd get_low();
	bdd get_high();

	bool empty();

	void print();

	friend inline bool operator==(const bdd& f, const bdd& g);
	bdd& operator=(const bdd& g);


	static void bdd_init(uint32_t num_var, unordered_map<string, uint32_t>& var_order);
	static void bdd_exit();


	static bdd bdd_not(bdd f);
	static bdd bdd_and(bdd f, bdd g);
	static bdd bdd_or(bdd f, bdd g);
	static bdd bdd_imp(bdd f, bdd g);
	static bdd bdd_xor(bdd f, bdd g);
	static bdd bdd_eq(bdd f, bdd g);



	static bdd ite(bdd f,  bdd g, bdd h);
	static string get_var(bdd_node* node);



private:
	static bdd_node* ite(bdd_node* f,  bdd_node* g, bdd_node* h);




private:
	static bdd_stats stats;

	static void reset_stats()
	{
		stats.ite_calls      = 0;
		stats.ite_terminals  = 0;
		stats.ite_time_total = milliseconds(0);
	}

public:
	static void print_stats()
	{
		cout << "Vars: " << setw(4) << num_var << "  ";
		cout << "ITE:  " << setw(6) << stats.ite_calls << "  ";
		cout << setw(7) << stats.ite_terminals << "  ";
		cout << setw(6) << stats.ite_time_total.count() << " ms" << endl;
	}
};


inline bool operator==(const bdd& f, const bdd& g)
{
	return (f.root == g.root);
}


#endif /* BDD_HPP_ */
