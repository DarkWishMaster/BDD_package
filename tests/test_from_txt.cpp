#include "doctest.h"
#include <test_input.hpp>
#include <test_utils.hpp>
#include <bdd.hpp>

// TBD check number of satisfying assignments and their vector
// TBD test_node pure 0 or pure 1 (no edges)

TEST_CASE("Test 1. Simple expression")
{
	bdd F = bdd_from_txt("G:\\Workspace\\Eclipse\\BDD_package\\test_data\\txt\\test01.txt");

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

TEST_CASE("Test 2. Complex expression")
{
	bdd F = bdd_from_txt("G:\\Workspace\\Eclipse\\BDD_package\\test_data\\txt\\test02.txt");

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

TEST_CASE("Test 3. Bad variable ordering from")
{
	bdd F = bdd_from_txt("G:\\Workspace\\Eclipse\\BDD_package\\test_data\\txt\\test03.txt");

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

TEST_CASE("Test 4. Same as Test 3 but with good variable ordering from")
{
	bdd F = bdd_from_txt("G:\\Workspace\\Eclipse\\BDD_package\\test_data\\txt\\test04.txt");

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

TEST_CASE("Test 5. Constant false")
{
	bdd F = bdd_from_txt("G:\\Workspace\\Eclipse\\BDD_package\\test_data\\txt\\test05.txt");

	REQUIRE(F.empty() != true);

	CHECK(F == bdd::bdd_zero);

	bdd::bdd_exit();
}

TEST_CASE("Test 6. Constant true")
{
	bdd F = bdd_from_txt("G:\\Workspace\\Eclipse\\BDD_package\\test_data\\txt\\test06.txt");

	REQUIRE(F.empty() != true);

	CHECK(F == bdd::bdd_one);

	bdd::bdd_exit();
}

TEST_CASE("Test 7. All operators")
{
	bdd F = bdd_from_txt("G:\\Workspace\\Eclipse\\BDD_package\\test_data\\txt\\test07.txt");

	REQUIRE(F.empty() != true);

	test_nodes expected;
	expected.add_test_node("x1", "x2", "x4");
	expected.add_test_node("x2", "x4", "x3");
	expected.add_test_node("x3", "x4", "x4");
	expected.add_test_node("x4", "x5", "x5");
	expected.add_test_node("x4", "x5", "x5");
	expected.add_test_node("x5", "x6", "0");
	expected.add_test_node("x5", "0", "x6");
	expected.add_test_node("x6", "0", "1");

	check_expected(F, expected);

	bdd::bdd_exit();
}

TEST_CASE("Test 8. Test implication associativity")
{
	bdd F = bdd_from_txt("G:\\Workspace\\Eclipse\\BDD_package\\test_data\\txt\\test08.txt");

	REQUIRE(F.empty() != true);

	test_nodes expected;
	expected.add_test_node("x1", "1", "x2");
	expected.add_test_node("x2", "1", "x3");
	expected.add_test_node("x3", "1", "x4");
	expected.add_test_node("x4", "0", "1");

	check_expected(F, expected);

	bdd::bdd_exit();
}

TEST_CASE("Test 9. Test constants in expressions")
{
	bdd F = bdd_from_txt("G:\\Workspace\\Eclipse\\BDD_package\\test_data\\txt\\test09.txt");

	REQUIRE(F.empty() != true);

	test_nodes expected;
	expected.add_test_node("x1", "1", "x2");
	expected.add_test_node("x2", "x3", "1");
	expected.add_test_node("x3", "0", "1");

	check_expected(F, expected);

	bdd::bdd_exit();
}





