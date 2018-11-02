#ifndef BDD_HPP_
#define BDD_HPP_

#include <iostream>
#include <cstdint>
#include <unordered_map>

using namespace std;


class bdd
{

public:
	uint32_t index;
	bdd* low;
	bdd* high;

	// leaf nodes
	static bdd bdd_one;
	static bdd bdd_zero;

public:
	enum class bdd_op {NOT, AND, OR};

	friend inline bool operator==(const bdd& f, const bdd& g)
	{
	    return (f.index == g.index && f.low == g.low && f.high == g.high);
	}

	bdd& operator=(const bdd& g)
	{
		this->index = g.index;
		this->low   = g.low;
		this->high  = g.high;

		return *this;
	}

	static void bdd_init(unsigned int num_var)
	{
		bdd_zero.index = num_var;
		bdd_zero.low = bdd_zero.high = nullptr;

		bdd_one.index  = num_var + 1;
		bdd_one.low = bdd_one.high = nullptr;
	}

	static bdd bdd_and(bdd& f, bdd& g);
	static bdd bdd_not(bdd& f, bdd& g);
	static bdd bdd_or(bdd& f, bdd& g);

	static bdd bdd_apply(bdd& f, bdd& g, bdd_op op);

	static bdd* ite(bdd* f,  bdd* g, bdd* h);

	friend ostream & operator << (ostream &out, const bdd &f)
	{
		cout << &f << " " << f.index << " " << f.low << " " << f.high << endl;
		return out;
	}



private:

	/*
	 * The unique tables maps triplets of (v, low, h) to F
	 * where v    - variable index (x0, x1 ... xn)
	 *       low  - pointer to low bdd
	 *       high - pointer to high bdd
	 *       F    - a function i.e a pointer to a BDD node in memory
	 *       		with the (v, low, high) values
	 */


	struct table_key
	{
		uint32_t index;
		bdd*     low;
		bdd*     high;

		bool operator==(const table_key& k) const
		{
			return (index == k.index && low == k.low && high == k.high);
		}
	};

	 struct table_hash
	  {
		std::size_t operator()(const table_key& k) const
		{
		  return std::hash<uint32_t>()(k.index);
		}
	  };

	static unordered_map<const table_key, bdd*, table_hash> unique_table;


	static bdd* find_or_add_unique(uint32_t v, bdd* low, bdd* high)
	{
		table_key key{v, low, high};
		auto element = unique_table.find(key);

		if (element == unique_table.end())
		{
			bdd* node = new bdd();
			node->index = v;
			node->low   = low;
			node->high  = high;
			unique_table.insert(std::pair<const table_key, bdd*>(key, node));
			return node;
		}
		else
		{
			return element->second;
		}
	}


};



#endif /* BDD_HPP_ */
