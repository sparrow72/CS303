#ifndef D_LINKED_LIST_CONST_ITERATOR_H_
#define D_LINKED_LIST_CONST_ITERATOR_H_

class const_iterator {
	// Give the parent class access to this class.
	friend class list<Item_Type>;

private:
	// Data fields
	/** A reference to the parent list */
     const list<Item_Type>* parent;
	/** A pointer to the current DNode */
	typename list<Item_Type>::DNode* current;
	// Member functions
	/** Constructs an iterator that references a specific DNode.
	Note: this constructor is private. Only the list class
	can create one from scratch.
	@param my_parent A reference to the list
	@param position A pointer to the current DNode
	*/
	const_iterator(const list<Item_Type>* my_parent, DNode* position) :
		parent(my_parent), current(position) {}
	
	
	/** Returns a reference to the currently referenced item.
	@return A reference to the currently referenced item
	@throws std::invalid_argument if this iterator is at end
	*/
public:
	const Item_Type& operator*() const {
		if (current == NULL)
			throw std::invalid_argument
			("Attempt to dereference end()");
		return current->data;
	}


	/** Returns a pointer to the currently referenced item.
	Item_Type must be a class or struct. This restriction
	is enforced by the compiler.
	@return A pointer to the currently referenced item
	@throws std::invalid_argument If this iterator is at end
	*/
	const Item_Type* operator->() const {
		if (current == NULL)
			throw std::invalid_argument
			("Attempt to dereference end()");
		return &(current->data);
	}


	const_iterator& operator++() {
		if (current == NULL)
			throw std::invalid_argument("Attempt to advance past end()");
		current = current->next;
		return *this;
	}


	const_iterator& operator--() {
		if (current == parent->head)
			throw std::invalid_argument("Attempt to move before begin()");
		if (current == NULL)   // Past last element.
			current = parent->tail;
		else
			current = current->prev;
		return *this;
	}

	const_iterator operator++(int) {
		// Make a copy of the current value.
		const_iterator return_value = *this;
		// Advance self forward.
		++(*this);
		// Return old value.
		return return_value;   // Return the value prior to increment
	}

	const_iterator  operator--(int) {
		// Make a copy of the current value.
		const_iterator return_value = *this;
		// Move self backward.
		--(*this);
		// Return old value.
		return return_value;   // Return the value prior to decrement
	}

	//Compare for equality
	bool operator ==(const const_iterator& other){
		return current == other.current;
	}

	//Not equal
	bool operator !=(const const_iterator&other){
		return current != other.current;
	}
};

#endif
