#include <cstddef>


template<typename Item_Type>
class list {

private:
	struct DNode {
		// Data Fields
		/** The data */
		Item_Type data;
		/** The pointer to the next node. */
		DNode* next;

		/** The pointer to the previous node. */
		DNode* prev;

		// Constructor
		DNode(const Item_Type& data_item, DNode* prev_val = NULL, DNode* next_val = NULL) :
			data(data_item), prev(prev_val), next(next_val) {}
	};

	// Data fields
	/** A reference to the head of the list */
	DNode* head;
	/** A reference to the end of the list */
	DNode* tail;
	/** The size of the list */
	size_t num_items;

public:

	// Insert definition of nested class iterator here.
#include "list_iterator.h"
	// Give iterator access to private members of list.
	friend class iterator;
	
	// Insert definition of nested class const_iterator here.
#include "list_const_iterator.h"
	// Give const_iterator access to private members of list.
	friend class const_iterator;
	
	
	/** Construct an empty list. */
	list() : head(NULL), tail(NULL), num_items(0) { }

	/** Construct a copy of a list. */
	list(const list<Item_Type>& other) : head(NULL),
		tail(NULL), num_items(0) {
		for (const_iterator itr = other.begin(); itr != other.end(); ++itr) {
			push_back(*itr);
		}
	}
	

	/** Destroy a list. */
	~list() {
		while (head != NULL) {
			DNode* current = head;
			head = head->next;
			delete current;
		}
		tail = NULL;
		num_items = 0;
	}

	/** Return an interator to the beginning of the list */
	iterator begin() {
		return iterator(this, head);
	}

	/** Return a const_iterator to the beginning of the list */
	const_iterator begin() const {
		return const_iterator(this,head);
	}

	/** Return an iterator to the end of the list */
	iterator end(){
		return iterator(this, NULL);
	}

	/** Return a const_iterator to the end of the list */
	const_iterator end() const{
		return const_iterator(this, NULL);
	}

	/** Assign the contents of one list to another. */
	list<Item_Type>& operator=(const list<Item_Type>& other) {
		// Make a copy of the other list.
		list<Item_Type> temp_copy(other);
		// Swap contents of self with the copy.
		swap(temp_copy);
		// Return -- upon return the old value will be destroyed.
		return *this;
	}

	void push_front(const Item_Type& item) {
		head = new DNode(item, NULL, head); // Step 1
		if (head->next != NULL)
			head->next->prev = head;  // Step 2
		if (tail == NULL)    // List was empty.
			tail = head;
		num_items++;
	}

	void push_back(const Item_Type& item) {
		if (tail != NULL) {
			tail->next = new DNode(item, tail, NULL); // Step 1
			tail = tail->next; // Step 2
			num_items++;
		}
		else {         // List was empty.
			push_front(item);
		}
	}

	void pop_front() {
		if (head == NULL)
			throw std::invalid_argument
			("Attempt to call pop_front() on an empty list");
		DNode* removed_node = head;
		head = head->next;
		delete removed_node;
		if (head != NULL)
			head->prev = NULL;
		else
			tail = NULL;
		num_items--;
	}


	void pop_back() {
		if (tail == NULL)
			throw std::invalid_argument
			("Attempt to call pop_back() on an empty list");
		DNode* removed_node = tail;
		tail = tail->prev;
		delete removed_node;
		if (tail != NULL)
			tail->next = NULL;
		else
			head = NULL;
		num_items--;
	}

	iterator insert(iterator pos, const Item_Type& item) {
		// Check for special cases
		if (pos.current == head) {
			push_front(item);
			return begin();
		}
		else if (pos.current == NULL) {  // Past the last node.
			push_back(item);
			return iterator(this, tail);
		}
		// Create a new node linked before node referenced by pos.
		DNode* new_node = new DNode(item,
			pos.current->prev,
			pos.current); // Step 1
		// Update links
		pos.current->prev->next = new_node;     // Step 2
		pos.current->prev = new_node;           // Step 3
		num_items++;
		return iterator(this, new_node);
	}

	void remove(const Item_Type& item){
		DNode* current_node = head;

		while (current_node != NULL){

			if (current_node->data == item){
				if (current_node->next == NULL)//the last element in the list
					return pop_back();

				if (current_node == head) //if the node we are deleting is the head
					head = current_node->next;

				DNode* to_be_deleted = current_node;
				current_node->next->prev = current_node->prev;
				if (current_node->prev != NULL)
					current_node->prev->next = current_node->next;

				current_node = current_node->next;
				delete to_be_deleted;
				num_items--;
			}
			else
				current_node = current_node->next;
		}
	}
	
	
	iterator erase(iterator pos) {
		if (empty())
			throw std::invalid_argument("Attempt to call erase on an empty list");
		if (pos.current == NULL)
			throw std::invalid_argument("Attempt to call erase of end()");
		// Create an iterator that references the position following pos.
		iterator return_value = pos;
		++return_value;
		// Check for special cases.
		if (pos.current == head) {
			pop_front();
			return return_value;
		}
		else if (pos.current == tail) {
			pop_back();
			return return_value;
		}
		else {  // Remove a node in the Item_Typeerior of the list.
			// Unlink current node.
			DNode* removed_node = pos.current;
			removed_node->prev->next = removed_node->next;
			removed_node->next->prev = removed_node->prev;
			delete removed_node;
			return return_value;
		}
	}

	bool empty(){
	
		return num_items == 0;
	}


	Item_Type& back(){
		if (tail != NULL)
			return tail->data;
		return NULL;
	}

	const Item_Type& back() const {
		if (tail != NULL)
			return tail->data;
		return NULL;
	}


	Item_Type& front(){
		if (head != NULL)
			return head->data;
		return NULL;
	}

	const Item_Type& front() const {
		if (head != NULL)
			return head->data;
		return NULL;
	}

	void swap(list<Item_Type> other){

	}

	size_t size() const{
		return num_items;
	}

	iterator find(Item_Type target) {
		for (iterator itr = begin(); itr != end(); ++itr) {
			if (*itr == target)
				return itr;
		}
		return end();
	}

};

