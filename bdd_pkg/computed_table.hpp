#ifndef COMPUTED_TABLE_HPP_
#define COMPUTED_TABLE_HPP_

#include <iostream>
#include <unordered_map>
#include <bdd_node.hpp>

using namespace std;

class computed_table
{
struct table_key
	{
	    bdd_node* f;
		bdd_node* g;
		bdd_node* h;

		bool operator==(const table_key& k) const
		{
			return (f == k.f && g == k.g && h == k.h);
		}
	};

	 struct table_hash
	 {
		std::size_t operator()(const table_key& k) const
		{
			std::size_t h;
			h = std::hash<bdd_node*>()(k.f);
			h = (h ^ std::hash<bdd_node*>()(k.g) << 1) >> 1;
			h = (h ^ std::hash<bdd_node*>()(k.h) << 1) >> 1;
			return  h ;
		}
	  };

	unordered_map<const table_key, bdd_node*, table_hash> table;

public:

	bdd_node* get_entry(bdd_node* f, bdd_node* g, bdd_node* h)
	{
		table_key key{f, g, h};
		auto element = table.find(key);

		if (element == table.end())
		{
			return nullptr;
		}
		else
		{
			return element->second;
		}
	}

	void add_entry(bdd_node* f, bdd_node* g, bdd_node* h, bdd_node* r)
	{
		table_key key{f, g, h};
		table.insert(std::pair<table_key, bdd_node*>(key, r));
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


#endif /* COMPUTED_TABLE_HPP_ */
