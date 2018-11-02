#ifndef BDD_HPP_
#define BDD_HPP_

#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <bdd_node.hpp>
#include <hash_table.hpp>

using namespace std;


class bdd
{

public:
	bdd_node_ptr root;

	static hash_table unique_table;

public:
	// leaf nodes
	static bdd bdd_one;
	static bdd bdd_zero;

public:
	enum class bdd_op {NOT, AND, OR};

	bdd()
	{
		this->root = nullptr;
	}

	bdd(uint32_t index)
	{
		this->root = unique_table.find_or_add_unique(index, bdd_zero.root, bdd_one.root);
	}

	bdd get_low()
	{
		bdd b;
		b.root = this->root->low;
		return b;
	}

	bdd get_high()
	{
		bdd b;
		b.root = this->root->high;
		return b;
	}

	friend inline bool operator==(const bdd& f, const bdd& g)
	{
	    return (f.root == g.root);
	}

	bdd& operator=(const bdd& g)
	{
		this->root = g.root;
		return *this;
	}

	static void bdd_init(unsigned int num_var)
	{
		bdd_zero.root = unique_table.find_or_add_unique(num_var,     nullptr, nullptr);
		bdd_one.root  = unique_table.find_or_add_unique(num_var + 1, nullptr, nullptr);
	}

	static void bdd_exit()
	{
		unique_table.clear();
		bdd_zero.root = nullptr;
		bdd_one.root  = nullptr;
	}

	static bdd bdd_apply(bdd& f, bdd& g, bdd_op op);

	static bdd bdd_not(bdd f);
	static bdd bdd_and(bdd f, bdd g);
	static bdd bdd_or(bdd f, bdd g);

	static bdd_node_ptr ite(bdd_node_ptr f,  bdd_node_ptr g, bdd_node_ptr h);
	static bdd ite(bdd f,  bdd g, bdd h);

	friend ostream & operator << (ostream &out, const bdd &f)
	{
		cout << f.root << " " << f.root->index << " " <<
				f.root->low << " " << f.root->high << endl;
		return out;
	}

	void print()
	{
		cout << *this;
		print_dfs("L", this->root->low);
		print_dfs("H", this->root->high);
	}

private:
	void print_dfs(string path, bdd_node_ptr r)
	{
		if (r != nullptr)
		{
			cout << path << " " << r << " " << r->index << " " << r->low << " " << r->high << endl;
			print_dfs(path+"L", r->low);
			print_dfs(path+"H", r->high);
		}
	}


};



#endif /* BDD_HPP_ */
