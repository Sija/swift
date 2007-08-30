#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/ChainedVariable.h"
#include "../../Source/Hash.h"
#include "../../Source/Array.h"
#include "../../Source/Param.h"
#include "../../Source/Function.h"
#include "../../Source/Globals.h"
#include "../../Source/values/String.h"

using namespace Swift;

class TestChainedVariable : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestChainedVariable);

  CPPUNIT_TEST(testGetValue);
  CPPUNIT_TEST(testSetValue);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp() { }
  void tearDown() { }

protected:
  void testGetValue() {
    Globals* vars = Globals::get();
    vars->addFunction("testFunction", bind(&TestChainedVariable::testFunction, this, _1));

    Hash h(0), h2("none");
    h.set("tree", "lemon");
    h.set("car", "orange");

    h2.set("sn", "111-234-555");
    h2.set("code", "4pqas");
    h.set("hash", h2);

    Array a("z");
    a << h << 15;
    h.set("array", a);

    vars->addVariable("a", a);
    vars->addVariable("h", h);

    Param* param;

    ChainedVariable* cvar = new ChainedVariable(oValueProxy(new Variable("a", vars)));

    param = new Param(0);
    param->add(0, operatorNone, operatorNone);
    cvar->addLink(param);
    cvar->addLink("hash");
    cvar->addLink("code");

    CPPUNIT_ASSERT(cvar->getValue() >> String() == "4pqas");

    ChainedVariable* cvar0 = new ChainedVariable(oValueProxy(new Variable("a", vars)));

    param = new Param(0);
    param->add(0, operatorNone, operatorNone);
    cvar0->addLink(param);
    cvar0->addLink("hash");
    cvar0->addLink("bg");

    CPPUNIT_ASSERT(cvar0->getValue() >> String() == "none");

    param = new Param(0);
    param->add(0, operatorNone, operatorNone);
    cvar0->addLink(param);

    try {
      cvar0->getValue();
      CPPUNIT_ASSERT(!"element is a hash");
    } catch (Stamina::Exception& e) {
    }

    ChainedVariable* cvar1 = new ChainedVariable(oValueProxy(new Variable("h", vars)));

    cvar1->addLink("array");
    param = new Param(0);
    param->add(0, operatorNone, operatorNone);
    cvar1->addLink(param);
    cvar1->addLink("tree");

    CPPUNIT_ASSERT(cvar1->getValue() >> String() == "lemon");

    cvar1->addLink("node");
    try {
      CPPUNIT_ASSERT(cvar1->getValue() >> String() == "lemon");
    } catch (Stamina::Exception& e) {
    }

    ChainedVariable* cvar2 = new ChainedVariable(oValueProxy(new Function("testFunction")));

    param = new Param(0);
    param->add(2, operatorNone, operatorNone);
    cvar2->addLink(param);

    CPPUNIT_ASSERT(cvar2->getValue() >> int() == 125);

    delete cvar;
    delete cvar0;
    delete cvar1;
    delete cvar2;

    Globals::get()->clearVariables();
  }

  void testSetValue() {
    Globals* vars = Globals::get();

    ChainedVariable* cvar = new ChainedVariable(oValueProxy(new Function("testFunction")));

    try {
      cvar->setValue("hello");
      CPPUNIT_ASSERT(!"assign to temp chain Oo");
    } catch (Stamina::Exception& e) {
    }

    Hash h(0);
    Array a;
    a << ":)" << 12;

    h.set("a", 0);
    h.set("b", a);
    vars->addVariable("h", h);

    ChainedVariable* cvar1 = new ChainedVariable(oValueProxy(new Variable("h", vars)));

    cvar1->addLink("a");

    cvar1->setValue("45");
    CPPUNIT_ASSERT(cvar1->getValue() >> String() == "45");

    cvar1->addLink("b");

    try {
      cvar1->setValue("once");
      CPPUNIT_ASSERT(!"assign to non hash value");
    } catch (Stamina::Exception& e) {
    }

    ChainedVariable* cvar2 = new ChainedVariable(oValueProxy(new Variable("h", vars)));

    cvar2->addLink("b");

    Param* param = new Param(0);
    param->add(0, operatorNone, operatorNone);
    cvar2->addLink(param);

    cvar2->setValue(":>");
    CPPUNIT_ASSERT(cvar2->getValue() >> String() == ":>");

    delete cvar;
    delete cvar1;
    delete cvar2;

    Globals::get()->clearVariables();
    Globals::get()->clearFunctions();
  }

private:
  oValue testFunction(const Globals::tFuncArguments& args) {
    Array a("element");
    a << "one" << "boo" << 125;
    return a;
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestChainedVariable);