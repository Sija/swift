#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/Param.h"
#include "../../Source/Variable.h"
#include "../../Source/iVariableManager.h"
#include "../../Source/iValue.h"
#include "../../Source/CastValues.h"

#include "../../Source/values/String.h"
#include "../../Source/values/Int.h"
#include "../../Source/values/Bool.h"
#include "../../Source/values/RegExPattern.h"
#include "../../Source/values/Array.h"

using namespace Swift;

class TestParam : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestParam);

  CPPUNIT_TEST(testManaging);
  CPPUNIT_TEST(testGetValue);
  CPPUNIT_TEST(testOperator);
  CPPUNIT_TEST(testOperators);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp() {
    param = new Param(0);

    try {
      iValue::addCastFunction(Values::Int::id, Values::String::id, &intToStr);
      iValue::addCastFunction(Values::Int::id, Values::Bool::id, &intToBool);

      iValue::addCastFunction(Values::String::id, Values::Bool::id, &strToBool);
      iValue::addCastFunction(Values::String::id, Values::Int::id, &strToInt);

      iValue::addCastFunction(Values::Bool::id, Values::String::id, &boolToStr);
      iValue::addCastFunction(Values::Date::id, Values::String::id, &dateToStr);
      iValue::addCastFunction(Values::RegExPattern::id, Values::String::id, &regExpToStr);
      iValue::addCastFunction(Values::Void::id, Values::String::id, &voidToStr);

    } catch (Stamina::Exception& e) {
    }
  }
  void tearDown() {
    delete param;
  }

protected:
  void testManaging() {
    CPPUNIT_ASSERT(!param->count());
    param->add(5, operatorMinus, operatorPlus);
    param->add(3, operatorNone, operatorPlus);
    param->add("hello", operatorNone, operatorPlus);
    param->add(false, operatorNot, operatorPlus);

    CPPUNIT_ASSERT(param->count());
    param->clear();
    CPPUNIT_ASSERT(!param->count());
  }

  void testGetValue() {
    try {
      param->add("test no:", operatorNone, operatorPlus);
      param->add(2, operatorMinus, operatorPlus);
      param->add(",it's ", operatorNone, operatorPlus);
      param->add(false, operatorNot, operatorNone);

      CPPUNIT_ASSERT(param->getValue() >> String() == "test no:-2,it's true");
    } catch (Stamina::Exception& e) {
    }

    param->clear();
  }

  void testOperator() {

    // operator plus
    param->add("4 - 7 = ", operatorNone, operatorPlus);
    param->add(3, operatorMinus, operatorNone);

    CPPUNIT_ASSERT(param->getValue() >> String() == "4 - 7 = -3");

    param->clear();

    // operator minus
    param->add(2, operatorNone, operatorMinus);
    param->add(3, operatorMinus, operatorNone);

    CPPUNIT_ASSERT(param->getValue() >> int() == 5);

    param->clear();

    // operator and
    param->add(true, operatorNone, operatorAnd);
    param->add(false, operatorNone, operatorNone);

    CPPUNIT_ASSERT(!(param->getValue() >> bool()));

    param->clear();

    // operator or
    param->add(true, operatorNone, operatorOr);
    param->add(false, operatorNone, operatorNone);

    CPPUNIT_ASSERT(param->getValue() >> bool());

    param->clear();

    // operator ==
    param->add(false, operatorNone, operatorEqual);
    param->add(false, operatorNone, operatorNone);

    CPPUNIT_ASSERT(param->getValue() >> bool());

    param->clear();

    // operator !=
    param->add(true, operatorNone, operatorNotEqual);
    param->add(false, operatorNone, operatorNone);

    CPPUNIT_ASSERT(param->getValue() >> bool());

    param->clear();

    // operator =~
    param->add(iValue::create<Values::RegExPattern>("hello"), operatorNone, operatorRegExEqual);
    param->add("hello", operatorNone, operatorNone);

    CPPUNIT_ASSERT(param->getValue() >> bool());

    param->clear();

    // operator !~
    param->add(iValue::create<Values::RegExPattern>("world"), operatorNone, operatorRegExNotEqual);
    param->add("hello", operatorNone, operatorNone);

    CPPUNIT_ASSERT(param->getValue() >> bool());

    param->clear();

    // operator in
    Array a;
    a << "String" << 2 << false;
    param->add(2, operatorNone, operatorIn);
    param->add(a, operatorNone, operatorNone);

    CPPUNIT_ASSERT(param->getValue() >> bool());

    param->clear();

    // operator "in" used with non struct value
    param->add(2, operatorNone, operatorIn);
    param->add("text", operatorNone, operatorNone);

    try {
      param->getValue();
      CPPUNIT_ASSERT(!"no errors");
    } catch (Stamina::Exception& e) {
    }

    param->clear();

    // operator =
    iVariableManager* vm = new iVariableManager;
    vm->setVariable("test", ":)");

    param->add(new Variable("test", vm), operatorNone, operatorAssign);
    param->add("text", operatorNone, operatorNone);

    CPPUNIT_ASSERT(param->getValue()->getID() == Values::Void::id);
    param->clear();

    // operator = and ! before var
    param->add(new Variable("test", vm), operatorNot, operatorAssign);
    param->add("text", operatorNone, operatorPlus);
    param->add("text", operatorNone, operatorNone);

    try {
      CPPUNIT_ASSERT(param->getValue());
    } catch (Stamina::Exception& e) {
    }

    param->clear();

    delete vm;

    // operator "=" used with non var value
    param->add("xxx", operatorNone, operatorAssign);
    param->add("text", operatorNone, operatorNone);

    try {
      CPPUNIT_ASSERT(param->getValue());
    } catch (Stamina::Exception& e) {
    }

    param->clear();

    // operator "=" used in second position
    param->add("xxx", operatorNone, operatorPlus);
    param->add("text", operatorNone, operatorAssign);
    param->add("text", operatorNone, operatorNone);

    try {
      CPPUNIT_ASSERT(param->getValue());
    } catch (Stamina::Exception& e) {
    }

    param->clear();
  }

  void testOperators() {
    param->add("number ", operatorNone, operatorPlus);
    param->add(5, operatorMinus, operatorEqual);
    param->add("number -5", operatorNone, operatorAnd);
    param->add(false, operatorNone, operatorNone);

    CPPUNIT_ASSERT(!(param->getValue() >> bool()));

    param->clear();
  }

private:
  Param* param;
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestParam);