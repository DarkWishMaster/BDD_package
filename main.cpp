#include <iostream>
#include <token_reader.hpp>
#include <bdd.hpp>
#include <txt_test_reader.hpp>

using namespace std;

#include <bool_parser.hpp>
#include <test_input.hpp>

int main(int argc, char **argv) {

//	bool_parser bp;
//
//	bool_expr_rpn expr = bp.parse("!(x1*x2) + x3*!((x4 * !(x5*x2 + !x1*(!x6 + x3))) + x6");
//
//	cout << expr;
//
//	txt_data td = txt_data_reader::read("..\\txt_data\\test2_compund.txt");
//
//	for (auto it=td.var_order.begin(); it!=td.var_order.end(); ++it)
//	    std::cout << it->first << " => " << it->second << '\n';
//
//	for (auto item : td.sub_expressions)
//	{
//		cout << "name " << item.name << endl;
//		cout << bp.parse(item.expr) << endl;
//	}
//
//	cout << td.evaluate << endl;
//	cout << bp.parse(td.evaluate);

//	bdd::bdd_init(3);
//
//	bdd  a(0);
//	bdd  b(1);
//	bdd  c(2);
//
//
//	cout << "ZERO : " << bdd::bdd_zero << "ONE : " << bdd::bdd_one << endl;
//
//	cout << "computing ac" << endl;
//	bdd ac = bdd::ite(a,c, bdd::bdd_zero);
//	cout << "computing bc" << endl;
//	bdd bc = bdd::ite(b,c, bdd::bdd_zero);
//	cout << "computing r" << endl;
//	bdd r  = bdd::ite(ac, bdd::bdd_one, bc);
//
//	cout << "R" << endl << r;
//	cout << "RL" << endl << r.get_low();
//	cout << "RH" << endl << r.get_high();
//
//	cout << "RLL" << endl << r.get_low().get_low();
//	cout << "RLH" << endl << r.get_low().get_high();
//	cout << "RHL" << endl << r.get_high().get_low();
//	cout << "RHH" << endl << r.get_high().get_high();

//	test2();
//	test3();
//	test4();
	bdd_from_txt("..\\test_data\\test2_compund.txt").print();
}
