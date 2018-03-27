#include <iostream>
#include <foo/foo.h>

int main() {
    std::cout << "Awesomeness enabled: " << foo::is_awesome() << std::endl;

    const auto some_day = "2018-Mar-27";
    std::cout << "Next sunday: " << foo::next_sunday() << std::endl
              << "Next sunday after " << some_day << ": " << foo::next_sunday(some_day) << std::endl;
    return 0;
}