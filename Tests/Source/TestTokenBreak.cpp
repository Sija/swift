#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/tokens/Break.h"

using namespace Swift;

class TestTokenBreak : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestTokenBreak);

  CPPUNIT_TEST(testOutput);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp() { }
  void tearDown() { }

protected:
  void testOutput() {
    iToken* token = new Tokens::Break;

    try {
      token->output();
      CPPUNIT_ASSERT(!"no break exception");
    } catch (const Tokens::BreakException& e) {
    }

    delete token;
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestTokenBreak);
