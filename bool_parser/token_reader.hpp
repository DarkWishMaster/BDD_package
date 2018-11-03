#ifndef TOKEN_READER_HPP_
#define TOKEN_READER_HPP_

#include <stdint.h>
#include <string>

using namespace std;

class token_reader
{

public:

	enum class bool_op    {NOT, AND, OR, IMP, XOR, EQ};
	enum class token_type {SYMBOL, OPERATOR, LEFT_BRACKET, RIGHT_BRACKET, UNKNOWN};

	class token
	{
		public:
			token_type    type;
			string        name;  // symbol name (if any)
			bool_op       op;    // boolean operator in case of operator

	};

	token_reader(string expression)
	{
		this->expression   = expression;
		this->current_char = 0;
	}

	token next_token()
	{
		token t;

		if (has_tokens())
		{
			/* skip spaces and new line characters */
			while (current_char < expression.length() &&
					(expression[current_char] == ' ' ||
					 expression[current_char] == '\r' ||
					 expression[current_char] == '\n'))
			{
				current_char++;
			}

//			cout << "Current char " << expression[current_char] << endl;

			if (is_character(expression[current_char]))
			{
				t.name = "";
				t.type = token_type::SYMBOL;
				while (current_char < expression.length() &&
					(is_character(expression[current_char])
					|| is_number(expression[current_char])))
				{
					t.name += expression[current_char++];
				}
			}
			else if (expression[current_char] == '1' || expression[current_char] == '0')
			{
				t.name = expression[current_char++];
				t.type = token_type::SYMBOL;
			}
			else if ((current_char + 1) < expression.length() &&
					expression[current_char] == '=' &&
					expression[current_char + 1] == '>')
			{
//					cout << "Implication " << endl;

					t.type = token_type::OPERATOR;
					t.op   = bool_op::IMP;
					t.name = "=>";
					current_char += 2;
			} else if ((current_char + 2) < expression.length() &&
					expression[current_char] == '<'     &&
					expression[current_char + 1] == '=' &&
					expression[current_char + 2] == '>')
			{
//				cout << "Equivalence " << endl;
				t.type = token_type::OPERATOR;
				t.op   = bool_op::EQ;
				t.name = "<=>";
				current_char += 3;
			}
			else
			{

				switch(expression[current_char])
				{
					case '!':
					case '~':
						t.type = token_type::OPERATOR;
						t.op   = bool_op::NOT;
						t.name = "!";
						break;
					case '*':
					case '&':
						t.type = token_type::OPERATOR;
						t.op   = bool_op::AND;
						t.name = "*";
						break;
					case '+':
					case '|':
						t.type = token_type::OPERATOR;
						t.op   = bool_op::OR;
						t.name = "+";
						break;
					case '^':
						t.type = token_type::OPERATOR;
						t.op   = bool_op::XOR;
						t.name = "^";
						break;
					case '(':
						t.type = token_type::LEFT_BRACKET;
						t.name = "(";
						break;
					case ')':
						t.type = token_type::RIGHT_BRACKET;
						t.name = ")";
						break;
					default:
						t.type = token_type::UNKNOWN;
						t.name = expression[current_char];
				}

				current_char++;
			}
		}

		return t;
	}

	bool has_tokens()
	{
		unsigned int i = current_char;

		while (i < expression.length() &&
				(expression[i] == ' '  ||
				 expression[i] == '\r' ||
				 expression[i] == '\n'))
		{
			i++;
		}

		return i < expression.length();
	}

	static int get_precedence(const bool_op op)
	{
		switch (op)
		{
			case bool_op::NOT:
				return 6;
			case bool_op::AND:
				return 5;
			case bool_op::OR:
				return 4;
			case bool_op::IMP:
				return 3;
			case bool_op::XOR:
				return 2;
			case bool_op::EQ:
				return 1;
			default:
				return 0;
			}
	}


private:
	string       expression;
	unsigned int current_char;


	bool is_character(char c)
	{
		return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
	}


	bool is_number(char c)
	{
		return (c >= '0' && c <= '9');
	}


};


#endif /* TOKEN_READER_HPP_ */
