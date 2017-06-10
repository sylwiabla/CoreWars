//
// Created by sylwia on 6/10/17.
//

//#define BOOST_TEST_MODULE SymbolTableManagerTest
#include <boost/test/unit_test.hpp>
#include "../../../src/redcodeInterpreter/symbolTableManager/SymbolTableManager.hpp"

BOOST_AUTO_TEST_CASE(constructor_test)
{
    SymbolTableManager * manager = new SymbolTableManager ();
    BOOST_CHECK(manager->getRecentlyAdded() == "");
    delete(manager);
}

BOOST_AUTO_TEST_CASE(setting_recently_added_test)
{
    SymbolTableManager * manager = new SymbolTableManager ();
    manager->setRecentlyAdded("abc");
    BOOST_CHECK(manager->getRecentlyAdded() == "abc");
    delete(manager);
}

BOOST_AUTO_TEST_CASE(finding_nonexisting_function_test)
{
    SymbolTableManager * manager = new SymbolTableManager ();
    BOOST_CHECK(manager->findFunction("foo") == nullptr);
    delete(manager);
}

BOOST_AUTO_TEST_CASE(inserting_function_test)
{
    SymbolTableManager * manager = new SymbolTableManager ();
    FunctionPtr foo = std::make_shared<Function> ("foo", nullptr);
    manager->insert("foo", foo);
    BOOST_CHECK(manager->findFunction("foo") == foo);
    delete(manager);
}

BOOST_AUTO_TEST_CASE(inserting_label_test)
{
    SymbolTableManager * manager = new SymbolTableManager ();
    LabelPtr label = std::make_shared<Label> ("label", 12);
    manager->insert("label", label);
    BOOST_CHECK(manager->findLabel("label") == label);
    delete(manager);
}

BOOST_AUTO_TEST_CASE(identifier_constructor_test)
{
    Identifier * identifier = new Identifier ("var", LABEL);
    BOOST_CHECK(identifier->getType() == LABEL);
    delete(identifier);
}

BOOST_AUTO_TEST_CASE(function_constructor_body_test)
{
    Function * function = new Function ("foo", nullptr);
    BOOST_CHECK(function->getInstruction() == nullptr);
    delete(function);
}

BOOST_AUTO_TEST_CASE(function_constructor_type_test)
{
    Function * function = new Function ("foo", nullptr);
    BOOST_CHECK(function->getType() == FUNCTION);
    delete(function);
}
