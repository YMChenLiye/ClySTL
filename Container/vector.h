#ifndef vector_h
#define vector_h
#include <memory>

template<typename T>
class stl_vector{
	public:
		//constructor,copy-control,destructor
		stl_vector():elements(nullptr),first_free(nullptr),cap(nullptr) { }
		stl_vector(const size_t n,const T &val);
		stl_vector(const stl_vector& v);
		stl_vector(stl_vector&& v);
		stl_vector(std::initializer_list<T> il);
		stl_vector& operator=(const stl_vector& v);
		stl_vector& operator=(stl_vector&& v);
		~stl_vector();

		//compare
		bool operator==(const stl_vector& v)const;
		bool operator!=(const stl_vector& v)const;

		//iterator
		T* begin() const { return elements; }
		const T* cbegin() const { return elements;}
		T* end() const { return first_free; }
		const T* cend() const { return first_free; }

		//capacity
		size_t size()const { return first_free - elements; }
		size_t capacity() const { return capacity - elements; }
		bool empty() const { return elements == first_free; }
		void resize(size_t n,T& val=T());
		void reserve(size_t n);

		//access
		T& operator[](const size_t i) { return *(elements + i); }
		const T& operator[](const size_t i) const { return *(elements + i); }
		T& front() { return *elements; }
		T& back() { return *(first_free - 1); }
		T* data() { return first_free; }
		
		//edit container
		void clear();
		void push_back(const T &val);
		void pop_back();



	private:
		static std::allocator<T> alloc;//this is static ,so we should declare this in the end of file
		void chk_n_alloc() { if ( size()==capacity() ) reallocate(); }
		std::pair<T*,T*> alloc_n_copy(const T*,const T*);
		void free();
		void reallocate();
		T* elements;
		T* first_free;
		T* cap;
};
//members in private:
template<typename T>
std::pair<T*,T*> stl_vector<T>::alloc_n_copy(const T* b,const T* e)
{
	auto data=alloc.allocate(e-b);
	return { data,std::uninitialized_copy(b,e,data)};
	//返回新开辟的内存的指针，指向elements，first_free
}

template<typename T>
void stl_vector<T>::free()
{
	if(elements)
	{
		for(auto p=elements;p!=first_free;++p)
		{
			alloc.destroy(p);
		}
		alloc.deallocate(elements,cap - elements);
	}
}

template<typename T>
void stl_vector<T>::reallocate()
{
	size_t newcapacity = size() ? 2*size() : 1;
	auto newdata=alloc.allocate(newcapacity);
	auto dest=newdata;
	auto elem=elements;
	for(size_t i=0;i != size(); ++i )
	{
		alloc.construct(dest++,std::move(*elem));
		++elem;
	}
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;
}

//================================================

//constructor,copy,destructor
template<typename T>
stl_vector<T>::stl_vector(const size_t n,const T& val)
{
	resize(n,val);
}

template<typename T>
stl_vector<T>::stl_vector(const stl_vector& v)
{
	auto newdata=alloc_n_copy(v.cbegin(),v.cend());
	elements = newdata.first;
	first_free = cap= newdata.second;
}

template<typename T>
stl_vector<T>::stl_vector(stl_vector&& v)
{
	elements = v.elements;
	first_free = v.first_free;
	capacity = v.capacity;
}

template<typename T>
stl_vector<T>::stl_vector(std::initializer_list<T> il)
{
	auto newdata = alloc_n_copy(il.begin(),il.end());
	elements = newdata.first;
	first_free = cap =newdata.second;
}

template<typename T>
stl_vector<T>& stl_vector<T>::operator=(const stl_vector& v)
{
	auto newdata = alloc_n_copy(v.cbegin(),v.cend());
	free();
	elements = newdata.first;
	first_free = cap = newdata.second;
	return *this;
}

template<typename T>
stl_vector<T>& stl_vector<T>::operator=(stl_vector&& v)
{
	free();
	elements = v.elements;
	first_free = v.first_free;
	cap = v.cap;
	return *this;
}

template<typename T>
stl_vector<T>::~stl_vector()
{
	free();
}

//compare
template<typename T>
bool stl_vector<T>::operator==(const stl_vector& v) const 
{
	return elements == v.elements && first_free == v.first_free ;
}

template<typename T>
bool stl_vector<T>::operator!=(const stl_vector& v) const
{
	return !(*this == v);
}

//capacity
template<typename T>
void stl_vector<T>::resize(size_t n,T& val)
{
	if( n < size())
	{
		for(auto p=elements + n;p!= first_free;++p)
		{
			alloc.destroy(p);
		}
		first_free =elements + n;
	}
	else if( n <= capacity() )
	{
		size_t number= n - size();
		for(size_t i=0;i<number;++i)
		{
			alloc.construct(first_free++,val);
		}
	}
	else
	{
		size_t newcapacity=size() ? 2 *size() : 1;
		while(newcapacity >= n)
		{
			newcapacity *= 2;
		}
		auto newdata = alloc.allocate(newcapacity);
		auto dest = newdata;
		auto elem = elements;
		for(size_t i=0;i!=n-size();++i)
		{
			alloc.construct(dest++,val);
		}
		free();
		elements = newdata;
		first_free = dest;
		cap = elements + newcapacity;
	}
}

template<typename T>
void stl_vector<T>::reserve(size_t n)
{
	if(n < capacity() )
	{
		return;
	}
	else
	{
		size_t newcapacity=size() ? 2 *size() : 1;
		while(newcapacity >= n)
		{
			newcapacity *= 2;
		}
		auto newdata = alloc.allocate(newcapacity);
		auto dest = newdata;
		auto elem = elements;
		for(size_t i=0;i!=size();++i)
		{
			alloc.construct(dest++,*elem);
			++elem;
		}
		free();
		elements = newdata;
		first_free = dest;
		cap = elements + newcapacity;
	}

}


//edit container
template<typename T>
void stl_vector<T>::clear()
{
	if(elements)
	{
		for(auto p=elements;p!=first_free;++p)
		{
			alloc.destroy(p);
		}
		first_free = elements;
	}
}

template<typename T>
void stl_vector<T>::push_back(const T& val)
{
	chk_n_alloc();
	alloc.construct(first_free++,val);
}

template<typename T>
void stl_vector<T>::pop_back()
{
	alloc.destroy(--first_free);
}



template<typename T>
std::allocator<T> stl_vector<T>::alloc;//because alloc is a static menber,so,we need declare it~


#endif
