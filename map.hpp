/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 16:26:08 by obouykou          #+#    #+#             */
/*   Updated: 2021/10/06 11:54:51 by obouykou         ###   ########.fr       */
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
		class value_compare : public std::binary_function<value_type, value_type, bool>
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
		typedef TreeIterator<value_type, key_compare> iterator;
		typedef TreeIterator<const value_type, key_compare> const_iterator;
		typedef TreeReverseIterator<iterator, key_compare> reverse_iterator;
		typedef TreeReverseIterator<const_iterator, key_compare> const_reverse_iterator;

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
			this->insert(first, last);
		}

		// copy (3)
		map(const map &x)
		{
			*this = x;
		}

		// operator=
		map &operator=(const map &x)
		{
			if (this != &x)
			{
				this->clear();
				this->insert(x.begin(), x.end());
			}
		}

		// Iterators:

		iterator begin()
		{
			return (iterator(tree.getStart()));
		}

		const_iterator begin() const
		{
			return (iterator(tree.getStart()));
		}

		iterator end()
		{
			return iterator(tree.getEnd());
		}

		const_iterator end() const
		{
			return iterator(tree.getEnd());
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(tree.getEnd());
		}
		const_reverse_iterator rbegin() const
		{
			return reverse_iterator(tree.getEnd());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(tree.getStart());
		}
		const_reverse_iterator rend() const
		{
			return reverse_iterator(tree.getStart());
		}

		// Capacity:

		bool empty() const
		{
			return this->size() == 0;
		}

		size_type size() const
		{
			return tree.getSize();
		}

		size_type max_size() const
		{
			return tree.getAllocator().max_size();
		}

		// Element access:

		mapped_type &operator[](const key_type &k)
		{
			return tree.getElementByKey(k);
		}

		// Modifiers:

		// insert
		// single element (1)
		ft::pair<iterator, bool> insert(const value_type &val)
		{
			return tree.insert(val);
		}
		// with hint (2)
		iterator insert(iterator hint, const value_type &val)
		{
			return tree.insert(hint, val);
		}
		// range (3)
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			while (first != last)
				tree.insert(*first++);
		}

		// erase

		// (1)
		void erase(iterator position)
		{
			tree.removeByPosition(position);
		}
		// single element (2)
		size_type erase(const key_type &k)
		{
			return tree.removeByKey(k);
		}
		// range (3)
		iterator erase(iterator first, iterator last)
		{
			while (first != last)
				first = tree.removeByPosition(first);
			return first;
		}

		void clear()
		{
		}

	private:
		// define data members
		tree_type tree;
	}; // map class

} // namespace ft

#endif // MAP_HPP
