#ifndef TESTS_TEST_UTILS_HPP_
#define TESTS_TEST_UTILS_HPP_

#include <string>
#include <bdd.hpp>
#include <unordered_set>

class test_nodes
{

	struct node
	{
		string v;
		string LO;
		string HI;
	};

private:
	/* maps variable names to the variable names of low and high children
	 * e.g x1 -> x2, x3
	 */
	unordered_multiset<string>  nodes;

public:
	void add_test_node(string v, string LO, string HI)
	{
		string node = v + " " + LO + " " + HI;
		nodes.insert(node);
	}

	/*
	 * Find the node x1-> x2, x3 and remove it from the map.
	 * returns true on success, false if not found.
	 */
	bool find_and_remove(string v, string LO, string HI)
	{
		string node = v + " " + LO + " " + HI;
		auto itr = nodes.find(node);
		if(itr != nodes.end()) {
			nodes.erase(itr);
			return true;
		}

		return false;
	}

	vector<struct node> get_nodes()
	{
		vector<struct node> result;
		for (auto triplet : nodes)
		{
			result.push_back(split_triplet(triplet));
		}

		return result;
	}

private:
	struct node split_triplet(string triplet)
	{
		struct node result;
		istringstream iss(triplet);
		getline(iss, result.v, ' ');
		getline(iss, result.LO, ' ');
		getline(iss, result.HI, ' ');

		return result;
	}
};

static void compare_dfs(bdd_node* r, unordered_set<bdd_node*>& visited, test_nodes& nodes)
{
	bool is_visited = false;
	if (visited.find(r) != visited.end())
	{
		is_visited = true;
	}
	else
	{
		visited.insert(r);
	}

	if (r != nullptr && !is_visited &&
			r != bdd::bdd_one.get_root() && r != bdd::bdd_zero.get_root())
	{
		string v     = bdd::get_var(r);
		string l     = bdd::get_var(r->low);
		string h     = bdd::get_var(r->high);
		bool is_edge = nodes.find_and_remove(v, l, h);

		if (!is_edge)
		{
			string msg = "Edge " + v + " -> " + l + ", " + h + " should not be present";
			FAIL_CHECK(msg);
		}

		compare_dfs(r->low, visited, nodes);
		compare_dfs(r->high, visited, nodes);
	}
}

void check_expected(bdd& F, test_nodes& nodes)
{
	unordered_set<bdd_node*> visited;
	compare_dfs(F.get_root(), visited, nodes);

	/* Check for remaining nodes that were not present in BDD */
	for (auto node : nodes.get_nodes())
	{
		string msg = "Node " + node.v + " -> " + node.LO + ", " + node.HI + " not present in BDD.";
		FAIL_CHECK(msg);
	}
}

#endif /* TESTS_TEST_UTILS_HPP_ */
