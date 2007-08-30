#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/Variable.h"
#include "../../Source/iVariableManager.h"
#include "../../Source/values/String.h"
#include "../../Source/values/Int.h"
#include "../../Source/values/Void.h"

using namespace Swift;

class TestVariable : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestVariable);

  CPPUNIT_TEST(testGetSetValue);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp() { }
  void tearDown() { }

protected:
  void testGetSetValue() {
    iVariableManager* vm = new iVariableManager;
    vm->addVariable("day", "today");

    Variable* var = new Variable("day", vm);
    Variable* var2 = new Variable("time", vm);
    Variable* var3 = new Variable("year", vm);

    CPPUNIT_ASSERT(var->getValue() >> String() == "today");
    CPPUNIT_ASSERT(var2->getValue()->getID() == Values::Void::id);

    vm->addVariable("time", "6:00pm");

    CPPUNIT_ASSERT(var2->getValue() >> String() == "6:00pm");

    var->setValue(1050);

    CPPUNIT_ASSERT(var->getValue() >> int() == 1050);

    var3->setValue("2002");

    CPPUNIT_ASSERT(var3->getValue() >> String() == "2002");

    CPPUNIT_ASSERT(vm->hasVariable("year"));

    delete var;
    delete var2;
    delete var3;
    delete vm;
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestVariable);