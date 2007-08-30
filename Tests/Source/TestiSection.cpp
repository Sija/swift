#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/iSection.h"
#include "../../Source/Values/String.h"
#include "../../Source/Values/Int.h"
#include "../../Source/Values/Void.h"

using namespace Swift;

class tiSection: public iSection {
public:
  tiSection() : iSection(0) { }

public:
  enSectionType getSectionType() const {
    switch (t) {
      case 1:
        return tNamed;
      case 2:
        return tUnnamed;
      case 3:
        return tNoArgs;
    }
  }

  String output() {
    return "";
  }

public:
  int t;
};

class TestiSection : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestiSection);

  CPPUNIT_TEST(testManagingReqArgs);
  CPPUNIT_TEST(testManagingDefArgs);
  CPPUNIT_TEST(testManagingArgs);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp() {
    section = new tiSection;
  }
  void tearDown() {
    delete section;
  }

protected:
  void testManagingReqArgs() {
    CPPUNIT_ASSERT(!section->countRequired());

    section->t = 1;

    CPPUNIT_ASSERT(!section->isRequired("x"));
    CPPUNIT_ASSERT(!section->getRequiredType("y"));

    try {
      section->checkRequired();
    } catch (Stamina::Exception& e) {
      CPPUNIT_ASSERT(!"missing argument");
    }
    section->setRequired("h", Values::Int::id);

    CPPUNIT_ASSERT(section->isRequired("h"));
    CPPUNIT_ASSERT(section->getRequiredType("h") == Values::Int::id);

    try {
      section->checkRequired();
      CPPUNIT_ASSERT(!"ghost argument");
    } catch (Stamina::Exception& e) {
    }

    section->setRequired("h", Values::String::id);

    CPPUNIT_ASSERT(section->isRequired("h"));
    CPPUNIT_ASSERT(section->getRequiredType("h") == Values::String::id);
  }

  void testManagingDefArgs() {
    section->t = 1;

    CPPUNIT_ASSERT(!section->hasDefault("h"));
    CPPUNIT_ASSERT(section->getDefault("h")->getID() == Values::Void::id);
    CPPUNIT_ASSERT(section->getArg("h")->getID() == Values::Void::id);

    section->setDefault("h", 123);

    CPPUNIT_ASSERT(section->getDefault("h")->getID() == Values::Int::id);

    section->setDefault("h", "hidden");

    CPPUNIT_ASSERT(section->getArg("h") >> String() == "hidden");
    CPPUNIT_ASSERT(section->hasDefault("h"));
    CPPUNIT_ASSERT(section->getDefault("h") >> String() == "hidden");

    try {
      section->checkRequired();
    } catch (Stamina::Exception& e) {
      CPPUNIT_ASSERT(!"missing unknown argument");
    }
  }

  void testManagingArgs() {
    CPPUNIT_ASSERT(!section->argsCount());
    section->t = 1;

    CPPUNIT_ASSERT(!section->hasArg("test"));

    Param* param = new Param(0);
    param->add(12, operatorNone, operatorNone);

    CPPUNIT_ASSERT(section->getArg("test")->getID() == Values::Void::id);

    section->addArg("test", param);

    CPPUNIT_ASSERT(section->getArg("test") >> int() == 12);

    param = new Param(0);
    param->add("text", operatorNone, operatorNone);
    section->setArg("test", param);

    section->setRequired("test", Values::Void::id);

    try {
      section->getArg("test");
      CPPUNIT_ASSERT(!"value is void");
    } catch (Stamina::Exception& e) {
    }
  }

private:
  tiSection* section;
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestiSection);