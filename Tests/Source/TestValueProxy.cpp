#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/values/Proxy.h"
#include "../../Source/values/Bool.h"
#include "../../Source/values/String.h"
#include "../../Source/iValueProxy.h"
#include "../../Source/Variable.h"
#include "../../Source/Globals.h"

using namespace Swift;

class TestValueProxy : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestValueProxy);

  CPPUNIT_TEST(testInit);
  CPPUNIT_TEST(testAssign);
  CPPUNIT_TEST(testGet);
  CPPUNIT_TEST(testSetClear);
  CPPUNIT_TEST(testOperators);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp() { }
  void tearDown() { }

protected:
  void testInit() {
    CPPUNIT_ASSERT(iValue::hasTypeString(Values::Proxy::id));
  }

  void testAssign() {
    oValue p(new Variable("name", 0));

    CPPUNIT_ASSERT(p->getID() == Values::Proxy::id);
  }

  void testGet() {
    Globals::get()->addVariable("name", "xyz");

    CPPUNIT_ASSERT((oValue(new Variable("name", Globals::get())) >> oValue()) >> String() == "xyz");
    CPPUNIT_ASSERT(((Values::Proxy*) oValue(new Variable("name", Globals::get())).get())->get() >> String() == "xyz");

    Globals::get()->clearVariables();
  }

  void testSetClear() {
    oValue v(new Variable("name", 0));
    v->clear();

    Values::Proxy* p = (Values::Proxy*) v.get();

    CPPUNIT_ASSERT(!p->output().get());

    p->set(new Variable("name", 0));

    CPPUNIT_ASSERT(p->output().get());
  }

  void testOperators() {
    Globals::get()->addVariable("name", "bca");
    oValue v(new Variable("name", Globals::get()));

    CPPUNIT_ASSERT((v == oValue("bca")) >> bool());
    CPPUNIT_ASSERT((v != oValue(3)) >> bool());
    CPPUNIT_ASSERT(!(!v >> bool()));

    CPPUNIT_ASSERT((oValue() << new Variable("name", Globals::get()))->getID() == Values::Proxy::id);
    CPPUNIT_ASSERT((v >> oValueProxy()).get());

    Globals::get()->clearVariables();
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestValueProxy);