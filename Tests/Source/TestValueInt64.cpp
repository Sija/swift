#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/values/Int64.h"
#include "../../Source/values/Bool.h"

using namespace Swift;

class TestValueInt64 : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestValueInt64);

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
    CPPUNIT_ASSERT(iValue::hasTypeString(Values::Int64::id));
  }

  void testAssign() {
    oValue i((__int64) 123);
    oValue i1(24434342545455677);

    CPPUNIT_ASSERT(i->getID() == Values::Int64::id);
    CPPUNIT_ASSERT(i1->getID() == Values::Int64::id);
  }

  void testGet() {
    CPPUNIT_ASSERT(oValue((__int64) 200) >> __int64() == 200);
    CPPUNIT_ASSERT(((Values::Int64*) oValue((__int64) 15).get())->output() == 15);
  }

  void testSetClear() {
    oValue v((__int64) 678);
    v->clear();

    CPPUNIT_ASSERT(v >> __int64() == 0);

    Values::Int64* i = (Values::Int64*) v.get();
    i->set(999);

    CPPUNIT_ASSERT(v >> __int64() == 999);
  }

  void testOperators() {
    CPPUNIT_ASSERT((oValue((__int64) 4) == oValue((__int64) 4)) >> bool());
    CPPUNIT_ASSERT((oValue((__int64) 2) != oValue((__int64) 3)) >> bool());
    CPPUNIT_ASSERT((oValue((__int64) 4) && oValue((__int64) 2)) >> bool());
    CPPUNIT_ASSERT((oValue((__int64) 0) || oValue((__int64) 5)) >> bool());
    CPPUNIT_ASSERT((-oValue((__int64) 15) == oValue((__int64) -15)) >> bool());
    CPPUNIT_ASSERT(((oValue((__int64) 8) + oValue((__int64) 3)) == oValue((__int64) 11)) >> bool());
    CPPUNIT_ASSERT(((oValue((__int64) 3) - oValue((__int64) 7)) == oValue((__int64) -4)) >> bool());
    CPPUNIT_ASSERT(!(!oValue((__int64) 4) >> bool()));

    CPPUNIT_ASSERT((oValue() << (__int64) 100)->getID() == Values::Int64::id);
    CPPUNIT_ASSERT((oValue((__int64) 2090) >> __int64()) == 2090);
  }
};


CPPUNIT_TEST_SUITE_REGISTRATION(TestValueInt64);
