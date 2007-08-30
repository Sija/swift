#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/values/String.h"
#include "../../Source/values/Bool.h"

using namespace Swift;

class TestValueString : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestValueString);

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
    CPPUNIT_ASSERT(iValue::hasTypeString(Values::String::id));
  }

  void testAssign() {
    oValue s("text");
    oValue s1(L"text");
    oValue s2(String("text"));
    oValue s3(string("text"));

    CPPUNIT_ASSERT(s->getID() == Values::String::id);
    CPPUNIT_ASSERT(s1->getID() == Values::String::id);
    CPPUNIT_ASSERT(s2->getID() == Values::String::id);
    CPPUNIT_ASSERT(s3->getID() == Values::String::id);
  }

  void testGet() {
    CPPUNIT_ASSERT(oValue("string") >> String() == "string");
    CPPUNIT_ASSERT(((Values::String*) oValue("string").get())->output() == "string");
  }

  void testSetClear() {
    oValue v("string");
    v->clear();

    CPPUNIT_ASSERT(v >> String() == "");

    Values::String* s = (Values::String*) v.get();
    s->set("text");

    CPPUNIT_ASSERT(v >> String() == "text");
  }

  void testOperators() {
    CPPUNIT_ASSERT((oValue("text1") == oValue("text1")) >> bool());
    CPPUNIT_ASSERT((oValue("home") != oValue("car")) >> bool());
    CPPUNIT_ASSERT(((oValue("one") + oValue("-key")) == oValue("one-key")) >> bool());
    CPPUNIT_ASSERT(!oValue("") >> bool());

    CPPUNIT_ASSERT((oValue() << "text")->getID() == Values::String::id);
    CPPUNIT_ASSERT((oValue("str") >> String()) == "str");
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestValueString);