// List.cpp
// Implementation file for List ADT.

#include "List.h"
#include <cstdio>


// Node constructor
List::Node::Node(ListElement x) {
   data = x;
   next = nullptr;
   prev = nullptr;
}

// Class Constructors & Destructors ----------------------------------------

// Creates new List in the empty state.
List::List() {
   frontDummy = new Node(0);  // You can use any value for the dummy nodes
   backDummy = new Node(0);
   beforeCursor = frontDummy;
   afterCursor = nullptr;
   pos_cursor = 0;
   num_elements = 0;
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
}

// Copy constructor.
List::List(const List& L) {
    // Initialize the new list, including dummy nodes
    frontDummy = new Node(0);
    backDummy = new Node(0);
    beforeCursor = frontDummy;
    afterCursor = nullptr;
    pos_cursor = num_elements = 0;
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;

    // Copy elements from L
    Node* temp = L.frontDummy->next;
    while (temp != nullptr) {
        insertBefore(temp->data);  // Insert at the front of the new list
        temp = temp->next;
    }

    // Set the cursor and position
    beforeCursor = frontDummy;
    afterCursor = (num_elements > 0) ? frontDummy->next : nullptr;
    pos_cursor = 0;
}

// Destructor
List::~List() {
    clear();  // Comment out the body temporarily
    delete frontDummy;
    delete backDummy;
}
// Access functions --------------------------------------------------------

// Returns the length of this List.
int List::length() const {
   return num_elements;
}

// Returns the front element in this List.
ListElement List::front() const {
   if (num_elements == 0) {
      throw std::length_error("List: front(): empty list");
   }
   return frontDummy->next->data;
}

// Returns the back element in this List.
ListElement List::back() const {
   if (num_elements == 0) {
      throw std::length_error("List: back(): empty list");
   }
   return backDummy->prev->data;
}

// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
   return pos_cursor;
}

// Returns the element after the cursor.
ListElement List::peekNext() const {
   if (pos_cursor == num_elements || afterCursor == nullptr) {
      throw std::range_error("List: peekNext(): cursor at back");
   }
   return afterCursor->data;
}

// Returns the element before the cursor.
ListElement List::peekPrev() const {
   if (pos_cursor == 0 || beforeCursor == nullptr) {
      throw std::range_error("List: peekPrev(): cursor at front");
   }
   return beforeCursor->data;
}

// Manipulation procedures -------------------------------------------------

// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
moveFront();
   while (num_elements > 0) {
      eraseAfter();
   }
}

// Moves cursor to position 0 in this List.
void List::moveFront() {
   pos_cursor = 0;
   beforeCursor = frontDummy;
   afterCursor = frontDummy->next;
}

// Moves cursor to position length() in this List.
void List::moveBack() {
   pos_cursor = num_elements;
   beforeCursor = backDummy->prev;
   afterCursor = nullptr;
}

// Advances cursor to next higher position. Returns the List element that
// was passed over.
// pre: position()<length() 
ListElement List::moveNext() {
   if (pos_cursor == num_elements || afterCursor == nullptr) {
      throw std::range_error("List: moveNext(): cursor at back");
   }
   beforeCursor = afterCursor;
   afterCursor = afterCursor->next;
   pos_cursor++;
   return beforeCursor->data;
}

// Advances cursor to next lower position. Returns the List element that
// was passed over.
// pre: position()>0
ListElement List::movePrev() {
   if (pos_cursor == 0 || beforeCursor == nullptr) {
      throw std::range_error("List: movePrev(): cursor at front");
   }
   afterCursor = beforeCursor;
   beforeCursor = beforeCursor->prev;
   pos_cursor--;
   if (pos_cursor == 0) {
      // If cursor is at the beginning, set beforeCursor to nullptr
      beforeCursor = nullptr;
   }

   return afterCursor->data;
}

// Inserts x after cursor.
void List::insertAfter(ListElement x) {
   Node* newNode = new Node(x);
   newNode->prev = beforeCursor;
   newNode->next = afterCursor;

   if (afterCursor != nullptr) {
      afterCursor->prev = newNode;
   } else {
      // If afterCursor is nullptr, we are inserting at the back
      backDummy->prev = newNode;
   }

   if (beforeCursor != nullptr) {
      beforeCursor->next = newNode;
   } else {
      // If beforeCursor is nullptr, we are inserting at the front
      frontDummy->next = newNode;
   }

   afterCursor = newNode;
   num_elements++;
}

// Inserts x before cursor.
void List::insertBefore(ListElement x) {
   Node* newNode = new Node(x);
   newNode->prev = beforeCursor;
   newNode->next = afterCursor;
   
   if (beforeCursor != nullptr) {
      beforeCursor->next = newNode;
   } else {
      frontDummy->next = newNode;
   }

   if (afterCursor != nullptr) {
      afterCursor->prev = newNode;
   } else {
      backDummy->prev = newNode;
   }
   beforeCursor = newNode;
   pos_cursor++;
   num_elements++;
}

// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x) {
   if (pos_cursor == num_elements || afterCursor == nullptr) {
      throw std::range_error("List: setAfter(): cursor at back");
   }
   afterCursor->data = x;
}

// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x) {
   if (pos_cursor == 0 || beforeCursor == nullptr) {
      throw std::range_error("List: setBefore(): cursor at front");
   }
   beforeCursor->data = x;
}

// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {
   if (pos_cursor == num_elements || afterCursor == nullptr) {
      throw std::range_error("List: eraseAfter(): cursor at back");
   }
   Node* temp = afterCursor;
   beforeCursor->next = afterCursor->next;
   if (afterCursor->next != nullptr) {
      afterCursor->next->prev = beforeCursor;
   } else {
      backDummy->prev = beforeCursor;
   }
   afterCursor = afterCursor->next;
   delete temp;
   num_elements--;
}

// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
    if (pos_cursor == 0 || beforeCursor == nullptr) {
        throw std::range_error("List: eraseBefore(): cursor at front");
    }

    Node* temp = beforeCursor;

    if (afterCursor != nullptr) {
        afterCursor->prev = beforeCursor->prev;
    }

    if (beforeCursor->prev != nullptr) {
        beforeCursor->prev->next = afterCursor;
    } else {
        // If erasing the front element, update frontDummy->next
        frontDummy->next = afterCursor;
    }

    beforeCursor = beforeCursor->prev;
    delete temp;
    pos_cursor--;
    num_elements--;
}

// Other Functions ---------------------------------------------------------

// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1.
int List::findNext(ListElement x) {
   while (afterCursor != nullptr && afterCursor->data != x) {
      moveNext();
   }

   if (afterCursor != nullptr) {
      moveNext();
      return pos_cursor;
   } else {
      moveBack();
      return -1;
   }
}

// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1.
int List::findPrev(ListElement x) {
   while (beforeCursor != nullptr && beforeCursor->data != x) {
      movePrev();
   }

   if (beforeCursor != nullptr) {
      movePrev();
      return pos_cursor;
   } else {
      moveFront();
      return -1;
   }
}

// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrence of each element, and removing all other occurrences. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
   Node* tempBeforeCursor = beforeCursor;
   Node* tempAfterCursor = afterCursor;

   Node* current = frontDummy->next;
   while (current != nullptr) {
      ListElement currentData = current->data;
      Node* runner = current->next;

      while (runner != nullptr) {
         if (runner->data == currentData) {
            // Duplicate found, remove it
            Node* temp = runner;
            runner = runner->next;

            // Update pointers to bypass the duplicate node
            temp->prev->next = runner;
            if (runner != nullptr) {
               runner->prev = temp->prev;
            } else {
               // If runner is null, update backDummy->prev
               backDummy->prev = temp->prev;
            }

            delete temp;  // Free the memory of the removed node
            num_elements--;
         } else {
            // No duplicate, move to the next node
            runner = runner->next;
         }
      }

      // Move to the next node
      current = current->next;
   }

   // Restore the cursor to its original position
   beforeCursor = tempBeforeCursor;
   afterCursor = tempAfterCursor;
   if (num_elements < pos_cursor) {
      pos_cursor = num_elements;
   }
}

// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at position 0.
List List::concat(const List& L) const {
   List result;
   Node* temp = frontDummy->next;
   while (temp != nullptr) {
      result.insertBefore(temp->data);
      temp = temp->next;
   }

   // Move the cursor to the end of the result list
   result.moveBack();

   temp = L.frontDummy->next;
   while (temp != nullptr) {
      result.insertBefore(temp->data);
      temp = temp->next;
   }

   // Move the cursor back to the beginning of the result list
   result.moveFront();

   return result;
}

// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
   std::string result = "(";
   Node* temp = frontDummy->next;
   while (temp != nullptr) {
      result += std::to_string(temp->data);
      if (temp->next != nullptr) {
         result += ", ";
      }
      temp = temp->next;
   }
   result += ")";
   return result;
}

// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
   if (num_elements != R.num_elements) {
      return false;
   }
   Node* temp1 = frontDummy->next;
   Node* temp2 = R.frontDummy->next;
   while (temp1 != nullptr) {
      if (temp1->data != temp2->data) {
         return false;
      }
      temp1 = temp1->next;
      temp2 = temp2->next;
   }
   return true;
}

// Overridden Operators ----------------------------------------------------

// Inserts string representation of L into stream.
std::ostream& operator<<(std::ostream& stream, const List& L) {
   stream << L.to_string();
   return stream;
}

// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==(const List& A, const List& B) {
   return A.equals(B);
}

// Overwrites the state of this List with the state of L.
List& List::operator=(const List& L) {
    if (this != &L) {
        // Clear the current list, excluding dummy nodes
        while (num_elements > 0) {
            eraseAfter();
        }

        // Copy elements from L
        Node* temp = L.frontDummy->next;
        while (temp != nullptr) {
            insertAfter(temp->data);
            temp = temp->next;
        }

        // Set the cursor and position
        beforeCursor = frontDummy;
        afterCursor = (num_elements > 0) ? frontDummy->next : nullptr;
        pos_cursor = 0;
    }
    return *this;
}