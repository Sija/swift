#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/values/Date.h"
#include "../../Source/values/Bool.h"

using namespace Swift;

class TestValueDate : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestValueDate);

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
    CPPUNIT_ASSERT(iValue::hasTypeString(Values::Date::id));
  }

  void testAssign() {
    oValue d(Date64(true));

    CPPUNIT_ASSERT(d->getID() == Values::Date::id);
  }

  void testGet() {
    CPPUNIT_ASSERT(oValue(Date64(true)) >> Date64() == Date64(true));
    CPPUNIT_ASSERT(((Values::Date*) oValue(Date64()).get())->output() == Date64());
  }

  void testSetClear() {
    oValue v(Date64(true));
    v->clear();

    CPPUNIT_ASSERT(v >> Date64() == Date64());

    Values::Date* d = (Values::Date*) v.get();
    d->set(Date64((time_t) 5443));

    CPPUNIT_ASSERT(v >> Date64() == Date64((time_t) 5443));
  }

  void testOperators() {
    CPPUNIT_ASSERT((oValue(Date64((time_t) 100)) == oValue(Date64((time_t) 100))) >> bool());
    CPPUNIT_ASSERT((oValue(Date64((time_t) 50000)) != oValue(Date64((time_t) 876555))) >> bool());
    CPPUNIT_ASSERT(((oValue(Date64((time_t) 560000)) + oValue(Date64((time_t) 40000))) == oValue(Date64((time_t) 600000))) >> bool());
    CPPUNIT_ASSERT(((oValue(Date64((time_t) 480000)) - oValue(Date64((time_t) 120000))) == oValue(Date64((time_t) 360000))) >> bool());

    CPPUNIT_ASSERT((oValue() << Date64())->getID() == Values::Date::id);
    CPPUNIT_ASSERT((oValue(Date64((time_t) 123)) >> Date64()) == Date64((time_t) 123));
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestValueDate);