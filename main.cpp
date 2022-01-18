#include "linked_ls.hpp"
#include <cstdlib>

int main(int argc, char **argv)
{
    try
    {
        LinkedList<int> sample_list(2);

        for (int i = 0; i < 5; i++)
            sample_list.push_back(std::rand() % 100 + 1);

        std::cout << sample_list << std::endl;
        std::cout << "Current size of LL: " << sample_list.size() << std::endl;

        std::cout << "Is the list empty?: " << std::boolalpha << sample_list.empty() << std::endl;

        // write data in LL to a text file
        sample_list.write_file("linked_list_contents.txt");

        // copy list
        LinkedList<int> sample_list_copy;
        sample_list_copy.copy(sample_list);
        std::cout << "Outputting copy: " << sample_list_copy << std::endl;

        // copy list with overloaded assignment operator
        LinkedList<int> sample_list_copy_copy;
        sample_list_copy_copy = sample_list_copy;
        std::cout << "Outputting copy of copy: " << sample_list_copy_copy << std::endl;

        // push to front of list
        sample_list.push_front(12345);
        std::cout << "After push_front: " << sample_list << std::endl;

        std::cout << "Front element: " << sample_list.front() << std::endl;
        std::cout << "Back element: " << sample_list.back() << std::endl;

        std::cout << "Popping first element, element val is: " << sample_list.pop_front() << std::endl;

        for (int i = 0; i < 6; i++)
            std::cout << "Popped element: " << sample_list.pop_back() << std::endl;

        std::cout << "Current size of LL: " << sample_list.size() << std::endl;
        std::cout << "Is the list empty?: " << std::boolalpha << sample_list.empty() << std::endl;
        std::cout << "List currently: " << sample_list << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}