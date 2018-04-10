#include<iostream>
using namespace std;

template<class T>
class QueueLL {
	class Node {
		public:
			T data;
			Node* next;
	};

	Node* front;
	Node* back;
	int size;

	public:
		QueueLL() {
			front = NULL;
			back = NULL;
			size = T(NULL);
		}

		/*
		 * Member Functions:
		 *	 void queue(T d);
		 *	 T dequeue();
		 *	 void empty();
		 *	 void display();
		 */


		void queue(T d) {
		/*
		 * Creates a new node and adds it to the end of the queue.
		 */
			Node* new_node = new Node;
			new_node->data = d;
		
			if (size == 0) {
				new_node->next = NULL;
				front = new_node;
			} else {
				new_node->next = back;
			}
			back = new_node;
			++size;
		}

		T dequeue() {
		/*
		 * Removes the node at the front of the queue
		 * Returns the value of the data stored in the removed node.
		 */
			T x;
			if (size == 0) {
				cout << "List empty. Nothing to do." << endl;
				return T(NULL);
			} else if (size == 1) {
				Node* temp = front;
				front = NULL;
				back = NULL;

				 x = temp->data;
				delete temp;
			} else {
				Node* p = back;
				while (p->next != front) {
					p = p->next;
				}
		
				Node* temp = front;
				p->next = NULL;
				front = p;

				x = temp->data;
				delete temp;
			}

			--size;
			return x;
		}

		void empty() {
		/*
		 * Empties the queue. Deletes all elements, sets size to zero
		 */
			while (size > 0) {
				dequeue();
			}
		}

		void display() {
		/*
		 * Displays all the elements of the queue from front to back
		 */
			if (size == 0) {
				cout << "List empty. Nothing to do." << endl;
				return;
			}
		
			Node* p = back;
			while (p != NULL) {
				cout << p->data << "->";
				p = p->next;
			}
			cout << "NULL" << endl;
		}
};
