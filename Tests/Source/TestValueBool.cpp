#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/values/Bool.h"

using namespace Swift;

class TestValueBool : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestValueBool);

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
    CPPUNIT_ASSERT(iValue::hasTypeString(Values::Bool::id));
  }

  void testAssign() {
    oValue b(true);

    CPPUNIT_ASSERT(b->getID() == Values::Bool::id);
  }

  void testGet() {
    CPPUNIT_ASSERT(oValue(true) >> bool());
    CPPUNIT_ASSERT(!((Values::Bool*) oValue(false).get())->output());
  }

  void testSetClear() {
    oValue v(true);
    v->clear();

    CPPUNIT_ASSERT(!(v >> bool()));

    Values::Bool* b = (Values::Bool*) v.get();
    b->set(true);

    CPPUNIT_ASSERT(v >> bool());
  }

  void testOperators() {
    CPPUNIT_ASSERT((oValue(true) == oValue(true)) >> bool());
    CPPUNIT_ASSERT((oValue(true) != oValue(false)) >> bool());
    CPPUNIT_ASSERT((oValue(true) && oValue(true)) >> bool());
    CPPUNIT_ASSERT((oValue(false) || oValue(true)) >> bool());
    CPPUNIT_ASSERT((!oValue(true) == oValue(false)) >> bool());

    CPPUNIT_ASSERT((oValue() << true)->getID() == Values::Bool::id);
    CPPUNIT_ASSERT((oValue(false) >> bool()) == false);
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestValueBool);