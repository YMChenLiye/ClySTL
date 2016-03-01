#ifndef Shared_ptr_h
#define Shared_ptr_h
#include <memory>
#include <functional>
#include "DebugDelete.h"

template<typename T>
class Shared_ptr{
	public:
		Shared_ptr()=default;
		explicit Shared_ptr(T* p,std::function<void(T*)> d=DebugDelete()):ptr(p),ref_count(new std::size_t(1)),deleter(d) { }
		
		Shared_ptr(const Shared_ptr& p):ptr(p.ptr),ref_count(p.ref_count),deleter(p.deleter) { ++*ref_count;}
		Shared_ptr(Shared_ptr&& p) noexcept :ptr(p.ptr),ref_count(p.ref_count),deleter(std::move(p.deleter)) {}
		Shared_ptr& operator=(const Shared_ptr &rhs)
		{
			++*rhs.ref_count;
			decream_and_destroy();
			ptr=rhs.ptr;
			ref_count=rhs.ref_count;
			deleter=rhs.deleter;
		}
		Shared_ptr& operator=(Shared_ptr &&rhs) noexcept
		{
			decream_and_destroy();
			std::swap(this->ptr,rhs.ptr);
			std::swap(this->ref_count,rhs.ref_count);
			std::swap(this->deleter,rhs.deleter);
			return *this;
		}
	
		Shared_ptr(std::shared_ptr<T> &&p,std::function<void(T*)> d=DebugDelete())
		{
			if(p.unique())
			{
				*this=Shared_ptr(new T(*p),d);
			}
			else
				throw std::runtime_error("only unique can transfer ownership");
		}

		operator bool() const { return ptr? true: false; }
		
		T& operator*() const { return *ptr; }
		T* operator->() const { return &*ptr; }

		T* get() const { return ptr;}
		std::size_t use_count() const { return *ref_count;}
		bool unique() const { return *ref_count==1; }
		void swap(Shared_ptr &rhs) 
		{
			std::swap(*this.ptr,rhs.ptr);
			std::swap(*this.ref_count,rhs.ref_count);
			std::swap(*this.deleter,rhs.deleter);
		}
		void reset() noexcept { decream_and_destroy(); }
		void reset(T* p)
		{
			if(ptr!=p)
			{
				decream_and_destroy();
				ptr=p;
				ref_count=new std::size_t(1);
			}
		}
		void reset(T *p,std::function<void(T*)>& d)
		{
			reset(p);
			deleter=d;
		}
		~Shared_ptr()
		{
			decream_and_destroy();
		}


	private:
		T* ptr;
		std::size_t *ref_count;
		std::function<void(T*)> deleter;

		void decream_and_destroy()
		{
			if(ptr && 0==-*ref_count)
			{
				delete ref_count;
				deleter(ptr);
			}
			else if(!ptr)
			{
				delete ref_count;
			}
			ptr=nullptr;
			ref_count=nullptr;
		}

};












#endif
