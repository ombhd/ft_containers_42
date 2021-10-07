/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 23:15:44 by obouykou          #+#    #+#             */
/*   Updated: 2021/10/07 18:35:45 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "map.hpp"
#include <map>
#include <iostream>

#ifndef NS
#define NS std
#endif

// template <typename T, typename U>
// void print_namespace(ft::map<T, U> const &mp)
// {
// 	std::cout << "ft::map<" << typeid(T).name() << ", " << typeid(U).name() << ">\n";
// 	mp.empty();
// 	std::cout << "\nNAMESPACE : ft" << std::endl;
// }

template <typename T, typename U>
void print_namespace(std::map<T, U> const &mp)
{
	mp.empty();
	std::cout << "\nNAMESPACE : std" << std::endl;
}

template <typename T, typename U>
void print_map(NS::map<T, U> &mp, char const *label)
{
	std::cout << "\nmap Size: " << mp.size();
	std::cout << "\nmap [" << label << "] contains: ";
	if (!mp.size())
		std::cout << "\tnothing";
	else
		std::cout << "\n\n";
	for (typename NS::map<T, U>::iterator it = mp.begin(); it != mp.end(); ++it)
	{
		std::cout << "[" << it->first << "]"
				  << " = " << it->second << std::endl;
	}
	std::cout << std::endl;
}

int main(void)
{
	NS::map<int, int> maptGolbal;
	print_namespace(maptGolbal);

	NS::map<int, int> maptLocal;
	maptLocal[12] = 12;
	maptLocal[6] = 13;
	maptLocal[5] = 14;
	maptLocal[3] = 15;
	maptLocal[4] = 16;
	maptLocal[7] = 17;
	maptLocal[8] = 18;
	maptLocal[14] = 19;
	maptLocal[20] = 20;
	maptLocal[30] = 21;

	// print_map(maptLocal, "maptLocal");
	NS::map<int, int>::iterator it = maptLocal.begin();
	it--;
	// it++;
	// it++;
	// it++;
	// it++;
	// it--;

	std::cout << "[" << it->first << "]" << std::endl;

	return 0;
}

// // function()
// {
// 	std::cout << "\nfunction()" << std::endl;
// 	std::cout << "=======================================" << std::endl;

// 	std::cout << "=======================================" << std::endl;
// }