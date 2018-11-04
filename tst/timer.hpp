#ifndef TESTS_TIMER_HPP_
#define TESTS_TIMER_HPP_

#include <iostream>
#include <chrono>

using milliseconds = std::chrono::duration<float, std::ratio<1, 1000>> ;

class timer
{
private:
	static std::chrono::steady_clock::time_point begin;
	static milliseconds elapsed_time;

public:
	static void start_count()
	{
		begin = std::chrono::steady_clock::now();
	}

	static milliseconds end_count()
	{
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		milliseconds dt = std::chrono::duration_cast<milliseconds>(end - begin);
		elapsed_time += dt;
		return dt;
	}

	static milliseconds get_elapsed()
	{
		return elapsed_time;
	}

	static void print_test(std::string test_name)
	{
		std::cout << std::setw(20) << test_name << "  ";

		std::cout << std::setw(6) << timer::end_count().count() << " ms, total "
				<< std::setw(6) << timer::get_elapsed().count() << " ms " << std::endl;
	}

};
std::chrono::steady_clock::time_point timer::begin;
milliseconds timer::elapsed_time(0);

#endif /* TESTS_TIMER_HPP_ */
