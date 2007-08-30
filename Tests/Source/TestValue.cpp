#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/values/Bool.h"
#include "../../Source/values/String.h"
#include "../../Source/values/Date.h"
#include "../../Source/values/Int.h"
#include "../../Source/values/RegExPattern.h"
#include "../../Source/iValue.h"
#include "../../Source/CastValues.h"

using namespace Swift;

class TestValue : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestValue);

  CPPUNIT_TEST(testAssign);
  CPPUNIT_TEST(testCast);
  CPPUNIT_TEST(testOperators);
  CPPUNIT_TEST(testIdentify);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp() {
    try {
      iValue::addCastFunction(Values::Int::id, Values::String::id, &intToStr);
      iValue::addCastFunction(Values::Int::id, Values::Bool::id, &intToBool);

      iValue::addCastFunction(Values::String::id, Values::Bool::id, &strToBool);
      iValue::addCastFunction(Values::String::id, Values::Int::id, &strToInt);

      iValue::addCastFunction(Values::Bool::id, Values::String::id, &boolToStr);
      iValue::addCastFunction(Values::Date::id, Values::String::id, &dateToStr);
      iValue::addCastFunction(Values::RegExPattern::id, Values::String::id, &regExpToStr);

    } catch (Stamina::Exception& e) {
    }
  }
  void tearDown() { }

protected:
  void testAssign() {
    CPPUNIT_ASSERT((oValue() << "text")->getID() == Values::String::id);
    CPPUNIT_ASSERT((oValue() = 14)->getID() == Values::Int::id);
    CPPUNIT_ASSERT(oValue(123)->getID() == Values::Int::id);
    CPPUNIT_ASSERT(iValue::create<Values::RegExPattern>("/pattern/")->getID() == Values::RegExPattern::id);
    CPPUNIT_ASSERT(oValue(oValue(5050))->getID() == Values::Int::id);
    CPPUNIT_ASSERT(oValue(new Values::String)->getID() == Values::String::id);
    CPPUNIT_ASSERT(oValue(false)->getName() == "Bool");
  }

  void testCast() {
    CPPUNIT_ASSERT((oValue() << "text") >> String() == "text");
    CPPUNIT_ASSERT(oValue(125) >> String() == "125");
    CPPUNIT_ASSERT(oValue(false) >> String() == "false");
    CPPUNIT_ASSERT(oValue("12") >> int() == 12);
    CPPUNIT_ASSERT(!(oValue("false") >> bool()));
  }

  void testOperators() {
    CPPUNIT_ASSERT(((oValue("Day: ") + oValue(12)) == oValue("Day: 12")) >> bool());
    CPPUNIT_ASSERT(((oValue(125) + oValue("75")) == oValue("200")) >> bool());
    CPPUNIT_ASSERT((oValue(12) == -oValue(-12)) >> bool());
    CPPUNIT_ASSERT(((oValue(true) || oValue(false)) == oValue(true)) >> bool());
    CPPUNIT_ASSERT(((oValue(true) && oValue(true)) == oValue(true)) >> bool());
    CPPUNIT_ASSERT((!oValue(true) == oValue(false)) >> bool());
  }

  void testIdentify() {
    CPPUNIT_ASSERT(iValue::getTypeString(Values::String::id) == "String");
    CPPUNIT_ASSERT(iValue::getTypeString(oValue(12)->getID()) == "Int");
    CPPUNIT_ASSERT(iValue::getTypeString(Values::Bool::id) == oValue(true)->getName());
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestValue);