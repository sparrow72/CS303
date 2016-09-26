#ifndef ORDERED_LIST_H_
#define ORDERED_LIST_H_
#include "list.h"

/* The ordered list maintains a list of objects ordered by their less-than operator*/
template<typename Item_Type>
class Ordered_List {

private:
	/**A list to contain the ordered list*/
	list<Item_Type> a_list;

public:
	//Typedefs
	typedef typename list<Item_Type>::const_iterator const_iterator;

	//Functions
	/** inserts a new item into the ordered list, maintaining order.
	@param an_item The item to be inserted
	*/
	void insert(const Item_Type& an_item){
		typename list<Item_Type>::iterator itr = a_list.begin();
		
		while (itr != a_list.end() && *itr < an_item)
			++itr; //itr points to the first item >= an_item
			//or the end
		a_list.insert(itr, an_item);
		
	}

	/** Remove an item from the ordered list.
	@param item The value to be removed
	*/
	void remove(const Item_Type& item){
		a_list.remove(item);
	}

	/** Return an iterator to the begining */
	const_iterator begin() const{
		return a_list.begin();
	}

	/** Return an iterator to the end */
	const_iterator end() const {
		return a_list.end();
	}

};

#endif