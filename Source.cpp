#include <iostream>
#include <vector>

struct ListNode {
	int data;
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
		void append_item(int data) {
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
		void add_item_after_position(int data, std::size_t position) {
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
		ListNode*& find_by_value(int value) {
			ListNode* current = list_head;
			while (current != nullptr) {
				if (current->data == value) {
					std::cout << "data found: " << current->data << std::endl;
					return current;
				}

				current = current->next;
			}
			std::cout << "no node with value " << value << " found" << std::endl;
		}
		//Adapter Pattern, between linked list and vector:
		std::vector<int> convert_to_vector() {
			std::vector<int> return_vector;
			ListNode* current = list_head;
			while (current != nullptr) {
				return_vector.push_back(current->data);
				current = current->next;
			}
			return return_vector;
		}
};

int main() {

	LinkedList test_list;

	test_list.append_item(1);
	test_list.append_item(5);
	test_list.append_item(9);
	test_list.add_item_after_position(6, 1);
	std::cout << "print: " << std::endl;
	test_list.print_list();
	std::cout << "print reverse: " << std::endl;
	test_list.print_reverse();
	std::cout << "print after deleting first element: " << std::endl;
	test_list.remove_item_at_position(0);
	test_list.print_list();
	std::cout << "delete entire list then add 5: " << std::endl;
	test_list.remove_entire_list();
	test_list.append_item(5);
	test_list.print_list();

	//Adapter pattern, converting the linked list into vector:
	std::vector<int> converted_vector = test_list.convert_to_vector();

	return 0;
}