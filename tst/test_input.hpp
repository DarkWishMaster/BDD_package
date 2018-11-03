#ifndef TST_TEST_INPUT_HPP_
#define TST_TEST_INPUT_HPP_

#include <iostream>
#include <assert.h>
#include <stack>
#include <bdd.hpp>
#include <bool_parser.hpp>
#include <txt_test_reader.hpp>
#include <unordered_map>

using namespace std;

extern bdd bdd_from_txt(string file_path);



#endif /* TST_TEST_INPUT_HPP_ */
