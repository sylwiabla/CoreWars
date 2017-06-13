//
// Created by sylwia on 6/14/17.
//

#include <boost/test/unit_test.hpp>
#include "../../../src/redcodeInterpreter/instruction/SingleInstruction.hpp"

BOOST_AUTO_TEST_CASE(constructor_type_test)
{
    ZeroArgsInstrPtr i = std::make_shared<ZeroArgsInstruction> (Token::nop);
    BOOST_CHECK(i->getType() == Token::nop);
}

