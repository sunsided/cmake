//
// Created by sunside on 27.03.18.
//

#include <iostream>
#include <foo/foo.h>
#include <bar/bar.h>

namespace bar {

    void do_stuff() {
        std::cout << "Awesomeness enabled: " << foo::is_awesome() << std::endl;

        const auto some_day = "2018-Mar-27";
        std::cout << "Next sunday: " << foo::next_sunday() << std::endl
                  << "Next sunday after " << some_day << ": " << foo::next_sunday(some_day) << std::endl;
    }

}