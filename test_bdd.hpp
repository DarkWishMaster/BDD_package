#ifndef TEST_BDD_HPP_
#define TEST_BDD_HPP_

#include <iostream>
#include <assert.h>
#include <test_data_reader.hpp>
#include <stack>
#include <bdd.hpp>
#include <bool_parser.hpp>
#include <unordered_map>

using namespace std;

bdd rpn_to_bdd(unordered_map<string, bdd>& bdd_map, bool_expr_rpn& bool_expr)
{
	auto tokens = bool_expr.get_tokens();
	stack<bdd> bdd_stack;

	for (auto token : tokens)
	{
		if (token.type == token_type::SYMBOL)
		{
			auto from_map = bdd_map.find(token.name);

			if (from_map == bdd_map.end())
			{
				// not found in map
				cout << "Symbol " << token.name << " not in the map => ERROR" << endl;
				bdd result;
				return result;

			}
			cout << "Symbol " << token.name << "pushed" << endl;
			bdd_stack.push(from_map->second);
		}
		else if (token.type == token_type::OPERATOR)
		{
			cout << "Operator processed " << endl;
			bdd op1;
			bdd op2;
			switch (token.op)
			{
				case token_reader::bool_op::NOT:
					op1 = bdd_stack.top();
					bdd_stack.pop();
					bdd_stack.push(bdd::bdd_not(op1));
					break;
				case token_reader::bool_op::AND:
					op1 = bdd_stack.top();
					bdd_stack.pop();
					op2 = bdd_stack.top();
					bdd_stack.pop();
					bdd_stack.push(bdd::bdd_and(op1, op2));
					break;
				case token_reader::bool_op::OR:
					op1 = bdd_stack.top();
					bdd_stack.pop();
					op2 = bdd_stack.top();
					bdd_stack.pop();
					bdd_stack.push(bdd::bdd_or(op1, op2));
					break;
			}
		}
	}

	return bdd_stack.top();
}


bdd evaluate_test_data(test_data td)
{
	bdd result;

	unordered_map<string, bdd> bdd_map;

	/* Create elementary bdds for every variable */
	for (auto it=td.var_order.begin(); it!=td.var_order.end(); ++it)
	{
		bdd_map.insert(pair<string, bdd>(it->first, bdd(it->second)));
	}

	cout << "Inserted OK" << endl;
	for (auto item : td.sub_expressions)
	{
		cout << "Parsing " << item.name << " " << endl;
		bool_expr_rpn expr = bool_parser::parse(item.expr);
		cout << "Parsed " << expr << endl;

		bdd computed = rpn_to_bdd(bdd_map, expr);
		string name = item.name;
		bdd_map.insert(pair<string, bdd>(name, computed));
	}

	cout << "Map after sub expressions " << endl;
	for (auto it=bdd_map.begin(); it!=bdd_map.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	bool_expr_rpn eval_expr = bool_parser::parse(td.evaluate);

	result = rpn_to_bdd(bdd_map, eval_expr);


	return result;
}

void test2()
{
	test_data td = test_data_reader::read("G:\\Workspace\\Eclipse\\BDD_package\\test_data\\test2_compund.txt");
	bdd::bdd_init(td.var_num);
	bdd result = evaluate_test_data(td);

	cout << "Result is: " << endl;
	result.print();

	bdd::bdd_exit();
}

void test3()
{
	test_data td = test_data_reader::read("G:\\Workspace\\Eclipse\\BDD_package\\test_data\\test3.txt");
	bdd::bdd_init(td.var_num);
	bdd result = evaluate_test_data(td);

	cout << "Result is: " << endl;
	result.print();

	bdd::bdd_exit();
}

void test4()
{
	test_data td = test_data_reader::read("G:\\Workspace\\Eclipse\\BDD_package\\test_data\\test4.txt");

	bdd::bdd_init(td.var_num);

	bdd result = evaluate_test_data(td);

	cout << "Result is: " << endl;
	result.print();

	bdd::bdd_exit();
}
#endif /* TEST_BDD_HPP_ */
