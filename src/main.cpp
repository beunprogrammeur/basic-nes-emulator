#include <iostream>
#include <nes/peripherals/memory.h>

int main(int argc, char** argv)
{

    for(int i = 0; i < argc; i++)
    {
        std::cout << argv[i] << std::endl;
    }

    std::cout << "Hello world!" << std::endl;

    return 0;
}