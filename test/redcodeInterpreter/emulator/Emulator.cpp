//
// Created by sylwia on 6/13/17.
//

#include <boost/test/unit_test.hpp>
#include "../../../src/redcodeInterpreter/emulator/Emulator.hpp"

BOOST_AUTO_TEST_CASE(constructor_core_size_test)
{
    ZeroArgsInstrPtr i = std::make_shared<ZeroArgsInstruction> (Token::nop);
    Emulator * e = new Emulator ((long) 400, 2, i);
    BOOST_CHECK(e->getCoreSize() == 400);
    delete(e);
}

BOOST_AUTO_TEST_CASE(pc_after_function_invocation_test)
{
    ZeroArgsInstrPtr i = std::make_shared<ZeroArgsInstruction> (Token::nop);
    Emulator * e = new Emulator ((long) 400, 2, i);
    BOOST_CHECK(e->getPc() == 0);
    delete(e);
}

BOOST_AUTO_TEST_CASE(write_to_core_test)
{
    Core core;
    TwoArgsInstrPtr instruction = std::make_shared<TwoArgsInstruction> (Token::dat);
    core.push_back(instruction);
    BOOST_CHECK((*core.begin())->getType() == Token::dat);
}

BOOST_AUTO_TEST_CASE(write_to_core_2_test)
{
    TwoArgsInstrPtr instruction = std::make_shared<TwoArgsInstruction> (Token::dat);
    Core core (4, instruction);
    BOOST_CHECK((*(++core.begin()))->getType() == Token::dat);
}