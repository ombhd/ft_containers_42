/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 17:36:55 by obouykou          #+#    #+#             */
/*   Updated: 2021/10/03 16:44:53 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <iostream>

#include "pair.hpp"

#define RED true
#define BLACK false

namespace ft
{

	template <typename T>
	struct Node
	{
		typedef T value_type;
		typedef Node<T> *node_ptr;

		bool color;
		node_ptr parent;
		node_ptr left;
		node_ptr right;
		value_type value;

		Node(value_type const &value, bool color = BLACK, node_ptr parent = nullptr, node_ptr left = nullptr, node_ptr right = nullptr)
			: color(color), parent(parent), left(left), right(right), value(value)
		{
		}

		~Node()
		{
		}

		void linkRight(node_ptr nodePtr)
		{
			nodePtr->parent = this;
			this->right = nodePtr;
		}

		void linkLeft(node_ptr nodePtr)
		{
			nodePtr->parent = this;
			this->left = nodePtr;
		}

		node_ptr unlinkRight(node_ptr nodePtr)
		{
			this->right = nullptr;
			return nodePtr;
		}

		node_ptr unlinkLeft(node_ptr nodePtr)
		{
			this->left = nullptr;
			return nodePtr;
		}

		void swapWithParent()
		{
			node_ptr parent = this->parent;
			node_ptr grandparent = parent->parent;

			if (parent->left == this)
				parent->linkLeft(this->unlinkRight(this->right));
			else
				parent->linkRight(this->unlinkLeft(this->left));

			if (grandparent->left == parent)
				grandparent->linkLeft(parent->unlinkRight(parent->right));
			else
				grandparent->linkRight(parent->unlinkLeft(parent->left));
		}
	};

	template <typename T>
	class RedBlackTree
	{
	public:
		typedef T value_type;
		typedef Node<T> *node_ptr;

		RedBlackTree() {}
		~RedBlackTree() {}

		void insert(value_type value)
		{
			insert(value, root);
		}
		void remove(value_type value)
		{
			remove(value, root);
		}

	private:
		node_ptr root;
		node_ptr _start;
		node_ptr _end;
	};
}; //namespace ft

#endif //RED_BLACK_TREE_HPP
