#ifndef BOOL_EXPR_RPN_HPP_
#define BOOL_EXPR_RPN_HPP_

#include <deque>
#include <token_reader.hpp>

using namespace std;
class bool_expr_rpn
{


private:
	unsigned int var_num;
	deque<token_reader::token> data;


public:


	bool evaluate(bool input[])
	{
		return true;
	}

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



};


#endif /* BOOL_EXPR_RPN_HPP_ */
