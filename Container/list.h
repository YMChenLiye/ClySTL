#ifndef list_h
#define list_h

template<typename T>
class List{
	private:
		struct Node{
			T value;
			struct Node *prev;
			struct Node *next;
			Node(const T& d=T(),Node *p=nullptr,Node * n=nullptr):value(d),prev(p),next(n) { }
		};
	public:
		class const_iterator{
			public:
				const_iterator():current(nullptr) { }
				const T& operator*() const { return retrieve() ; }
				const_iterator & operator++()
				{
					current = current->next;
					return *this;
				}
				const_iterator & operator++(int)
				{
					const_iterator ret=*this;
					++(*this);
					return ret; 
				}

				bool operator==(const const_iterator &rhs) const { return current == rhs.current; }
				bool operator!=(const const_iterator &rhs) const { return !(*this == rhs); }

			protected:
				Node *current;
				T& retrieve() const { return current->value; }
				const_iterator (Node *p):current(p) { }
				friend class List<T>;

		};
		class iterator:public const_iterator 
		{
			public:
				iterator() { }
				T& operator*() { return const_iterator::retrieve(); }
				const T& operator*() const { return const_iterator::operator*(); }

				iterator& operator++()
				{
					const_iterator::current = const_iterator::current->next;
					return *this;
				}
				iterator operator++(int)
				{
					iterator ret = *this;
					++(*this);
					return ret;
				}
			protected:
				iterator(Node *p):const_iterator(p) { }

				friend	class List<T>;

		};
	public:
		List() { init(); }
		List(const List &rhs) { init(); *this = rhs; }
		~List() { clear(); delete head; delete tail; }
		const List & operator=(const List& rhs)
		{
			if(this == &rhs)
				return *this;
			clear();
			for(const_iterator itr = rhs.begin(); itr != rhs.end();++itr)
				push_back(*itr); 
			return *this;
		}

		iterator begin() { return iterator(head->next); }
		const_iterator begin() const { return const_iterator( head->next ); }
		iterator end() { return iterator(tail) ; }
		const_iterator end() const { return const_iterator(tail); }

		int size() const { return theSize; }
		bool empty() const { return size()==0 ; }

		void clear() {
			while(!empty())
				pop_front();
		}

		T& front() { return *begin(); }
		const T& front() const { return *begin(); }
		T& back() { return *--end(); }
		const T& back() const { return *--end(); }

		void push_front(const T& x) { insert(begin(),x) ; }
		void push_back(const T& x) { insert(end(),x) ; }
		void pop_front() { erase(begin()); }
		void pop_back() { erase(--end()); }

		iterator insert(iterator itr,const T& x)
		{
			Node *p=itr.current;
			theSize++;
			Node *newNode = new Node(x,p->prev,p);
			p->prev = p->prev->next = newNode;
			return iterator(newNode);
		}
		iterator erase(iterator itr)
		{
			Node *p = itr.current;
			iterator retVal(p->next);
			p->prev->next = p->next;
			p->next->prev = p->prev;
			delete p;
			theSize--;

			return retVal;
		
		}
		iterator erase(iterator start,iterator end)
		{
			for(iterator itr = start;itr !=end; )
				itr=erase(itr);
			return end;
		}
	private:
		int theSize;
		Node *head;
		Node *tail;

		void init()
		{
			theSize = 0;
			head = new Node;
			tail = new Node;
			head->next = tail;
			tail->prev = head;
		}
};



#endif
