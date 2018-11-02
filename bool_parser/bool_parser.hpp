#ifndef BOOL_PARSER_HPP_
#define BOOL_PARSER_HPP_

#include <string>
#include <deque>
#include <stack>

#include <bool_expr_rpn.hpp>
#include <token_reader.hpp>

using token_type = token_reader::token_type;

using namespace std;

class bool_parser
{

public:

	/* Parses a boolean expression using Shunting-yard algorithm
	 * and returns it into a reverse polish notation (stored in a list)
	 */
	static bool_expr_rpn parse(string bool_expr)
	{
		token_reader tr(bool_expr);
		bool_expr_rpn b_expr;

		stack<token_reader::token>  op_stack;

		while (tr.has_tokens())
		{
			token_reader::token token = tr.next_token();
			if (token.type == token_type::SYMBOL)
			{
				b_expr.add_token(token);
			}
			else if (token.type == token_type::OPERATOR)
			{
				while (!op_stack.empty() && (op_stack.top().type == token_type::OPERATOR &&
						(token_reader::get_precedence(op_stack.top().op))
					       > token_reader::get_precedence(token.op))
						&& op_stack.top().type != token_type::LEFT_BRACKET)
				{
					b_expr.add_token(op_stack.top());
					op_stack.pop();
				}

				op_stack.push(token);
			}
			else if (token.type == token_type::LEFT_BRACKET)
			{
				op_stack.push(token);
			}
			else if (token.type == token_type::RIGHT_BRACKET)
			{
				while (!op_stack.empty() && op_stack.top().type != token_type::LEFT_BRACKET)
				{
					b_expr.add_token(op_stack.top());
					op_stack.pop();
				}
				op_stack.pop();
			}
			else if (token.type == token_type::UNKNOWN)
			{
				// TBD: error
			}

		}

		// TBD: check if parentheses match

		while (!op_stack.empty())
		{
			b_expr.add_token(op_stack.top());
			op_stack.pop();
		}

		return b_expr;
	}


private:




};


#endif /* BOOL_PARSER_HPP_ */
