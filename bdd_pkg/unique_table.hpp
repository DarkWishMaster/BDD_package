#include <iostream>
#include <unordered_map>
#include <bdd_node.hpp>

#ifndef BDD_PKG_unique_table_HPP_
#define BDD_PKG_unique_table_HPP_

using namespace std;
/*
 * The unique tables maps triplets of (v, low, h) to F
 * where v    - variable index (x0, x1 ... xn)
 *       low  - pointer to low bdd
 *       high - pointer to high bdd
 *       F    - a function i.e a pointer to a BDD node in memory
 *       		with the (v, low, high) values
 */
/*
 * Note that hash table may contain a lot of dead nodes
 * TBD Garbage collection
 */
class unique_table
{
	struct table_key
	{
		uint32_t     index;
		bdd_node* low;
		bdd_node* high;

		bool operator==(const table_key& k) const
		{
			return (index == k.index && low == k.low && high == k.high);
		}
	};

	 struct table_hash
	 {
		std::size_t operator()(const table_key& k) const
		{
			std::size_t h;
			h = std::hash<uint32_t>()(k.index);
			h = (h ^ std::hash<bdd_node*>()(k.low) << 1) >> 1;
			h = (h ^ std::hash<bdd_node*>()(k.high) << 1) >> 1;
			return  h ;
		}
	  };

	unordered_map<const table_key, bdd_node*, table_hash> table;

public:

	bdd_node* find_or_add_unique(uint32_t v, bdd_node* low, bdd_node* high)
	{
		table_key key{v, low, high};
		auto element = table.find(key);

		if (element == table.end())
		{
			bdd_node* node = new bdd_node();
			node->index = v;
			node->low   = low;
			node->high  = high;
			table.insert(std::pair<const table_key, bdd_node*>(key, node));
			return node;
		}
		else
		{
			return element->second;
		}
	}

	uint32_t get_size()
	{
		return table.size();
	}

	float get_load_factor()
	{
		return table.load_factor();
	}

};


#endif /* BDD_PKG_unique_table_HPP_ */
