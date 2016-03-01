#ifndef Unique_ptr_h
#define Unique_ptr_h
#include <memory>
#include "DebugDelete.h"
#include <functional>

template<typename T,typename D=DebugDelete>
class Unique_ptr{
	public:
		Unique_ptr(const Unique_ptr &)=delete;
		Unique_ptr& operator=(const Unique_ptr &)=delete;
		
		Unique_ptr()=default;
		explicit Unique_ptr(T *p):ptr(p) { }
		Unique_ptr(Unique_ptr &&rhs) noexcept:ptr(rhs.ptr) { rhs.ptr=nullptr; }
		Unique_ptr& operator=(Unique_ptr &&rhs) noexcept
		{
			if(ptr != rhs.ptr)
			{
				deleter(ptr);
				ptr=nullptr;
				std::swap(ptr,rhs.ptr);
				std::swap(deleter,rhs.deleter);
			}
			return *this;
		}

		operator bool() const { return ptr? true:false; }
		T& operator*() const { return *ptr;}
		T* operator->() const { return &*ptr; }

		T* get() const { return ptr; }

		void reset() noexcept { deleter(ptr);ptr=nullptr;}
		void reset(T *p) noexcept { deleter(ptr);ptr=p; }
		
		~Unique_ptr()
		{
			deleter(ptr);
		}



	private:
		T *ptr;
		D deleter=D();
};




#endif
