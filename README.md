# "Modern" CMake Example Project

CMake is anarchy. In order to do it better, here's an
example project that contains the following structure:

- A library `foo` that privately depends on 
  `Boost::date_time` and provides some functionality.
- A library `bar` that solely depends on `foo`.
- An executable `baz` that calls a method in `bar`.

All projects are set up in a way that they can be installed
and found using `find_package()`, as well as added
using `add_subdirectory()`. The `CMakeLists.txt` files
are heavily documented, but care should be taken to
also have a look at the `cmake/*-cmake.in` files of
the individual libraries.

Each installation is versioned, allowing for keeping
multiple different versions at the same time.
Likewise, installation paths are prefixed with the build
configuration.

## References

Blog posts and repositories that helped in assembling
this:

- [It's Time To Do CMake Right](https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/)
  by Pablo Arias and the companion repo
- [modern-cmake-sample](https://github.com/pabloariasal/modern-cmake-sample), as well as
- [Easily supporting CMake install and find_package()](https://foonathan.net/blog/2016/03/03/cmake-install.html)
  by Jonathan Müller.