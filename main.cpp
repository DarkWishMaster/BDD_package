#include <iostream>
#include <token_reader.hpp>

#include <test_data_reader.hpp>

using namespace std;

#include <bool_parser.hpp>

int main(int argc, char **argv) {

	bool_parser bp;

	bool_expr_rpn expr = bp.parse("!(x1*x2) + x3*!(x4 * !(x5*x2 + !x1*(!x6 + x3))) + x6");

	cout << expr;

	test_data td = test_data_reader::read("..\\test_data\\test2_compund.txt");

	for (auto it=td.var_order.begin(); it!=td.var_order.end(); ++it)
	    std::cout << it->first << " => " << it->second << '\n';

	for (auto item : td.sub_expressions)
	{
		cout << "name " << item.name << endl;
		cout << bp.parse(item.expr) << endl;
	}

	cout << td.evaluate << endl;
	cout << bp.parse(td.evaluate);

}
