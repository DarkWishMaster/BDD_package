#ifndef BOOL_EXPR_RPN_HPP_
#define BOOL_EXPR_RPN_HPP_

#include <deque>
#include <token_reader.hpp>
#include <cstdint>

using namespace std;
class bool_expr_rpn
{


private:
	uint32_t var_num;
	deque<token_reader::token> data;

public:

	void add_token(token_reader::token token)
	{
		data.push_back(token);
	}

	friend ostream & operator << (ostream &out, const bool_expr_rpn &expr)
	{
		for (auto token : expr.data)
		{
			out << token.name << " ";
		}
		out << endl;

		return out;
	}

	deque<token_reader::token>& get_tokens()
	{
		return data;
	}

};


#endif /* BOOL_EXPR_RPN_HPP_ */
