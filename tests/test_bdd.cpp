#include "doctest.h"
#include <bdd.hpp>
#include <unordered_map>

TEST_CASE("BDD Info")
{
	unordered_map<string, uint32_t> var_map;

	var_map["x1"] = 0;
	var_map["x2"] = 1;
	bdd::bdd_init(2, var_map);

	bdd f;

	cout << "Size of BDD instance " << sizeof(f) << " bytes" << endl;
	cout << "Size of BDD node "     << sizeof(bdd_node) << " bytes" << endl;

}





