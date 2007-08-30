#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/tokens/Continue.h"

using namespace Swift;

class TestTokenContinue : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestTokenContinue);

  CPPUNIT_TEST(testOutput);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp() { }
  void tearDown() { }

protected:
  void testOutput() {
    iToken* token = new Tokens::Continue;

    try {
      token->output();
      CPPUNIT_ASSERT(!"no continue exception");
    } catch (const Tokens::ContinueException& e) {
    }

    delete token;
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestTokenContinue);
