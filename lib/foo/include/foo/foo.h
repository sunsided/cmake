//
// Created by sunside on 27.03.18.
//

#ifndef FOO_FOO_H
#define FOO_FOO_H

#include <string>

namespace foo {

    /// \brief Determines if this library was compiled with awesomeness enabled.
    /// \return true if this library is awesome.
    bool is_awesome();

    /// \brief Obtains the date of the next sunday.
    /// \return The date of the next sunday.
    std::string next_sunday();

    /// \brief Obtains the date of the next sunday following the specified date.
    /// \param input The date to calculate the next sunday from.
    /// \return The date of the next sunday.
    std::string next_sunday(const std::string& input);

}

#endif //FOO_FOO_H
