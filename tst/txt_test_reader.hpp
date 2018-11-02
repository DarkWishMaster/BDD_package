#ifndef txt_data_READER_HPP_
#define txt_data_READER_HPP_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <cstdint>

using namespace std;


typedef struct
{
	string name;
	string expr;
} sub_expr;

class txt_data
{
public:
	uint32_t		  	  var_num;
	map<string, uint32_t> var_order;
	vector<sub_expr> 	  sub_expressions;
	string evaluate;
};



/*
 * Reads the test file, saves the variable order,
 * provides a list of boolean subexpressions as bool_expr_rpn (in reverse polish notation)
 */
class txt_test_reader
{

public:

	static txt_data read(string file_path)
	{
		txt_data td;
		td.var_num = 0;

		string line;
		ifstream test_file (file_path);
		if (test_file.is_open())
		{
			while (getline(test_file, line))
			{
				if (line.find("[var_order]") != string::npos)
				{
					getline(test_file, line);
					istringstream iss(line);
					string word;
					while(iss >> word) {
						if (td.var_order.find(word) == td.var_order.end())
						{
							td.var_order.insert(pair<string, uint32_t>(word, td.var_num++));
						}
						else
						{
							cerr << "Duplicate variable " << word << "in [var_order]" << endl;
						}
					}
				}
				else if (line.find("[sub_expression]") != string::npos)
				{
					sub_expr sub;;
					getline(test_file, sub.name);
					if (sub.name[sub.name.length() - 1] == '\r')
					{
						sub.name = sub.name.substr(0, sub.name.length() - 1);
					}

					getline(test_file, sub.expr);
					td.sub_expressions.push_back(sub);
				}
				else if (line.find("[evaluate]") != string::npos )
				{
					getline(test_file, td.evaluate);
				}
			}

			test_file.close();
		}
		else
		{
			cerr << "Unable to open file " + file_path << endl;
		}

		return td;
	}


};



#endif /* txt_data_READER_HPP_ */
