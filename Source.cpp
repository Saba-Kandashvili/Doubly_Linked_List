#include "LinkedList.h"

int main()
{
	LinkedList<int> list1;
	list1.add_at_beginning(1);
	list1.add_at_beginning(2);
	list1.add_at_beginning(3);
	std::cout << list1 << std::endl;

	return 0;
}