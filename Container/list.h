#ifndef list_h
#define list_h
#include <memory>

template<typename T>
class list{
	public:
		struct node{
			T val;
			T* next;
			T* prev;
		};
		struct listIterator{
			typedef struct node* nodePtr;
			nodePtr p;

			explicit listIterator(nodePtr ptr = nullptr):p(ptr) { }
			listIterator& operator++()
			{
				p=p->next;
				return *this;
			}
			listIterator& operator++(int)
			{
				listIterator ret=*this;
				p=p->next;
				return ret;
			}
			listIterator& operator--()
			{
				p=p->prev;
				return *this;
			}
			listIterator& operator--(int)
			{
				listIterator ret=*this;
				p=p->prev;
				return ret;
			}

			T& operator*() { return p->val; }
			T* operator->() { return &(operator*()); }
		};


		typedef T										value_type;
		typedef Allocator 								allocator_type;
		typedef size_t 									size_type;
		typedef std::ptrdiff_t 							difference_type;
		typedef value_type& 							reference;
		typedef const value_type& 						const_reference;
		typedef struct node * 							nodePtr;

	private:
		listIterator begin_;
		listIterator end_;
		size_type count;
		std::allocator<struct node> allocNode;
		std::allocator<struct listIterator> allocIter;
		listIterator alloc_one()
		{
			nodePtr p= allocNode.allocate(1);
			listIterator iter=allocIter.allocate(1);
			iter.p=p;
			iter.p->val=T();
			iter.p->prev=nullptr;
			iter.p->next=nullptr;
			return iter;
		}

	public:
		//member function
		list(): begin_(nullptr),end_(nullptr) { }
		list(std::initializer_list<T> il);
		list(const list& v);
		list(list&& v);
		list& operator=(const list& v);
		list& operator=(list&& v);

		//Element access
		reference front() const { return begin_.p->val; }
		reference back() const { return end_.p->prev->val; }

		//Iterator
		listIterator begin() { return begin_; }
		const listIterator cbegin() const { return begin_; }
		listIterator end() { return end_; }
		const initializer_list cend() const { return end_; }
		
		//Capacity
		bool empty() const { return begin_==end_; }
		size_type size() const { return count; }

		//Modifiers
		void clear();
		void push_back(value_type &val);
		void push_front(value_type &val);
		void pop_back();
		void pop_front();
};

template<typename T>
void list<T>::push_back(value_type &val)
{
	if(empty())
	{
		push_front(val);
	}

	listIterator ret = alloc_one();
	nodePtr pos=ret.p;
	pos->val = val;
	nodePtr last=end_.p->prev;
	pos->next = end_.p;
	pos.prev = last;
	last->next = pos;
	end_.p->prev = pos;
}

template<typename T>
void list<T>::push_front(value_type& val)
{
	listIterator ret = alloc_one();
	nodePtr pos = ret.p;
	pos->val = val;
	if(empty())
	{
		begin_.p=pos;
		end_.p->prev=pos;
	}
	nodePtr first=begin_.p;
	begin_.p=pos;
	pos->next = first;
	first->prev = pos;
}






}

#endif
