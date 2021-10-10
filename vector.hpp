/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:52:04 by obouykou          #+#    #+#             */
/*   Updated: 2021/10/10 10:53:31 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstring>
#include <limits>
#include <algorithm>
#include <stdexcept>
#include <iostream>

#include "utils.hpp"

namespace ft
{
	template <typename T, class Alloc = std::allocator<T> >
	class vector
	{

	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef vector_iterator<pointer> iterator;
		typedef vector_iterator<const_pointer> const_iterator;
		typedef ft::reverse_iterator<const_iterator, std::random_access_iterator_tag> const_reverse_iterator;
		typedef ft::reverse_iterator<iterator, std::random_access_iterator_tag> reverse_iterator;

		// constructors

		vector(const allocator_type &alloc = allocator_type()) : _alloc(alloc),
																 _arr(this->_alloc.allocate(1)),
																 _capacity(1),
																 _size(0)
		{
		}

		vector(size_type n, const_reference val = value_type(), const allocator_type &alloc = allocator_type()) : _alloc(alloc),
																												  _arr(NULL),
																												  _capacity(0),
																												  _size(0)
		{
			if (n == 0)
			{
				_arr = this->_alloc.allocate(1);
				_capacity = 1;
				return;
			}
			this->assign(n, val);
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
			   typename enable_if<!is_integral<InputIterator>::value, bool>::type = true) : _alloc(alloc),
																							_arr(this->_alloc.allocate(1)),
																							_capacity(1),
																							_size(0)
		{
			this->assign(first, last);
		}

		vector(vector const &rhs) : _alloc(rhs._alloc),
									_arr(this->_alloc.allocate(1)),
									_capacity(1),
									_size(0)
		{
			this->reserve_no_copy(rhs._capacity);
			memcpy(static_cast<void *>(this->_arr), static_cast<void *>(rhs._arr), rhs._size * sizeof(value_type));
			this->_size = rhs._size;
		}

		// destructor
		virtual ~vector()
		{
			this->clear();
			this->_alloc.deallocate(this->_arr, this->_capacity);
		}

		// = operator overloading
		vector &operator=(vector const &rhs)
		{
			if (this == &rhs)
				return *this;
			this->clear();
			this->reserve_no_copy(rhs._capacity);
			memcpy(static_cast<void *>(this->_arr), static_cast<void *>(rhs._arr), rhs._size * sizeof(value_type));
			this->_size = rhs._size;
			return (*this);
		}

		// iterators

		iterator begin(void)
		{
			return (iterator(this->_arr));
		}

		const_iterator begin(void) const
		{
			return (const_iterator(this->_arr));
		}

		reverse_iterator rbegin(void)
		{
			return (reverse_iterator(this->end()));
		}

		const_reverse_iterator rbegin(void) const
		{
			return (const_reverse_iterator(this->end()));
		}

		iterator end(void)
		{
			return (iterator(this->_arr + this->_size));
		}

		const_iterator end(void) const
		{
			return (const_iterator(this->_arr + this->_size));
		}

		reverse_iterator rend(void)
		{
			return (reverse_iterator(this->begin()));
		}

		const_reverse_iterator rend(void) const
		{
			return (const_reverse_iterator(this->begin()));
		}

		// Capacity

		size_type size(void) const
		{
			return (this->_size);
		}

		size_type max_size(void) const
		{
			return this->_alloc.max_size();
		}

		void resize(size_type n, value_type val = value_type())
		{
			if (n > this->_size)
			{
				for (size_type i = this->_size; i < n; ++i)
					this->push_back(val);
			}
			else if (n < this->_size)
			{
				size_type tmp = this->_size;
				for (size_type i = n; i < tmp; ++i)
					this->pop_back();
			}
		}

		size_type capacity(void) const
		{
			return (this->_capacity);
		}

		bool empty(void) const
		{
			return (this->_size == 0);
		}

		void reserve(size_type n)
		{
			if (n > this->_capacity)
			{
				n = n > this->_capacity * 2 ? n : this->_capacity * 2;
				pointer tmp = _alloc.allocate(n);
				this->_capacity = n;
				for (size_type i = 0; i < this->_size; i++)
				{
					_alloc.construct(tmp + i, this->_arr[i]);
				}
				_alloc.deallocate(this->_arr, this->_capacity);
				this->_arr = tmp;
			}
		}

		// Element Access

		reference operator[](size_type index)
		{
			return (this->_arr[index]);
		}

		const_reference operator[](size_type index) const
		{
			return (this->_arr[index]);
		}

		reference at(size_type index)
		{
			if (index >= this->_size)
				throw std::out_of_range("vector: index is out of range");
			return (this->_arr[index]);
		}

		const_reference at(size_type index) const
		{
			if (index >= this->_size)
				throw std::out_of_range("vector: index is out of range");
			return (this->_arr[index]);
		}

		reference front(void)
		{
			return (this->_arr[0]);
		}

		const_reference front(void) const
		{
			return (this->_arr[0]);
		}

		reference back(void)
		{
			return (this->_arr[this->_size - 1]);
		}

		const_reference back(void) const
		{
			return (this->_arr[this->_size - 1]);
		}

		//Modifiers

		// range (1)
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value, bool>::type = true)
		{
			difference_type diff = last - first;
			if (diff < 0)
				throw std::range_error("vector: invalid range");
			else if (!diff)
				return;
			size_type count = static_cast<size_type>(diff);
			size_type old_size = this->_size;
			if (count > this->_capacity)
				this->reserve_no_copy(count);
			for (size_type i = 0; i < count; i++)
			{
				this->_alloc.construct(&this->_arr[i], first[i]);
			}
			if (old_size > count)
				for (size_type i = count; i < old_size; i++)
				{
					this->_alloc.destroy(&this->_arr[i]);
				}
			this->_size = count;
		}

		// fill (2)
		void assign(size_type n, const value_type &val)
		{
			if (!n)
				return;
			size_type old_size = this->_size;
			if (n > this->_capacity)
				this->reserve_no_copy(n);
			for (size_type i = 0; i < n; i++)
			{
				this->_alloc.construct(&this->_arr[i], val);
			}
			if (old_size > n)
				for (size_type i = n; i < old_size; i++)
				{
					this->_alloc.destroy(&this->_arr[i]);
				}
			this->_size = n;
		}

		void push_back(value_type val)
		{
			if (this->_size + 1 > this->_capacity)
				this->reserve(this->_size + 1);
			this->_alloc.construct(&this->_arr[this->_size++], val);
		}

		void pop_back()
		{
			if (this->_size)
				this->_alloc.destroy(&this->_arr[--this->_size]);
		}

		// single element (1)
		iterator insert(iterator position, const value_type &val)
		{
			size_type pos = position.asIndex(this->_arr);
			if (this->_size + 1 > this->_capacity)
				this->reserve(this->_size + 1);
			for (size_t j = this->_size; j > pos; j--)
			{
				this->_alloc.construct(&this->_arr[j], this->_arr[j - 1]);
			}
			this->_alloc.construct(&this->_arr[pos], val);
			this->_size++;
			return iterator(this->_arr + pos);
		}

		// fill (2)
		void insert(iterator position, size_type n, const value_type &val)
		{
			if (!n)
				return;
			size_type totalRequired = this->_size + n;
			size_type pos = position.asIndex(this->_arr);
			if (totalRequired > this->_capacity)
				this->reserve(totalRequired);
			for (size_t j = this->_size; j > pos; j--)
			{
				this->_alloc.construct(&this->_arr[j - 1 + n], this->_arr[j - 1]);
			}
			this->_size += n;
			while (n--)
			{
				this->_alloc.construct(&this->_arr[pos + n], val);
			}
		}

		// range (3)
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value, bool>::type = true)
		{
			difference_type diff = last - first;
			if (diff < 0)
				throw std::range_error("vector: invalid range");
			else if (!diff)
				return;
			size_type count = static_cast<size_type>(diff);
			size_type pos = position.asIndex(this->_arr);
			if (count + this->_size > this->_capacity)
				this->reserve(count + this->_size);
			for (size_t j = this->_size; j > pos; j--)
			{
				this->_alloc.construct(&this->_arr[j - 1 + count], this->_arr[j - 1]);
			}
			this->_size += count;
			while (count--)
			{
				this->_alloc.construct(&this->_arr[pos + count], *--last);
			}
		}

		iterator erase(iterator position)
		{
			if (!this->_size)
				return position;
			size_type i = position.asIndex(this->_arr);

			if (i >= this->_size)
				return position;

			while (i < this->_size - 1)
			{
				this->_alloc.destroy(&this->_arr[i]);
				this->_alloc.construct(&this->_arr[i], this->_arr[i + 1]);
				i++;
			}

			if (!--this->_size)
				return this->end();
			return position;
		}

		iterator erase(iterator first, iterator last)
		{
			if (!this->_size)
				return first;
			difference_type diff = last - first;
			size_type pos = first.asIndex(this->_arr);
			if (diff < 0)
				throw std::range_error("vector: invalid range");
			else if (!diff || pos >= this->_size)
				return this->end();
			size_type count = static_cast<size_type>(diff);
			for (size_t j = pos; j < this->_size - count; j++)
			{
				this->_alloc.destroy(&this->_arr[j]);
				this->_alloc.construct(&this->_arr[j], this->_arr[j + count]);
			}
			for (size_t i = pos + count; i < this->_size; i++)
			{
				this->_alloc.destroy(&this->_arr[i]);
			}
			this->_size -= count;
			return first;
		}

		void swap(vector &x)
		{
			std::swap(this->_arr, x._arr);
			std::swap(this->_size, x._size);
			std::swap(this->_capacity, x._capacity);
			std::swap(this->_alloc, x._alloc);
		}

		void clear()
		{
			while (this->_size != 0)
				this->_alloc.destroy(&this->_arr[--this->_size]);
			this->_alloc.deallocate(this->_arr, this->_capacity);
			this->_arr = this->_alloc.allocate(1);
			this->_capacity = 1;
		}

		// allocator
		allocator_type get_allocator() const
		{
			return this->_alloc;
		}

	private:
		std::allocator<value_type> _alloc;
		pointer _arr;
		size_type _capacity;
		size_type _size;

		void reserve_no_copy(size_type n)
		{
			if (n > this->_capacity)
			{
				this->_alloc.deallocate(this->_arr, this->_capacity);
				n = n > this->_capacity * 2 ? n : this->_capacity * 2;
				this->_arr = this->_alloc.allocate(n);
				this->_capacity = n;
				this->_size = 0;
			}
		}
	}; // class vector

	template <typename T, class Alloc>
	bool operator==(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <typename T, class Alloc>
	bool operator!=(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs)
	{
		return (!(lhs == rhs));
	}

	template <typename T, class Alloc>
	bool operator<(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename T, class Alloc>
	bool operator<=(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs)
	{
		return (!(rhs < lhs));
	}

	template <typename T, class Alloc>
	bool operator>(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs)
	{
		return (rhs < lhs);
	}

	template <typename T, class Alloc>
	bool operator>=(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs)
	{
		return (!(lhs < rhs));
	}

	template <typename T, class Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		x.swap(y);
	}
} // namespace ft

#endif // !VECTOR_HPP