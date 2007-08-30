#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/Globals.h"
#include "../../Source/values/String.h"

using namespace Swift;

class TestGlobals : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestGlobals);

  CPPUNIT_TEST(testInit);
  CPPUNIT_TEST(testBindFunctions);
  CPPUNIT_TEST(testCallFunctions);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp() { }
  void tearDown() { }

protected:
  void testInit() {
    CPPUNIT_ASSERT(Globals::get());
  }

  void testBindFunctions() {
    CPPUNIT_ASSERT(!Globals::get()->hasFunction("test"));
    CPPUNIT_ASSERT(Globals::get()->addFunction("test", bind(&TestGlobals::testFunc, this, _1)));
    CPPUNIT_ASSERT(Globals::get()->hasFunction("test"));
    CPPUNIT_ASSERT(!Globals::get()->addFunction("test", bind(&TestGlobals::testFunc, this, _1)));
    CPPUNIT_ASSERT(!Globals::get()->removeFunction("abc"));
    CPPUNIT_ASSERT(Globals::get()->removeFunction("test"));
    Globals::get()->clearFunctions();
    CPPUNIT_ASSERT(Globals::get()->addFunction("test", bind(&TestGlobals::testFunc, this, _1)));
    CPPUNIT_ASSERT(Globals::get()->removeFunction("test"));
  }

  void testCallFunctions() {
    CPPUNIT_ASSERT(Globals::get()->addFunction("test", bind(&TestGlobals::testFunc, this, _1)));

    Globals::tFuncArguments arg;
    CPPUNIT_ASSERT(Globals::get()->callFunction("test", Globals::tFuncArguments()) >> String() == "no args");

    arg.push_back("arg1");
    CPPUNIT_ASSERT(Globals::get()->callFunction("test", arg) >> String() == "arg1");

    try {
      CPPUNIT_ASSERT(Globals::get()->callFunction("test1", arg) >> String() == "arg1");
    } catch (Stamina::Exception& e) {
    }

    Globals::get()->clearFunctions();
  }

private:
  oValue testFunc(const Globals::tFuncArguments& args) {
    return args.size() ? args[0] : "no args";
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestGlobals);