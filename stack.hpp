/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 14:56:51 by obouykou          #+#    #+#             */
/*   Updated: 2021/10/11 14:53:12 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{

	template <typename T, typename Container = ft::vector<T> >
	class stack
	{
	public:
		// typenames aliases
		typedef T value_type;
		typedef size_t size_type;
		typedef Container container_type;

		// default constructor / constructor with parameter
		explicit stack(const container_type &ctnr = container_type()) : c(ctnr) {}

		// destructor
		virtual ~stack() {}

		// Member functions

		bool empty(void) const
		{
			return (this->c.empty());
		}
		size_t size(void) const
		{
			return (this->c.size());
		}

		value_type &top(void)
		{
			return (this->c.back());
		}

		value_type const &top(void) const
		{
			return (this->c.back());
		}

		void push(value_type const &val)
		{
			this->c.push_back(val);
		}

		void pop(void)
		{
			this->c.pop_back();
		}

		template <typename ST, typename CT>
		friend bool operator==(stack<ST, CT> const &lhs, stack<ST, CT> const &rhs);

		template <typename ST, typename CT>
		friend bool operator!=(stack<ST, CT> const &lhs, stack<ST, CT> const &rhs);

		template <typename ST, typename CT>
		friend bool operator<(stack<ST, CT> const &lhs, stack<ST, CT> const &rhs);

		template <typename ST, typename CT>
		friend bool operator<=(stack<ST, CT> const &lhs, stack<ST, CT> const &rhs);

		template <typename ST, typename CT>
		friend bool operator>(stack<ST, CT> const &lhs, stack<ST, CT> const &rhs);

		template <typename ST, typename CT>
		friend bool operator>=(stack<ST, CT> const &lhs, stack<ST, CT> const &rhs);

	protected:
		Container c;
	}; // class stack
	// Non-member function overloads for the stack class

	template <typename ST, typename CT>
	bool operator==(stack<ST, CT> const &lhs, stack<ST, CT> const &rhs)
	{
		return (lhs.c == rhs.c);
	}

	template <typename ST, typename CT>
	bool operator!=(stack<ST, CT> const &lhs, stack<ST, CT> const &rhs)
	{
		return (lhs.c != rhs.c);
	}

	template <typename ST, typename CT>
	bool operator<(stack<ST, CT> const &lhs, stack<ST, CT> const &rhs)
	{
		return (lhs.c < rhs.c);
	}

	template <typename ST, typename CT>
	bool operator<=(stack<ST, CT> const &lhs, stack<ST, CT> const &rhs)
	{
		return (lhs.c <= rhs.c);
	}

	template <typename ST, typename CT>
	bool operator>(stack<ST, CT> const &lhs, stack<ST, CT> const &rhs)
	{
		return (lhs.c > rhs.c);
	}

	template <typename ST, typename CT>
	bool operator>=(stack<ST, CT> const &lhs, stack<ST, CT> const &rhs)
	{
		return (lhs.c >= rhs.c);
	}
} // namespace ft

#endif