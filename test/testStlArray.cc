#include "../Container/array.h"
#include <iostream>

int main()
{
	stl_array<int,3> arr={1,2,3};
	std::cout<<arr.at(2)<<std::endl;
	std::cout<<arr.front()<<std::endl;
	std::cout<<arr.empty()<<std::endl;
	std::cout<<arr.size()<<std::endl;
	arr.fill(4);
	std::cout<<arr[2]<<std::endl;

	return 0;
}
