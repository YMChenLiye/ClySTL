#ifndef string_h
#define string_h

#include <memory>


class String{
	public:
		String() :String("") { }
		String(const char *);
		String(const String&);
		String& operator=(const String&);
		~String();
		String(String&&) noexcept;
		String& operator=(String&&) noexcept;

		const char *c_str()const { return element;}

		size_t size()const { return end-element;}
		size_t length()const { return end-element-1;}

	private:
		static std::allocator<char> alloc;
		std::pair<char*,char*> alloc_n_copy(const char*,const char*);
		void free();
		char *element;
		char *end;
};

std::pair<char*,char*> String::alloc_n_copy(const char *b,const char *e)
{
	auto data=alloc.allocate(e-b);
	return { data,std::uninitialized_copy(b,e,data)};
}
String::String(const char *s)
{
	char *e=const_cast<char *>(s);
	while(*e) ++e;
	auto data=alloc_n_copy(s,++e);
	element=data.first;
	end=data.second;
}

String::String(const String& s)
{
	auto data=alloc_n_copy(s.element,s.end);
	element=data.first;
	end=data.second;
}
void String::free()
{
	std::for_each(element,end,[this](char &c){ alloc.destroy(&c);});
	alloc.deallocate(element,end-element);
}

String& String::operator=(const String& s)
{
	auto newdata=alloc_n_copy(s.element,s.end);
	free();
	element=newdata.first;
	end=newdata.second;
	return *this;
}
String::~String()
{
	free();
}
String::String(String&& rhs) noexcept :element(rhs.element),end(rhs.end) { rhs.element=rhs.end=nullptr;  }


#endif
