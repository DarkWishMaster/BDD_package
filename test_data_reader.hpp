#ifndef TEST_DATA_READER_HPP_
#define TEST_DATA_READER_HPP_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>

using namespace std;


typedef struct
{
	string name;
	string expr;
} sub_expr;

class test_data
{
public:
	unsigned int		  	  var_num;
	map<string, unsigned int> var_order;
	vector<sub_expr> 		  sub_expressions;
	string evaluate;
};



/*
 * Reads the test file, saves the variable order,
 * provides a list of boolean subexpressions as bool_expr_rpn (in reverse polish notation)
 */
class test_data_reader
{

public:

	static test_data read(string file_path)
	{
		test_data td;
		td.var_num = 0;

		// TBD error detection mechanism
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
						// TBD check for duplicates
						td.var_order.insert(pair<string, unsigned int>(word, td.var_num++));
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
		else cout << "Unable to open file";

		return td;
	}


};



#endif /* TEST_DATA_READER_HPP_ */
