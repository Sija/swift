#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/values/RegExPattern.h"

using namespace Swift;

class TestValueRegExPattern : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestValueRegExPattern);

  CPPUNIT_TEST(testInit);
  CPPUNIT_TEST(testAssign);
  CPPUNIT_TEST(testGet);
  CPPUNIT_TEST(testSetClear);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp() { }
  void tearDown() { }

protected:
  void testInit() {
    CPPUNIT_ASSERT(iValue::hasTypeString(Values::RegExPattern::id));
  }

  void testAssign() {
    oValue r(iValue::create<Values::RegExPattern>("/pattern/"));

    CPPUNIT_ASSERT(r->getID() == Values::RegExPattern::id);
  }

  void testGet() {
    CPPUNIT_ASSERT(((Values::RegExPattern*) iValue::create<Values::RegExPattern>("/pattern/").get())->output() == "/pattern/");
  }

  void testSetClear() {
    oValue v = iValue::create<Values::RegExPattern>("/pattern/");
    v->clear();

    CPPUNIT_ASSERT(((Values::RegExPattern*) v.get())->output() == "");

    Values::RegExPattern* r = (Values::RegExPattern*) v.get();
    r->set("/pat/");

    CPPUNIT_ASSERT(((Values::RegExPattern*) v.get())->output() == "/pat/");
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestValueRegExPattern);