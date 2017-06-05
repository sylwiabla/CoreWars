#include "src/compiler.hpp"
#include <boost/python.hpp>
using namespace boost::python;

BOOST_PYTHON_MODULE(compiler_ext)
{
    def("compile", compile);
}
