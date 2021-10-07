/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_tree.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 16:15:06 by obouykou          #+#    #+#             */
/*   Updated: 2021/10/07 18:55:41 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <iostream>

#include "utils.hpp"
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
			nodePtr->right = this->right;
			this->right = nodePtr;
			nodePtr->isRightChild = true;
		}

		void linkLeft(node_ptr nodePtr)
		{
			nodePtr->parent = this;
			this->left = nodePtr;
			nodePtr->isRightChild = false;
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
	class TreeIterator : public iterator<std::bidirectional_iterator_tag,
										 typename ft::iterator_traits<T>::value_type>
	{
	public:
		typedef TreeNode<T> *node_ptr;
		typedef T value_type;

		TreeIterator(node_ptr pos = nullptr) : current(pos), comp(Compare()), end(findEnd())
		{
		}

		TreeIterator(TreeIterator const &other)
		{
			*this = other;
		}

		TreeIterator &operator=(TreeIterator const &other)
		{
			if (this != &other)
			{
				this->current = other.current;
				this->comp = other.comp;
				this->end = other.end;
			}
			return *this;
		}
		~TreeIterator() {}

		bool operator==(TreeIterator const &other) const
		{
			return (this->current == other.current);
		}

		bool operator!=(TreeIterator const &other) const
		{
			return (this->current != other.current);
		}

		value_type &operator*() const
		{
			return this->current->value;
		}

		value_type *operator->() const
		{
			return &(this->current->value);
		}

		TreeIterator &operator++()
		{
			if (this->current == this->end)
				return *this;
			if (this->current->right != nullptr)
			{
				this->current = this->current->right;
				while (this->current->left != nullptr)
					this->current = this->current->left;
			}
			else
			{
				while (this->current->isRightChild)
				{
					this->current = this->current->parent;
				}
				this->current = this->current->parent;
			}
			return *this;
		}

		TreeIterator operator++(int)
		{
			TreeIterator tmp(*this);
			++(*this);
			return tmp;
		}

		TreeIterator &operator--()
		{
			if (this->current == this->start)
				return *this;
			if (this->current->left != nullptr)
			{
				this->current = this->current->left;
				while (this->current->right != nullptr)
					this->current = this->current->right;
			}
			else
			{
				if (this->current->isRightChild)
				{
					this->current = this->current->parent;
				}
			}
			return *this;
		}

		TreeIterator operator--(int)
		{
			TreeIterator tmp(*this);
			--(*this);
			return tmp;
		}

	private:
		Compare comp;
		node_ptr current;
		node_ptr end;

		// find the end node of binary search tree
		node_ptr findEnd()
		{
			node_ptr end = this->current;
			while (end->right != nullptr)
				end = end->right;
			return end;
		}
	};

	template <typename T, class Compare>
	class TreeReverseIterator : public TreeIterator<T, Compare>
	{
	public:
		typedef TreeNode<T> *node_ptr;
		typedef T value_type;

		TreeReverseIterator(node_ptr pos = nullptr) : TreeIterator<T, Compare>(pos)
		{
		}

		TreeReverseIterator(TreeReverseIterator const &other)
		{
			*this = other;
		}

		

	private:
		Compare comp;
		node_ptr current;
		node_ptr end;

		// find the end node of binary search tree
		node_ptr findEnd()
		{
			node_ptr end = this->current;
			while (end->right != nullptr)
				end = end->right;
			return end;
		}
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
		typedef TreeIterator<value_type, key_compare> iterator;

		BinarySearchTree(const key_compare &comp = key_compare(),
						 const allocator_type &alloc = allocator_type()) : alloc(alloc),
																		   comp(comp),
																		   root(alloc.allocate(1)),
																		   start(root),
																		   end(root),
																		   size(0)
		{
			alloc.construct(root, node());
		}
		~BinarySearchTree()
		{
			clear();
			alloc.destroy(start);
			alloc.deallocate(start, 1);
		}

		node_ptr const &getStart() const
		{
			return start;
		}

		node_ptr const &getEnd() const
		{
			return end;
		}

		size_type const &getSize() const
		{
			return size;
		}

		allocator_type &getAllocator() const
		{
			return alloc;
		}

		mapped_type &getElementByKey(key_type const &k)
		{
		}

		// define insert_left
		ft::pair<iterator, bool> insert_left(node_ptr current, value_type const &value)
		{
			current->linkLeft(new_node(value));
			this->size++;
			this->start = this->current->left;
			return ft::make_pair(iterator(current->right), true);
		}

		// define insert_right
		ft::pair<iterator, bool> insert_right(node_ptr current, value_type const &value)
		{
			current->linkRight(new_node(value));
			this->size++;
			return ft::make_pair(iterator(current->right), true);
		}

		// define build root
		ft::pair<iterator, bool> build_root(value_type const &value)
		{
			this->root = new_node(value, BLACK);
			this->size++;
			this->start = this->root;
			return ft::make_pair(iterator(this->root), true);
		}

		// define insert
		ft::pair<iterator, bool> insert(value_type const &value)
		{
			if (this->root == end)
				return build_root(value);
			node_ptr current = this->root;
			while (current != nullptr)
			{
				if (!comp(value->first, current->value->first) && !comp(current->value->first, value->first))
					return ft::make_pair(iterator(current), false);
				else if (comp(value->first, current->value->first))
				{
					if (current->left == nullptr)
						return (insert_left(current, value));
					current = current->right;
				}
				else
				{
					if (current->right == this->end)
						return insert_right(current, value);
					current = current->left;
				}
			}
		}

		// define insert with hint
		iterator insert(iterator hint, value_type const &value)
		{
			ft::pair<iterator, bool> result;
			if (hint.current->left == nullptr && comp(hint.current->value.first, value.first))
				result = insert_left(hint.current, value);
			else if (hint.current->right == nullptr && comp(value.first, hint.current->value.first))
				result = insert_right(hint.current, value);
			else
				result = insert(value);
			return result.first;
		}

		iterator removeByKey(const key_type &key)
		{
			node_ptr current = this->root;
			node_ptr parent = nullptr;
			while (current != nullptr)
			{
				if (comp(key, current->value->first))
				{
					parent = current;
					current = current->left;
				}
				else if (comp(current->value->first, key))
				{
					parent = current;
					current = current->right;
				}
				else
				{
					if (current->left == nullptr)
					{
					}
					else if (current->right == this->end)
					{
					}
					else
					{
					}
				}
			}
			return iterator();
		}

		void removeByPosition(iterator &it)
		{
		}

		void clear()
		{
			// TODO: implement clear() methodd
		}

	private:
		// private data members
		//TODO: change the type of the allocator at the end of dev
		std::allocator<value_type> alloc;
		key_compare comp;
		node_ptr root;
		node_ptr start;
		node_ptr end;
		size_type size;

		// private member methods

		node_ptr new_node(value_type const &value, bool const &color)
		{
			node_ptr newNode = alloc.allocate(1);
			alloc.construct(newNode, node(value, color));
			return newNode;
		}
	}; // class BinarySearchTree

} // namespace ft

#endif //BINARY_SEARCH_TREE_HPP