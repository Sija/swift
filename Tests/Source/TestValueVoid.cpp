#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/values/Void.h"

using namespace Swift;

class TestValueVoid : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestValueVoid);

  CPPUNIT_TEST(testInit);
  CPPUNIT_TEST(testAssign);
  CPPUNIT_TEST(testOperators);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp() { }
  void tearDown() { }

protected:
  void testInit() {
    CPPUNIT_ASSERT(iValue::hasTypeString(Values::Void::id));
  }

  void testAssign() {
    oValue v = Void();

    CPPUNIT_ASSERT(v->getID() == Values::Void::id);
  }

  void testOperators() {
    CPPUNIT_ASSERT((oValue() << Void())->getID() == Values::Void::id);
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestValueVoid);