#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/Factory.h"
#include "../../Source/tokens/IF.h"
#include "../../Source/tokens/Unless.h"
#include "../../Source/tokens/Iterate.h"
#include "../../Source/tokens/Break.h"

using namespace Swift;

class TestFactory : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestFactory);

  CPPUNIT_TEST(testInit);
  CPPUNIT_TEST(testBind);
  CPPUNIT_TEST(testGetInstance);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp() { }
  void tearDown() { }

protected:
  void testInit() {
    CPPUNIT_ASSERT(Factory::get());
  }

  void testBind() {
    CPPUNIT_ASSERT(Factory::get()->isBinded("if"));

    //Factory::get()->bind("if", Tokens::IF::getInstance);
    Factory::get()->bind("unless", Tokens::Unless::getInstance);
    Factory::get()->bind("iterate", Tokens::Iterate::getInstance);
    Factory::get()->bind("break", Tokens::Break::getInstance);

    CPPUNIT_ASSERT(Factory::get()->isBinded("iterate"));

    Factory::get()->unbind("break");

    CPPUNIT_ASSERT(!Factory::get()->isBinded("break"));
  }

  void testGetInstance() {
    try {
      iToken* token_1 = Factory::get()->getInstance("unless", 0);
      CPPUNIT_ASSERT(token_1);
      CPPUNIT_ASSERT(token_1->getName() == "unless");
      delete token_1;

      iToken* token_2;
      token_2 = Factory::get()->getInstance("break", 0);
      CPPUNIT_ASSERT(token_2);

    } catch (const Stamina::Exception& e) {
      CPPUNIT_ASSERT(e.getReason() == "No instance of break");
    }
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestFactory);