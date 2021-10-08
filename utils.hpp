/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 12:01:43 by obouykou          #+#    #+#             */
/*   Updated: 2021/10/08 12:46:56 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
namespace ft
{
	// define iterator traits for iterator types

	template <class Iter>
	struct iterator_traits
	{
		typedef typename Iter::iterator_category iterator_category;
		typedef typename Iter::value_type value_type;
		typedef typename Iter::difference_type difference_type;
		typedef typename Iter::pointer pointer;
		typedef typename Iter::reference reference;
	};

	// define iterator traits for non-iterator types
	template <class T>
	struct iterator_traits<T *>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template <class T>
	struct iterator_traits<const T *>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T *pointer;
		typedef const T &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	// define iterator base class
	template <class Category,			  // iterator::iterator_category
			  class T,					  // iterator::value_type
			  class Distance = ptrdiff_t, // iterator::difference_type
			  class Pointer = T *,		  // iterator::pointer
			  class Reference = T &		  // iterator::reference
			  >
	class iterator
	{
	public:
		typedef Category iterator_category;
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
	};

	// define vector iterator
	template <class Iterator>
	class vector_iterator : public iterator<std::random_access_iterator_tag,
											typename iterator_traits<Iterator>::value_type>
	{

	public:
		// typedefs
		typedef Iterator iterator_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::pointer pointer;
		typedef typename iterator_traits<Iterator>::reference reference;

		// default (1)
		vector_iterator() : _current(iterator_type()) {}

		// initialization (2)
		explicit vector_iterator(iterator_type it) : _current(it) {}

		// copy (3)
		template <class Iter>
		vector_iterator(const vector_iterator<Iter> &vec_it) : _current(vec_it.base()) {}

		// base() : Returns a copy of the base iterator.
		iterator_type base() const
		{
			return this->_current;
		}

		// Dereference iterator
		reference operator*() const
		{
			iterator_type tmp = this->base();
			return *tmp;
		}

		// Addition operator
		vector_iterator operator+(difference_type n) const
		{
			return vector_iterator(this->base() + n);
		}

		size_t asIndex(iterator_type it) const
		{
			ptrdiff_t diff = this->_current - it;
			if (diff < 0L)
				throw std::invalid_argument("vector iterator: invalid iterator for the current vector");
			return (diff);
		}

		// Increment iterator position operators
		vector_iterator &operator++()
		{
			++this->_current;
			return *this;
		}

		vector_iterator operator++(int)
		{
			vector_iterator tmp = *this;
			++this->_current;
			return tmp;
		}

		// Advance iterator position operators
		vector_iterator &operator+=(difference_type n)
		{
			this->_current += n;
			return *this;
		}

		// Subtraction operator
		vector_iterator operator-(difference_type n) const
		{
			return vector_iterator(this->base() - n);
		}

		// Decrement iterator position operators
		vector_iterator &operator--()
		{
			--this->_current;
			return *this;
		}

		vector_iterator operator--(int)
		{
			vector_iterator tmp = *this;
			--this->_current;
			return tmp;
		}

		// Dereference iterator
		pointer operator->() const
		{
			iterator_type tmp = this->base();
			return &*tmp;
		}

		// Dereference iterator with offset
		reference operator[](difference_type n) const
		{
			return *(*this + n);
		}

	private:
		iterator_type _current;
	};

	// Relational operators for vector_iterator
	// (1)
	template <class Iterator>
	bool operator==(const vector_iterator<Iterator> &lhs,
					const vector_iterator<Iterator> &rhs)
	{
		return (lhs.base() == rhs.base());
	}
	// (2)
	template <class Iterator>
	bool operator!=(const vector_iterator<Iterator> &lhs,
					const vector_iterator<Iterator> &rhs)
	{
		return (lhs.base() != rhs.base());
	}
	// (3)
	template <class Iterator>
	bool operator<(const vector_iterator<Iterator> &lhs,
				   const vector_iterator<Iterator> &rhs)
	{
		return (lhs.base() < rhs.base());
	}
	// (4)
	template <class Iterator>
	bool operator<=(const vector_iterator<Iterator> &lhs,
					const vector_iterator<Iterator> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}
	// (5)
	template <class Iterator>
	bool operator>(const vector_iterator<Iterator> &lhs,
				   const vector_iterator<Iterator> &rhs)
	{
		return (lhs.base() > rhs.base());
	}
	// (6)
	template <class Iterator>
	bool operator>=(const vector_iterator<Iterator> &lhs,
					const vector_iterator<Iterator> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	// Addition operator for vector_iterator
	template <class Iterator>
	vector_iterator<Iterator> operator+(
		typename vector_iterator<Iterator>::difference_type n,
		const vector_iterator<Iterator> &rev_it)
	{
		return vector_iterator<Iterator>(rev_it.base() + n);
	}

	// Subtraction operator for vector_iterator
	template <class Iterator>
	typename vector_iterator<Iterator>::difference_type operator-(
		const vector_iterator<Iterator> &lhs,
		const vector_iterator<Iterator> &rhs)
	{
		return lhs.base() - rhs.base();
	}

	// define reverse iterator
	template <class Iterator, class Category = std::random_access_iterator_tag>
	class reverse_iterator : public iterator<Category,
											 typename iterator_traits<Iterator>::value_type>
	{
	public:
		// typedefs
		typedef Iterator iterator_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::pointer pointer;
		typedef typename iterator_traits<Iterator>::reference reference;

		// default (1)
		reverse_iterator() : _current(iterator_type()) {}

		// initialization (2)
		explicit reverse_iterator(iterator_type it) : _current(it) {}

		// copy (3)
		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter> &rev_it) : _current(rev_it.base()) {}

		// base() : Returns a copy of the base iterator.
		iterator_type base() const
		{
			return this->_current;
		}

		// Dereference iterator
		reference operator*() const
		{
			iterator_type tmp = this->base();
			return *--tmp;
		}

		// Addition operator
		reverse_iterator operator+(difference_type n) const
		{
			return reverse_iterator(this->base() - n);
		}

		// Increment iterator position operators
		reverse_iterator &operator++()
		{
			--this->_current;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			--this->_current;
			return tmp;
		}

		// Advance iterator position operators
		reverse_iterator &operator+=(difference_type n)
		{
			this->_current -= n;
			return *this;
		}

		// Subtraction operator
		reverse_iterator operator-(difference_type n) const
		{
			return reverse_iterator(this->base() + n);
		}

		// Decrement iterator position operators
		reverse_iterator &operator--()
		{
			++this->_current;
			return *this;
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			++this->_current;
			return tmp;
		}

		// Dereference iterator
		pointer operator->() const
		{
			iterator_type tmp = this->base();
			return &*--tmp;
		}

		// Dereference iterator with offset
		reference operator[](difference_type n) const
		{
			return *(*this + n);
		}

	private:
		iterator_type _current;
	};

	// Relational operators for reverse_iterator
	// (1)
	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() == rhs.base());
	}
	// (2)
	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() != rhs.base());
	}
	// (3)
	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator> &lhs,
				   const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() > rhs.base());
	}
	// (4)
	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	// (5)
	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator> &lhs,
				   const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() < rhs.base());
	}
	// (6)
	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	// Addition operator for reverse_iterator
	template <class Iterator>
	reverse_iterator<Iterator> operator+(
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator> &rev_it)
	{
		return reverse_iterator<Iterator>(rev_it.base() - n);
	}

	// Subtraction operator for reverse_iterator
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(
		const reverse_iterator<Iterator> &lhs,
		const reverse_iterator<Iterator> &rhs)
	{
		return rhs.base() - lhs.base();
	}

	// define lexicographical_compare
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								 InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	// define lexicographical_compare (2)
	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								 InputIterator2 first2, InputIterator2 last2,
								 Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return false;
			else if (comp(*first1, *first2))
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	// define enable_if
	template <bool B, class T = void>
	struct enable_if
	{
	};

	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	// define is_integral
	template <class T>
	struct is_integral
	{
		static const bool value = false;
	};

	template <>
	struct is_integral<bool>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<char>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<char16_t>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<char32_t>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<wchar_t>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<signed char>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<short int>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<int>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<long int>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<long long int>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned char>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned short int>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned int>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned long int>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned long long int>
	{
		static const bool value = true;
	};

}