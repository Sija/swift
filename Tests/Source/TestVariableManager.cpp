#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/iVariableManager.h"

#include "../../Source/values/Void.h"
#include "../../Source/values/String.h"
#include "../../Source/values/Int.h"

using namespace Swift;

class TestVariableManager : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestVariableManager);

  CPPUNIT_TEST(testManaging);
  CPPUNIT_TEST(testGetVar);
  CPPUNIT_TEST(testTree);
  CPPUNIT_TEST(testSetVars);
  CPPUNIT_TEST(testAccessToVar);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp() {
    vm = new iVariableManager;
  }
  void tearDown() {
    delete vm;
  }

protected:
  void testManaging() {
    CPPUNIT_ASSERT(!vm->hasVariable("var"));
    CPPUNIT_ASSERT(vm->addVariable("var", "test"));
    CPPUNIT_ASSERT(vm->hasVariable("var"));
    CPPUNIT_ASSERT(vm->removeVariable("var"));

    CPPUNIT_ASSERT(!vm->removeVariable("var1"));
    CPPUNIT_ASSERT(vm->addVariable("var1", "test-2", true));
    CPPUNIT_ASSERT(!vm->addVariable("var1", 123));
    vm->clearVariables();
    CPPUNIT_ASSERT(!vm->removeVariable("var1"));
    CPPUNIT_ASSERT(!vm->hasVariable("var1"));
  }

  void testGetVar() {
    vm->addVariable("abc", 2020);
    vm->addVariable("l", "ok", true);

    CPPUNIT_ASSERT(vm->getVariable("l") >> String() == "ok");
    CPPUNIT_ASSERT(vm->getVariable("abc") >> int() == 2020);
    CPPUNIT_ASSERT(vm->getVariable("x")->getID() == Values::Void::id);

    vm->removeVariable("l");
    CPPUNIT_ASSERT(vm->getVariable("l")->getID() == Values::Void::id);

    vm->clearVariables();
  }

  void testTree() {
    iVariableManager* svm = new iVariableManager(vm);

    CPPUNIT_ASSERT(!svm->find("x"));

    vm->addVariable("a", 123);
    svm->addVariable("b", "water");

    CPPUNIT_ASSERT(svm->find("a")->getVariable("a") >> int() == 123);
    CPPUNIT_ASSERT(svm->find("b")->getVariable("b") >> String() == "water");

    svm->addVariable("a", 1050);

    CPPUNIT_ASSERT(svm->find("a")->getVariable("a") >> int() == 1050);

    delete svm;
    vm->clearVariables();
  }

  void testSetVars() {
    CPPUNIT_ASSERT(!vm->setVariable("var", 15, false));
    CPPUNIT_ASSERT(!vm->hasVariable("var"));
    CPPUNIT_ASSERT(vm->setVariable("var", 15));
    CPPUNIT_ASSERT(vm->hasVariable("var"));
    CPPUNIT_ASSERT(vm->addVariable("var1", "test-2", true));

    CPPUNIT_ASSERT(vm->getVariable("var") >> int() == 15);
    CPPUNIT_ASSERT(vm->getVariable("var1") >> String() == "test-2");

    CPPUNIT_ASSERT(vm->setVariable("var", "four", false));
    CPPUNIT_ASSERT(vm->setVariable("var1", 45, false));

    CPPUNIT_ASSERT(vm->getVariable("var") >> String() == "four");
    CPPUNIT_ASSERT(vm->getVariable("var1") >> int() == 45);

    iVariableManager::tVariableData data;

    data["abc"] = 123;
    data["var"] = "five";

    vm->setData(data);

    CPPUNIT_ASSERT(vm->hasVariable("abc"));
    CPPUNIT_ASSERT(vm->getVariable("var") >> String() == "five");
    CPPUNIT_ASSERT(vm->getVariable("abc") >> int() == 123);

    vm->clearVariables();
  }

  void testAccessToVar() {
    /*
    vm->addVariable("var", "cloudy", true);
    vm->addVariable("x", "mountain");
    vm->setVariable("y", "city");

    vm->setVariable("var", "sunny");
    vm->setVariable("x", "forest");
    vm->setVariable("y", "town");
    */
  }

private:
  iVariableManager* vm;
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestVariableManager);
