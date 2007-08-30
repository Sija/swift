#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/values/Hash.h"
#include "../../Source/values/String.h"
#include "../../Source/values/Int.h"
#include "../../Source/values/Bool.h"

using namespace Swift;

class TestValueHash : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestValueHash);

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
    CPPUNIT_ASSERT(iValue::hasTypeString(Values::Hash::id));
  }

  void testAssign() {
    oValue h = Hash();

    CPPUNIT_ASSERT(h->getID() == Values::Hash::id);
  }

  void testGet() {
    Hash h;
    h.set("a", 100);
    h.set("b", "once");

    CPPUNIT_ASSERT((oValue(h) >> Hash())["a"] >> int() == 100);
    CPPUNIT_ASSERT(((Values::Hash*) oValue(h).get())->output()["b"] >> String() == "once");
  }

  void testSetClear() {
    Hash h_;
    h_.set("x", "zero");
    h_.set("y", 1);

    oValue v(h_);
    v->clear();

    Values::Hash* h = (Values::Hash*) v.get();
    CPPUNIT_ASSERT(!h->output().count());

    h_.set("0","n");
    h->set(h_);

    CPPUNIT_ASSERT(h->output().count());
  }

  void testOperators() {
    oValue v = Hash();

    CPPUNIT_ASSERT(!v >> bool());
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestValueHash);