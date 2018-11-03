#include "doctest.h"
#include <test_input.hpp>
#include <bdd.hpp>

TEST_CASE("Simple expression from test1.txt")
{
	bdd F = bdd_from_txt("G:\\Workspace\\Eclipse\\BDD_package\\test_data\\txt\\test1.txt");

	CHECK(F.empty() != true);

	F.print();

	bdd::bdd_exit();

}



