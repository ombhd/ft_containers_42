/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_tree.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 16:15:06 by obouykou          #+#    #+#             */
/*   Updated: 2021/10/09 16:13:29 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <iostream>
#include <cstdio>

#include "utils.hpp"
#include "pair.hpp"

#define RED true
#define BLACK false
#define RIGHT 'R'
#define LEFT 'L'
#define NONE 'N'

// TODO: to remove
#define check std::cout << "============ > checked < ===========" << std::endl;

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

		TreeNode(TreeNode const &other)
			: color(other.color),
			  isRightChild(other.isRightChild),
			  parent(other.parent),
			  left(other.left),
			  right(other.right),
			  value(other.value)
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

		void copyLinks(node_ptr node)
		{
			node->parent = this->parent;
			if (this->parent != nullptr)
			{
				if (this->isRightChild)
					node->parent->right = node;
				else
					node->parent->left = node;
			}
			node->left = this->left;
			if (node->left != nullptr)
				node->left->parent = node;
			node->right = this->right;
			if (node->right != nullptr)
				node->right->parent = node;
			node->isRightChild = this->isRightChild;
		}

		bool isLeaf(node_ptr end) const
		{
			return (this->left == end && (this->right == end || this->right == nullptr));
		}

		ft::pair<node_ptr, bool> hasOnlyOneChild(node_ptr end) const
		{
			if (this->left == nullptr && (this->right != nullptr && this->right != end))
				return ft::make_pair(this->right, true);
			if (this->left != nullptr && (this->right == nullptr || this->right == end))
				return ft::make_pair(this->left, false);
			return ft::make_pair(nullptr, false);
		}

	}; // struct TreeNode

	// TreeIterator : Binary Search Tree Iterator definition
	template <typename T>
	class TreeIterator : public iterator<std::bidirectional_iterator_tag,
										 typename ft::iterator_traits<T *>::value_type>
	{
	public:
		typedef TreeNode<T> *node_ptr;
		typedef T value_type;

		TreeIterator(node_ptr pos = nullptr) : current(pos), end(findEnd())
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
			if (this->current == nullptr)
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

		node_ptr const &asPointer() const
		{
			return this->current;
		}

	protected:
		node_ptr current;
		node_ptr end;

		// find the end node of binary search tree
		node_ptr findEnd()
		{
			node_ptr end = this->current;
			while (end->parent != nullptr)
				end = end->parent;
			while (end->right != nullptr)
				end = end->right;
			return end;
		}
	};

	// BinarySearchTree class definition
	template <typename T, class Compare = std::less<typename T::first_type>, class Alloc = std::allocator<TreeNode<T> > >
	class BinarySearchTree
	{
	public:
		typedef T value_type;
		typedef typename value_type::first_type key_type;
		typedef typename value_type::second_type mapped_type;
		typedef TreeNode<T> node;
		typedef TreeNode<T> *node_ptr;
		typedef size_t size_type;
		// typedef Alloc allocator_type;
		typedef Compare key_compare;
		typedef TreeIterator<value_type> iterator;
		typedef typename Alloc::template rebind<TreeNode<T> >::other allocator_type;

		BinarySearchTree(const key_compare &comp = key_compare(),
						 const allocator_type &alloc = allocator_type()) : alloc(alloc),
																		   comp(comp),
																		   root(this->alloc.allocate(1)),
																		   start(root),
																		   end(root),
																		   size(0)
		{
			this->alloc.construct(root, node());
		}
		~BinarySearchTree()
		{
			clear();
			this->alloc.destroy(end);
			this->alloc.deallocate(end, 1);
		}

		iterator getStart() const
		{
			return iterator(start);
		}

		iterator getEnd() const
		{
			return iterator(end);
		}

		size_type const &getSize() const
		{
			return size;
		}

		allocator_type &getAllocator() const
		{
			return this->alloc;
		}

		// define insert_left
		ft::pair<iterator, bool> insert_left(node_ptr current, value_type const &value)
		{
			current->linkLeft(new_node(value));
			this->size++;
			this->start = current->left;
			return ft::make_pair(iterator(current->left), true);
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
			this->root->right = end;
			end->parent = root;
			return ft::make_pair(iterator(this->root), true);
		}

		// define insert
		ft::pair<iterator, bool> insert(value_type const &value)
		{
			std::cout << "inserting pair :[" << value.first << "]=" << value.second << " ==> ";
			if (this->root == end)
			{
				std::cout << "root" << std::endl;
				return build_root(value);
			}
			node_ptr current = this->root;
			while (current != nullptr)
			{
				if (!comp(value.first, current->value.first) && !comp(current->value.first, value.first))
				{
					check return ft::make_pair(iterator(current), false);
				}

				else if (comp(value.first, current->value.first))
				{
					if (current->left == nullptr)
					{
						std::cout << "left" << std::endl;
						return (insert_left(current, value));
					}
					current = current->right;
				}
				else
				{

					if (current->right == this->end)
					{
						std::cout << "right" << std::endl;
						return insert_right(current, value);
					}
					current = current->left;
				}
			}
			return ft::make_pair(iterator(current), false);
		}

		// define insert with hint
		iterator insert(iterator hint, value_type const &value)
		{

			ft::pair<iterator, bool> result;
			if (hint.current->left == nullptr && comp(hint.current->value.first, value.first))
			{
				std::cout << "insert left" << std::endl;
				result = insert_left(hint.current, value);
			}
			else if (hint.current->right == nullptr && comp(value.first, hint.current->value.first))
			{
				std::cout << "insert right" << std::endl;
				result = insert_right(hint.current, value);
			}
			else
				result = insert(value);
			return result.first;
		}

		void removeLeafNode(node_ptr node)
		{
			if (node == start)
				start = (node->parent == nullptr) ? end : node->parent;
			this->alloc.destroy(node);
			this->alloc.deallocate(node, 1);
			this->size--;
		}

		void removeNodeWithOneChild(node_ptr node)
		{
			node_ptr child = (node->hasOnlyOneChild(end)).first;
			if (node == start)
				start = (child == node->left) ? child : ((node->parent == nullptr) ? end : node->parent);
			if (node->parent != nullptr)
			{
				if (node->isRightChild)
					node->parent->right = child;
				else
					node->parent->left = child;
			}
			else
			{
				findMax(child)->right = end;
				root = child;
			}
			child->parent = node->parent;
			this->alloc.destroy(node);
			this->alloc.deallocate(node, 1);
			this->size--;
		}

		void removeByPosition(iterator const &it)
		{
			node_ptr ptr = it.asPointer();
			if (size == 0 || ptr == nullptr || ptr == end)
				return;

			// case 1: leaf node
			if (ptr->isLeaf(end))
			{
				removeLeafNode(ptr);
			}

			// case 2: node with one child
			else if (ptr->hasOnlyOneChild(end).second)
			{
				removeNodeWithOneChild(ptr);
			}

			// case 3: node with two children
			else
			{
				node_ptr successor = findMin(ptr->right);
				node_ptr holder = alloc.allocate(1);
				alloc.construct(holder, successor->value);
				ptr->copyLinks(holder);
				alloc.destroy(ptr);
				alloc.deallocate(ptr, 1);
				removeByPosition(iterator(successor));
			}
		}

		void swap(BinarySearchTree &other)
		{
			std::swap(this->root, other.root);
			std::swap(this->start, other.start);
			std::swap(this->end, other.end);
			std::swap(this->size, other.size);
			std::swap(this->comp, other.comp);
			std::swap(this->alloc, other.alloc);
		}

		void clear()
		{
			// node_ptr current = this->root == end ? nullptr : this->root;
			// node_ptr parent = nullptr;
			// while (current != nullptr)
			// {
			// 	if (current->left == nullptr)
			// 	{
			// 		if (parent != nullptr)
			// 		{
			// 			if (parent->left == current)
			// 				parent->left = current->right;
			// 			else
			// 				parent->right = current->right;
			// 		}
			// 		else
			// 			this->root = current->right;
			// 		this->alloc.destroy(current);
			// 		this->alloc.deallocate(current, 1);
			// 		current = parent;
			// 	}
			// 	else
			// 	{
			// 		parent = current;
			// 		current = current->left;
			// 	}
			// }
			// this->size = 0;
			iterator it = this->getStart();
			while (it != this->getEnd())
			{
				removeByPosition(it++);
			}
		}

		key_compare getComp() const
		{
			return comp;
		}

		iterator findByKey(const key_type &key)
		{
			node_ptr current = this->root;
			while (current != nullptr)
			{
				if (comp(key, current->value.first))
					current = current->left;
				else if (comp(current->value.first, key))
					current = current->right;
				else
					return iterator(current);
			}
			return iterator(end);
		}

	private:
		// private data members
		allocator_type alloc;
		key_compare comp;
		node_ptr root;
		node_ptr start;
		node_ptr end;
		size_type size;

		// private member methods

		node_ptr new_node(value_type const &value, bool const &color = BLACK)
		{
			node_ptr newNode = this->alloc.allocate(1);
			this->alloc.construct(newNode, node(value, color));
			return newNode;
		}

		// define find min
		node_ptr findMin(node_ptr curr_root)
		{
			if (curr_root != nullptr && curr_root != end)
			{
				while (curr_root->left != nullptr)
					curr_root = curr_root->left;
			}
			return curr_root;
		}

		// define find max
		node_ptr findMax(node_ptr curr_root)
		{
			if (curr_root != nullptr && curr_root != end)
			{
				while (curr_root->right != nullptr && curr_root->right != end)
					curr_root = curr_root->right;
			}
			return curr_root;
		}
	}; // class BinarySearchTree

} // namespace ft

#endif //BINARY_SEARCH_TREE_HPP