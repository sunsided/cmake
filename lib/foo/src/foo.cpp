//
// Created by sunside on 27.03.18.
//

#include <sstream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <foo/foo.h>

namespace foo {

    bool is_awesome() {
#if IS_AWESOME
        return true;
#else
        return false;
#endif
    }

    static inline std::string next_sunday(boost::gregorian::date date) {
        const auto sunday = boost::gregorian::greg_weekday(boost::date_time::Sunday);
        const auto next_sunday = boost::gregorian::next_weekday(date, sunday);

        std::stringstream ss;
        ss << next_sunday;
        return ss.str();
    }

    std::string next_sunday() {
        const auto today = boost::gregorian::day_clock::local_day();
        return next_sunday(today);
    }

    std::string next_sunday(const std::string& input) {
        boost::gregorian::date date;
        std::stringstream ss(input);
        ss >> date;

        return next_sunday(date);
    }

}