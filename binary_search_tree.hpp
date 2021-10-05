/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_tree.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 16:15:06 by obouykou          #+#    #+#             */
/*   Updated: 2021/10/05 16:34:03 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <iostream>

#include "pair.hpp"

#define RED true
#define BLACK false

namespace ft
{

	template <typename T>
	class TreeNode
	{
	public:
		typedef T value_type;
		typedef TreeNode<T> *node_ptr;

		bool color;
		bool isRightChild;
		node_ptr parent;
		node_ptr left;
		node_ptr right;
		value_type value;

		TreeNode(value_type const &value = value_type(),
				 bool color = RED,
				 node_ptr parent = nullptr,
				 node_ptr left = nullptr,
				 node_ptr right = nullptr,
				 bool isRightChild = false)
			: color(color),
			  isRightChild(isRightChild),
			  parent(parent),
			  left(left),
			  right(right),
			  value(value)
		{
		}

		~TreeNode()
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
	}; // struct TreeNode

	// TreeIterator : Binary Search Tree Iterator definition
	template <typename T, class Compare>
	class TreeIterator
	{
	public:
		TreeIterator() {}
		~TreeIterator() {}

	private:
	};

	template <typename T, class Compare>
	class TreeReverseIterator
	{
	public:
		TreeReverseIterator() {}
		~TreeReverseIterator() {}

	private:
	};

	// BinarySearchTree class definition
	template <typename T, class Compare, class Alloc = std::allocator<TreeNode<T> > >
	class BinarySearchTree
	{
	public:
		typedef T value_type;
		typedef typename value_type::first_type key_type;
		typedef typename value_type::second_type mapped_type;
		typedef TreeNode<T> node;
		typedef TreeNode<T> *node_ptr;
		typedef size_t size_type;
		typedef Alloc allocator_type;
		typedef Compare key_compare;

		BinarySearchTree(const key_compare &comp = key_compare(),
						 const allocator_type &alloc = allocator_type()) : alloc(alloc),
																		   comp(comp),
																		   root(nullptr),
																		   start(alloc.allocate(1)),
																		   end(start),
																		   size(0)

		{
			alloc.construct(start, node());
		}
		~BinarySearchTree()
		{
			// TODO: implement clear() method
			// clear();
			alloc.destroy(start);
			alloc.deallocate(start, 1);
		}

		void insert(value_type value)
		{
			if (this->root == nullptr)
			{
				this->root = new node(value, BLACK);
				this->size++;
				return;
			}
			node_ptr current = this->root;
			while (current != nullptr)
			{
				if (value < current->value)
				{
					if (current->left == nullptr)
					{
						current->linkLeft(new node(value));
						this->size++;
						return;
					}
					current = current->left;
				}
				else if (value > current->value)
				{
					if (current->right == nullptr)
					{
						current->linkRight(new node(value));
						this->size++;
						return;
					}
					current = current->right;
				}
				else
				{
					return;
				}
			}
		}

		mapped_type getElementByKey(key_type const &k)
		{
			
		}

		node_ptr const &getStart() const
		{
			return start;
		}

		node_ptr const &getEnd() const
		{
			return end;
		}

		size_type const & getSize() const
		{
			return size;
		}

		allocator_type & getAllocator() const
		{
			return alloc;
		}
		// define clear()

	private:
		//TODO: change the type of the allocator at the end of dev 
		std::allocator<value_type> alloc;
		key_compare comp;
		node_ptr root;
		node_ptr start;
		node_ptr end;
		size_type size;
	}; // class BinarySearchTree

} // namespace ft

#endif //BINARY_SEARCH_TREE_HPP