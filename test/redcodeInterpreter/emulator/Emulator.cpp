//
// Created by sylwia on 6/13/17.
//

#include <boost/test/unit_test.hpp>
#include "../../../src/redcodeInterpreter/emulator/Emulator.hpp"

BOOST_AUTO_TEST_CASE(constructor_core_size_test)
{
    Emulator * e = new Emulator (400, 2);
    BOOST_CHECK(e->getCoreSize() == 400);
    delete(e);
}