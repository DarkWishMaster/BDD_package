#include <iostream>
#include <token_reader.hpp>


using namespace std;

#include <bool_parser.hpp>

int main(int argc, char **argv) {

	bool_parser bp;

	bool_expr_rpn expr = bp.parse("!(x1*x2) + x3*!(x4 * !(x5*x2 + !x1*(!x6 + x3))) + x6");

	cout << expr;

//	token_reader tr("!(x1*x2) + x3*!(x4 * !(x5*x2 + !x1*(!x6 + x3))) + x6");
//
//	int i = 0;
//
//	while (tr.has_tokens())
//	{
//		i++;
//		if (i > 50) break;
//		token_reader::token t = tr.next_token();
//		cout << t.name << " ";
//	}




}
