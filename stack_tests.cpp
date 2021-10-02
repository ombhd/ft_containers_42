/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_tests.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 23:15:44 by obouykou          #+#    #+#             */
/*   Updated: 2021/10/02 16:22:30 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.hpp"
#include <stack>
#include <cmath>
#include <iostream>

#ifndef NS
#define NS ft
#endif

template <typename T>
void print_namespace(ft::stack<T> const &stk)
{
	if (stk.size())
		stk.empty();
	std::cout << "\nNAMESPACE : ft" << std::endl;
}

template <typename T>
void print_namespace(std::stack<T> const &stk)
{
	if (stk.size())
		stk.empty();
	std::cout << "\nNAMESPACE : std" << std::endl;
}

template <typename T>
void print_stack(NS::stack<T> &mystk, char const *label)
{
	NS::stack<T> stk = mystk;
	std::cout << "\nstack Size: " << stk.size();
	std::cout << "\nstack [" << label << "] contains:";
	if (stk.empty())
		std::cout << "\tnothing";
	for (; stk.size();)
	{
		std::cout << " \n [ " << stk.top() << " ]";
		stk.pop();
	}
	std::cout << std::endl;
}

int main(void)
{
	NS::stack<int> vectGolbal;
	print_namespace(vectGolbal);
	// top() and empty()
	{
		std::cout << "\nfront() & back()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::stack<int> mystack;

		if (mystack.empty())
		 std::cout << "mystack is empty" << std::endl;

		mystack.push(22);
		mystack.push(77);

		print_stack(mystack, "mystack");

		// now top equals 77
		std::cout << "mystack.top() is now " << mystack.top() << '\n';
		std::cout << "=======================================" << std::endl;
	}

	// size()
	{
		std::cout << "\nmax_size()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::stack<size_t> mystack;

		mystack.push(77);
		mystack.push(65);
		mystack.push(69);
		mystack.push(65);
		mystack.push(78);
		mystack.push(22);

		print_stack(mystack, "mystack");

		std::cout << "mystack.size() is: " << mystack.size() << '\n';
		std::cout << "=======================================" << std::endl;
	}



	// relational operators()
	{
		std::cout << "\nrelational operators" << std::endl;
		std::cout << "=======================================" << std::endl;

		NS::stack<int> a;
		a.push(10);
		a.push(20);
		a.push(30);
		print_stack(a, "a");
		NS::stack<int> b = a;
		// b = a;

		print_stack(b, "b");

		NS::stack<int> c;
		c.push(30);
		c.push(20);
		c.push(10);
		print_stack(c, "c");

		if (a == b)
			std::cout << "\na and b are equal\n";
		if (b != c)
			std::cout << "b and c are not equal\n";
		if (b < c)
			std::cout << "b is less than c\n";
		if (c > b)
			std::cout << "c is greater than b\n";
		if (a <= b)
			std::cout << "a is less than or equal to b\n";
		if (a >= b)
			std::cout << "a is greater than or equal to b\n";
		std::cout << "=======================================" << std::endl;
	}

	return 0;
}

// // function()
// {
// 	std::cout << "\nfunction()" << std::endl;
// 	std::cout << "=======================================" << std::endl;

// 	std::cout << "=======================================" << std::endl;
// }