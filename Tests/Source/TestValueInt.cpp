#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/values/Int.h"
#include "../../Source/values/Bool.h"

using namespace Swift;

class TestValueInt : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestValueInt);

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
    CPPUNIT_ASSERT(iValue::hasTypeString(Values::Int::id));
  }

  void testAssign() {
    oValue i(123);
    oValue i1(-875);

    CPPUNIT_ASSERT(i->getID() == Values::Int::id);
    CPPUNIT_ASSERT(i1->getID() == Values::Int::id);
  }

  void testGet() {
    CPPUNIT_ASSERT(oValue(200) >> int() == 200);
    CPPUNIT_ASSERT(((Values::Int*) oValue(15).get())->output() == 15);
  }

  void testSetClear() {
    oValue v(678);
    v->clear();

    CPPUNIT_ASSERT(v >> int() == 0);

    Values::Int* i = (Values::Int*) v.get();
    i->set(999);

    CPPUNIT_ASSERT(v >> int() == 999);
  }

  void testOperators() {
    CPPUNIT_ASSERT((oValue(4) == oValue(4)) >> bool());
    CPPUNIT_ASSERT((oValue(2) != oValue(3)) >> bool());
    CPPUNIT_ASSERT((oValue(4) && oValue(2)) >> bool());
    CPPUNIT_ASSERT((oValue(0) || oValue(5)) >> bool());
    CPPUNIT_ASSERT((-oValue(15) == oValue(-15)) >> bool());
    CPPUNIT_ASSERT(((oValue(8) + oValue(3))  == oValue(11)) >> bool());
    CPPUNIT_ASSERT(((oValue(3) - oValue(7))  == oValue(-4)) >> bool());
    CPPUNIT_ASSERT(!(!oValue(8) >> bool()));

    CPPUNIT_ASSERT((oValue() << 100)->getID() == Values::Int::id);
    CPPUNIT_ASSERT((oValue(2090) >> int()) == 2090);
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestValueInt);