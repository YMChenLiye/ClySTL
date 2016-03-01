#ifndef array_h
#define array_h
#include <iostream>
#include <memory>

template<typename T,std::size_t N>
class stl_array{
	public:
		typedef T									value_type;
		typedef std::size_t 						size_type;
		typedef std::ptrdiff_t						difference_type;
		typedef value_type&							reference;
		typedef const value_type& 					const_reference;
		typedef value_type*							pointer;
		typedef const value_type*					const_pointer;
	
	private:
		static std::allocator<T> alloc;
		T* begin_;
		T* alloc_n()
		{
			return alloc.allocate(N);
		}
		
		void free()
		{
			for(auto p=begin_;p != begin_ + N; ++p)
			{
				alloc.destroy(p);
			}
		}
	public:
		//construct
		stl_array();
		stl_array(std::initializer_list<T> il);
		stl_array(const stl_array& v);
		stl_array(stl_array&& v);
		stl_array& operator=(const stl_array& v);
		stl_array& operator=(stl_array&& v);
		~stl_array();

		//Element access
		reference at(size_type n) const { return *(begin_+n); }
		reference operator[](size_type n) const { return *(begin_ + n); }
		reference front() const { return *begin_ ; }
		reference back() const { return *(begin_ + N); }
		pointer data() const { return begin_; }

		//iterators
		pointer begin() { return begin_; }
		const_pointer cbegin() const { return begin_; }
		pointer end() { return begin_ + N; }
		const_pointer cend() const { return begin_ + N; }

		//capacity
		bool empty() const { return N; }
		size_type size() const { return N; }
		size_type max_size() const { return N; }    //Because each std::array<T, N> is a fixed-size container, the value returned by max_size equals N (which is also the value returned by size) 
		
		//operations
		void fill(const value_type & val);

};


template<typename T,size_t N>
stl_array<T,N>::stl_array()
{
	begin_ = alloc_n();
}

template<typename T,size_t N>
stl_array<T,N>::stl_array(std::initializer_list<T> il)
{
	begin_ = alloc_n();
	int cnt=0;
	for(const T* p=il.begin();p!=il.end() && cnt < N;++p)
	{
		*(begin_+cnt) = *p;
		++cnt;
	}
	//这样做，如果il里的数据比N小，那么array中前面就是il中的值，后面还是T默认的值
	//如果il里的数据比N大，那么array中只会有il中前N个值，后面的值就被抛弃
}

template<typename T,size_t N>
stl_array<T,N>::stl_array(const stl_array& v)
{
	begin_ = alloc_n();
	std::uninitialized_copy(v.begin(),v.end(),begin_);
}

template<typename T,size_t N>
stl_array<T,N>::stl_array(stl_array&& v)
{
	begin_ = v.begin();
}

template<typename T,size_t N>
stl_array<T,N>& stl_array<T,N>::operator=(const stl_array& v)
{
	free();
	std::uninitialized_copy(v.cbegin(),v.cend(),begin_);
}

template<typename T,size_t N>
stl_array<T,N>& stl_array<T,N>::operator=(stl_array&& v)
{
	begin_ = v.begin();
}

template<typename T,size_t N>
stl_array<T,N>::~stl_array()
{
	free();
	begin_ = nullptr;
}

template<typename T,size_t N>
void stl_array<T,N>::fill(const value_type &val)
{
	for(int i=0;i<N;++i)
	{
		*(begin_+i)=val;
	}
}



template<typename T,size_t N>
std::allocator<T> stl_array<T,N>::alloc;

#endif
