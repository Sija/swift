#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/Function.h"
#include "../../Source/Globals.h"
#include "../../Source/values/String.h"
#include "../../Source/values/Int.h"
#include "../../Source/values/Void.h"

using namespace Swift;

class TestFunction : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestFunction);

  CPPUNIT_TEST(testGetValue);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp() { }
  void tearDown() { }

protected:
  void testGetValue() {
    Param* param;

    Function* func = new Function("test");
    Function* func1 = new Function("test1");

    param = new Param(0);
    param->add("x", operatorNone, operatorNone);
    func1->addParam(param);

    param = new Param(0);
    param->add("y", operatorNone, operatorNone);
    func1->addParam(param);

    Function* func2 = new Function("test2");

    Function* func3 = new Function("test2");

    param = new Param(0);
    param->add("a", operatorNone, operatorNone);
    func3->addParam(param);

    param = new Param(0);
    param->add(120, operatorNone, operatorNone);
    func3->addParam(param);

    try {
      CPPUNIT_ASSERT(func->getValue());
    } catch (Stamina::Exception& e) {
    }

    Globals::get()->addFunction("test", bind(&TestFunction::testFunction, this, _1));
    Globals::get()->addFunction("test1", bind(&TestFunction::testFunction1, this, _1));
    Globals::get()->addFunction("test2", bind(&TestFunction::testFunction2, this, _1));

    CPPUNIT_ASSERT(func->getValue() >> String() == "noargs");
    CPPUNIT_ASSERT(func1->getValue() >> String() == "arg");
    CPPUNIT_ASSERT(func2->getValue()->getID() == Values::Void::id);
    CPPUNIT_ASSERT(func3->getValue() >> int() == 120);

    Globals::get()->clearFunctions();

    delete func;
    delete func1;
    delete func2;
    delete func3;
  }

private:
  oValue testFunction(const Globals::tFuncArguments& args) {
    CPPUNIT_ASSERT(!args.size());
    return "noargs";
  }
  oValue testFunction1(const Globals::tFuncArguments& args) {
    CPPUNIT_ASSERT(args.size());
    return "arg";
  }
  oValue testFunction2(const Globals::tFuncArguments& args) {
    return args.size() ? args[args.size() - 1] : Values::Void();
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestFunction);