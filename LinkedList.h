#ifndef LinkedList_H
#define LinkedList_H

#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING 1

#include <iostream>
#include <vector>

//typedef double ListDataType;
#include "ListDataType.h"

struct ListNode {
	ListDataType data;
	ListNode* prev;
	ListNode* next;
};

class LinkedList {
    protected:
		ListNode* list_head;
    public:
		LinkedList() {
			list_head = nullptr;
		}
		ListNode* get_list_head() { return list_head; };
		void append_item(ListDataType data) {
			ListNode* new_node = new ListNode;
			new_node->data = data;
			new_node->next = nullptr;

			if (list_head == nullptr) {
				new_node->prev = nullptr;
				list_head = new_node;
				return;
			}
			ListNode* current = list_head;
			while (current->next != nullptr) {
				current = current->next;
			}
			new_node->prev = current;
			current->next = new_node;
			//	return list_head;
		}
		void print_list() {
			ListNode* current = list_head;
			while (current != nullptr) {
				std::cout << current->data << " ";
				current = current->next;
			}
			std::cout << std::endl;
		}
		// add item to list after specific position (1 is after first element, 2 is after second element)
		void add_item_after_position(ListDataType data, std::size_t position) {
			ListNode* new_node = new ListNode;
			new_node->data = data;
			new_node->next = nullptr;

			if (list_head == nullptr) {
				new_node->prev = nullptr;
				list_head = new_node;
				return;
			}

			//insert at start:
			if (position == 0) {
				new_node->prev = nullptr;
				new_node->next = list_head;
				list_head->prev = new_node;
				list_head = new_node;
				return;
			}

			ListNode* current = list_head;
			std::size_t current_position = 1;
			//if position is higher than the number of nodes, just append to end
			while ((current->next != nullptr) && (current_position < position)) {
				current = current->next;
				current_position++;
			}
			//changing next/prev parameters, so that current points to new_node, and new_mode node points to the node that the current was pointing to
			new_node->next = current->next;
			new_node->prev = current;
			//if next element exists
			if (current->next) {
				current->next->prev = new_node;
			}
			current->next = new_node;
		}
		void print_reverse() {
			ListNode* current = list_head;
			if (current == nullptr) { std::cout << std::endl; return; }
			while (current->next != nullptr) {
				current = current->next;
			}

			while (current != nullptr) {
				std::cout << current->data << " ";
				current = current->prev;
			}

			std::cout << std::endl;
		}
		void remove_item_at_position(std::size_t position) {
			if (list_head == nullptr) {
				return;
			}
			ListNode* current = list_head;
			std::size_t current_position = 0;
			//if position is higher than the number of nodes - don't remove, output error
			while ((current != nullptr) && (current_position < position)) {
				current = current->next;
				current_position++;
			}

			if (current == nullptr) {
				std::cout << "ERROR: trying to delete nonexistent element" << std::endl;
				return;
			}

			if (current == list_head) { //remove from start
				if (current->next == nullptr) { //remove single item, results in empty list
					list_head = nullptr;
				}
				else {
					list_head = current->next;
					list_head->prev = nullptr;
				}
				delete current;

				return;
			}

			ListNode* prev_node = current->prev;

			if (current->next == nullptr) { //remove from end
				prev_node->next = nullptr;
			}
			else { //remove in the middle
				ListNode* next_node = current->next;
				prev_node->next = next_node;
				next_node->prev = prev_node;
			}
			delete current;
		}
		void remove_entire_list() {
			ListNode* current = list_head;

			while (current != nullptr) {
				ListNode* to_delete = current;
				current = current->next;
				delete to_delete;
			}
			list_head = nullptr;
		}
		size_t length() {
			size_t counter = 0;
			ListNode* current = list_head;
			while (current != nullptr) {
				counter++;
				current = current->next;
			}
			return counter;
		}
		ListNode* find_by_value(ListDataType value) {
			ListNode* current = list_head;
			while (current != nullptr) {
				if (current->data == value) {
					std::cout << "data found: " << current->data << std::endl;
					return current;
				}

				current = current->next;
			}
			std::cout << "no node with value " << value << " found" << std::endl;
			return nullptr;
		}
		//Adapter Pattern, between linked list and vector:
		std::vector<ListDataType> convert_to_vector() {
			std::vector<ListDataType> return_vector;
			ListNode* current = list_head;
			while (current != nullptr) {
				return_vector.push_back(current->data);
				current = current->next;
			}
			return return_vector;
		}
		void replace_listnodes_with_vector_values(std::vector<ListDataType> inputvector) {
			remove_entire_list();
			for (unsigned int i = 0; i < inputvector.size(); i++) {
				append_item(inputvector[i]);
			}
		}
		//Iterator Pattern:
		class iterator : public std::iterator<
			std::input_iterator_tag,   // iterator_category
			ListDataType,                      // value_type
			ListDataType,                      // difference_type
			const ListDataType*,               // pointer
			ListDataType                       // reference
		> {
			ListNode* where = nullptr;
		public:
			explicit iterator(ListNode* _where = nullptr) : where(_where) {}
			iterator& operator++() {
			    if(where != nullptr){ where = where->next;};
			    return *this;
			}
			iterator operator++(int) { iterator retval = *this; ++(*this); return retval; }
			bool operator==(iterator other) const { return where == other.where; }
			bool operator!=(iterator other) const { return !(*this == other); }
			reference operator*() const { return where->data; }
		};
		iterator begin() { return iterator(list_head); }
		iterator end() { return iterator(nullptr); }

		void process(ProcessDataStrategy& processor) {
			for (ListDataType val: *this) {processor.process(val);};
		};
};

#endif //LinkedList_H
