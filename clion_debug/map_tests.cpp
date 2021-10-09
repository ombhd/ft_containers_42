/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 23:15:44 by obouykou          #+#    #+#             */
/*   Updated: 2021/10/09 16:18:43 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "map.hpp"
#include <map>
#include <iostream>
#include "map.hpp"

#ifndef NS
#define NS ft
#endif

template <typename T, typename U>
void print_namespace(ft::map<T, U> const &mp)
{
	mp.empty();
	std::cout << "\nNAMESPACE : ft" << std::endl;
}

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
		std::cout << "nothing";
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

	// begin()
	{
		std::cout << "\nbegin()" << std::endl;
		std::cout << "=======================================" << std::endl;
		NS::map<int, int> map1;
		map1.insert(NS::make_pair(5, 1));
		map1.insert(NS::make_pair(2, 2));
		map1.insert(NS::make_pair(10, 3));
        map1.insert(NS::make_pair(4, 4));
        map1.insert(NS::make_pair(8, 4));
        map1.insert(NS::make_pair(20, 4));
        map1.insert(NS::make_pair(6, 4));
		NS::map<int, int>::iterator it = map1.begin();
		NS::map<int, int>::iterator ite = map1.end();
		// print_map(map1, "map1");
		std::cout << "map1.begin(): [" << (*it).first << "] = " << (*it).second << std::endl;
		std::cout << "map1.end(): [" << (*ite).first << "] = " << (*ite).second << std::endl;
		
		std::cout << "=======================================" << std::endl;
	}

	std::cout << "end of program" << std::endl;
	return 0;
}

// // function()
// {
// 	std::cout << "\nfunction()" << std::endl;
// 	std::cout << "=======================================" << std::endl;

// 	std::cout << "=======================================" << std::endl;
// }

// NS::map<int, int>::iterator it = maptLocal.lower_bound(i);

// print_map(maptLocal, "maptLocal");
// int i = 15;
// NS::map<int, int>::iterator it = maptLocal.lower_bound(i);
// NS::map<int, int>::iterator itu = maptLocal.upper_bound(i);
// NS::map<int, int>::key_compare comp = maptLocal.key_comp();
// if (comp(0, 1))
// 	std::cout << "0 < 1" << std::endl;
// if (comp(1, 0))
// 	std::cout << "1 < 0" << std::endl;

// it--;
// it++;
// it++;
// it++;
// it++;
// it--;

// std::cout << "lower bound of " << i << " ==> [" << it->first << "]" << std::endl;
// if (it == maptLocal.end())
// 	std::cout << "it's end" << std::endl;

// std::cout << "upper bound of " << i << " ==> [" << itu->first << "]" << std::endl;
// if (itu == maptLocal.end())
// 	std::cout << "it's end" << std::endl;