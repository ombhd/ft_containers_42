/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 16:26:08 by obouykou          #+#    #+#             */
/*   Updated: 2021/10/02 17:38:36 by obouykou         ###   ########.fr       */
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
		public:
		// typedef typenames
		typedef Key												key_type;
		typedef T												mapped_type;
		typedef pair<const key_type, mapped_type>				value_type;
		typedef Compare											key_compare;
		// typedef value_compare <key_type, key_compare>			value_compare;
		typedef Alloc											allocator_type;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		typedef ptrdiff_t  										difference_type;
		typedef size_t											size_type;
		
		// typedefs for iterator
		
		
	};

} // namespace ft

#endif // MAP_HPP
