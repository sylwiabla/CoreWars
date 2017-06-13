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

/*BOOST_AUTO_TEST_CASE(get_pc_on_start_test)
{
    Emulator * e = new Emulator (4000, 2);
    BOOST_CHECK(e->getPc() == 0);
    delete(e);
}*/

/*BOOST_AUTO_TEST_CASE(get_pc_after_invoking_insruction_test)
{
    Emulator * e = new Emulator (4000, 2);
    CorePtr core = e->getCore();
    (*core)[0] = std::make_shared<ZeroArgsInstruction> (ZeroArgsInstruction (Token::nop));
    e->invokeInstruction();
    BOOST_CHECK(e->getPc() == 1);
    delete(e);
}*/
