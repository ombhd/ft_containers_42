/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 16:26:08 by obouykou          #+#    #+#             */
/*   Updated: 2021/10/04 18:43:12 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <functional>

#include "red_black_tree.hpp"

namespace ft
{

	// define the map container
	template <class Key,										// map::key_type
			  class T,											// map::mapped_type
			  class Compare = std::less<Key>,					// map::key_compare
			  class Alloc = std::allocator<pair<const Key, T> > // map::allocator_type
			  >
	class map
	{
		private:
		
	public:
		// typedef typenames
		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		class value_compare : public std::binary_function<value_type,value_type,bool>
		{
			friend class map;
			private:
				key_compare comp;
			public:
				value_compare(const key_compare &x) : comp(x) {}
				bool operator()(const value_type &x, const value_type &y) const
				{
					return comp(x.first, y.first);
				}
		};
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
		typedef BinarySearchTree<value_type, value_compare, allocator_type> tree_type;

		// typedefs for iterator

		// define construtors

		// empty (1)
		explicit map(const key_compare &comp = key_compare(),
					 const allocator_type &alloc = allocator_type()) : tree(comp, alloc)
		{
		}

		// range (2)
		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type()) : tree(comp, alloc)
		{
		}

		// copy (3)
		map(const map &x)
		{
		}

	private:
		// define data members
		tree_type tree;	
	}; // map class

} // namespace ft

#endif // MAP_HPP
