#include <test_input.hpp>


static bdd rpn_to_bdd(unordered_map<string, bdd>& bdd_map, bool_expr_rpn& bool_expr);
static bdd evaluate_txt_data(txt_data td);

bdd bdd_from_txt(string file_path)
{
	txt_data td = txt_test_reader::read(file_path);
	bdd::bdd_init(td.var_num);
	return evaluate_txt_data(td);
}


static bdd rpn_to_bdd(unordered_map<string, bdd>& bdd_map, bool_expr_rpn& bool_expr)
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
				cerr << "Symbol " << token.name << " not in the map => ERROR" << endl;
				// return an empty bdd
				return bdd();

			}
			bdd_stack.push(from_map->second);
		}
		else if (token.type == token_type::OPERATOR)
		{
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


static bdd evaluate_txt_data(txt_data td)
{
	bdd result;

	unordered_map<string, bdd> bdd_map;

	/* Create elementary bdds for every variable */
	for (auto it=td.var_order.begin(); it!=td.var_order.end(); ++it)
	{
		bdd_map.insert(pair<string, bdd>(it->first, bdd(it->second)));
	}

	for (auto item : td.sub_expressions)
	{
		bool_expr_rpn expr = bool_parser::parse(item.expr);
		bdd computed       = rpn_to_bdd(bdd_map, expr);
		// insert the subexpression in bdd map (to be reused later)
		bdd_map.insert(pair<string, bdd>(item.name, computed));
	}

	// evaluate last equation using already computed subexpressions
	bool_expr_rpn eval_expr = bool_parser::parse(td.evaluate);
	result = rpn_to_bdd(bdd_map, eval_expr);

	return result;
}

