#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/values/Array.h"
#include "../../Source/values/String.h"
#include "../../Source/values/Int.h"
#include "../../Source/values/Bool.h"

using namespace Swift;

class TestValueArray : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestValueArray);

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
    CPPUNIT_ASSERT(iValue::hasTypeString(Values::Array::id));
  }

  void testAssign() {
    oValue a = Array();

    CPPUNIT_ASSERT(a->getID() == Values::Array::id);
  }

  void testGet() {
    Array a;
    a << "100" << 100;

    CPPUNIT_ASSERT((oValue(a) >> Array())[0] >> String() == "100");
    CPPUNIT_ASSERT(((Values::Array*) oValue(a).get())->output()[1] >> int() == 100);
  }

  void testSetClear() {
    Array a_;
    a_ << "566" << 1020 << 544;

    oValue v(a_);
    v->clear();

    Values::Array* a = (Values::Array*) v.get();
    CPPUNIT_ASSERT(!a->output().count());

    a_ << "last";
    a->set(a_);

    CPPUNIT_ASSERT(a->output().count());
  }

  void testOperators() {
    oValue v = Array();

    CPPUNIT_ASSERT(!v >> bool());
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestValueArray);