#include "doctest.h"
#include <test_input.hpp>
#include <test_utils.hpp>
#include <bdd.hpp>

// TBD check number of satisfying assignments and their vector
// TBD test_node pure 0 or pure 1 (no edges)

TEST_CASE("Simple expression from test1.txt")
{
	bdd F = bdd_from_txt("G:\\Workspace\\Eclipse\\BDD_package\\test_data\\txt\\test1.txt");

	REQUIRE(F.empty() != true);


	test_nodes expected;
	expected.add_test_node("x1", "x3", "x2");
	expected.add_test_node("x2", "x3", "1");
	expected.add_test_node("x3", "1", "x5");
	expected.add_test_node("x5", "1", "x6");
	expected.add_test_node("x6", "1", "0");

	check_expected(F, expected);

	bdd::bdd_exit();
}

TEST_CASE("Complex expression from test2.txt")
{
	bdd F = bdd_from_txt("G:\\Workspace\\Eclipse\\BDD_package\\test_data\\txt\\test2.txt");

	REQUIRE(F.empty() != true);

	test_nodes expected;
	expected.add_test_node("x1", "x3", "x2");
	expected.add_test_node("x2", "x3", "1");
	expected.add_test_node("x3", "1", "x5");
	expected.add_test_node("x3", "1", "x5");
	expected.add_test_node("x5", "1", "x6");
	expected.add_test_node("x5", "1", "x6");
	expected.add_test_node("x6", "1", "0");
	expected.add_test_node("x6", "1", "x7");
	expected.add_test_node("x7", "x8", "0");
	expected.add_test_node("x8", "x9", "0");
	expected.add_test_node("x9", "x10", "1");
	expected.add_test_node("x10", "0", "1");

	check_expected(F, expected);

	bdd::bdd_exit();
}

TEST_CASE("Bad variable ordering from test3.txt")
{
	bdd F = bdd_from_txt("G:\\Workspace\\Eclipse\\BDD_package\\test_data\\txt\\test3.txt");

	REQUIRE(F.empty() != true);

	test_nodes expected;
	expected.add_test_node("x1", "x3", "x3");
	expected.add_test_node("x3", "x5", "x5");
	expected.add_test_node("x3", "x5", "x5");
	expected.add_test_node("x5", "x7", "x7");
	expected.add_test_node("x5", "x7", "x7");
	expected.add_test_node("x5", "x7", "x7");
	expected.add_test_node("x5", "x7", "x7");
	expected.add_test_node("x7", "x2", "x2");
	expected.add_test_node("x7", "x2", "x2");
	expected.add_test_node("x7", "x2", "x2");
	expected.add_test_node("x7", "x4", "x4");
	expected.add_test_node("x7", "x6", "x6");
	expected.add_test_node("x7", "x4", "x4");
	expected.add_test_node("x7", "x2", "x2");
	expected.add_test_node("x7", "0", "x8");
	expected.add_test_node("x2", "x4", "1");
	expected.add_test_node("x2", "x4", "1");
	expected.add_test_node("x2", "x4", "1");
	expected.add_test_node("x2", "x6", "1");
	expected.add_test_node("x2", "x6", "1");
	expected.add_test_node("x2", "x4", "1");
	expected.add_test_node("x2", "x8", "1");
	expected.add_test_node("x2", "0", "1");
	expected.add_test_node("x4", "x6", "1");
	expected.add_test_node("x4", "x6", "1");
	expected.add_test_node("x4", "x8", "1");
	expected.add_test_node("x4", "0", "1");
	expected.add_test_node("x6", "x8", "1");
	expected.add_test_node("x6", "0", "1");
	expected.add_test_node("x8", "0", "1");


	check_expected(F, expected);

	bdd::bdd_exit();
}

TEST_CASE("Same as test3.txt but with good variable ordering from test4.txt")
{
	bdd F = bdd_from_txt("G:\\Workspace\\Eclipse\\BDD_package\\test_data\\txt\\test4.txt");

	REQUIRE(F.empty() != true);

	test_nodes expected;
	expected.add_test_node("x1", "x3", "x2");
	expected.add_test_node("x2", "x3", "1");
	expected.add_test_node("x3", "x5", "x4");
	expected.add_test_node("x4", "x5", "1");
	expected.add_test_node("x5", "x7", "x6");
	expected.add_test_node("x6", "x7", "1");
	expected.add_test_node("x7", "0", "x8");
	expected.add_test_node("x8", "0", "1");

	check_expected(F, expected);

	bdd::bdd_exit();
}





