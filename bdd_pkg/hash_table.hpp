#include <iostream>
#include <unordered_map>
#include <bdd_node.hpp>

#ifndef BDD_PKG_HASH_TABLE_HPP_
#define BDD_PKG_HASH_TABLE_HPP_

using namespace std;
/*
 * The unique tables maps triplets of (v, low, h) to F
 * where v    - variable index (x0, x1 ... xn)
 *       low  - pointer to low bdd
 *       high - pointer to high bdd
 *       F    - a function i.e a pointer to a BDD node in memory
 *       		with the (v, low, high) values
 */
class hash_table
{
	struct table_key
	{
		uint32_t     index;
		bdd_node_ptr low;
		bdd_node_ptr high;

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

	unordered_map<const table_key, bdd_node_ptr, table_hash> table;

public:
	bdd_node_ptr find_or_add_unique(uint32_t v, bdd_node_ptr low, bdd_node_ptr high)
	{
		table_key key{v, low, high};
		auto element = table.find(key);

		if (element == table.end())
		{
//			cout << "Key not found, adding: " << endl;
//			cout << v << " " << low << " " << high << endl;
			bdd_node_ptr node = new bdd_node();
			node->index = v;
			node->low   = low;
			node->high  = high;
			table.insert(std::pair<const table_key, bdd_node_ptr>(key, node));
			return node;
		}
		else
		{
//			cout << "Key found, returning: " << endl;
//			cout << v << " " << low << " " << high << endl;
			return element->second;
		}
	}

	void clear()
	{
		for ( auto it = table.begin(); it != table.end(); ++it )
		{
			delete it->second;
		}
		table.clear();
	}

};


#endif /* BDD_PKG_HASH_TABLE_HPP_ */
